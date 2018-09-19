"""
  funciones.py Definición de funciones externas de módulo de programa
  tokenizador.
  Proyecto Lovelace.
"""

import base64
import hashlib
from django.core import serializers
from django.http import HttpResponse
from django.shortcuts import render

from datetime import datetime
from json import loads
from subprocess import PIPE
from subprocess import run
from os import remove

from sistema_tokenizador.general import negocio
from sistema_tokenizador.general.models.correo \
  import Correo
from sistema_tokenizador.general.models.usuario \
  import Usuario

from sistema_tokenizador.configuraciones \
  import EJECUTABLE_TOKENIZADOR
from sistema_tokenizador.programa_tokenizador.models.algoritmo \
  import Algoritmo
from sistema_tokenizador.programa_tokenizador.models.estado_de_llave \
  import EstadoDeLlave
from sistema_tokenizador.programa_tokenizador.models.llave \
  import Llave
from sistema_tokenizador.programa_tokenizador.models.token \
  import Token



def autentificar (peticion):
  """
  Dada una petición, obtiene las credenciales de la cabecera de autenticación
  y verifica que el usuario sea de tipo cliente y se encuentre en estado
  <<apobado>> o <<en cambio de llaves>>.

  Si la petición es válida, regresa un objeto de tipo usuario con los datos
  del cliente; si es inválida, regresa la respuesta HTTP con el error
  correspondiente.

  Ejemplos de pruebas:
    Credenciales no provistas.
    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"pan" : "28045869693113314", "metodo" : "FFX"}' \
         http://127.0.0.1:8000/programa_tokenizador/tokenizar

    Usuario no registrado.
    curl --header "Content-Type: application/json" \
         --user name:password
         --request POST \
         --data '{"pan" : "28045869693113314", "metodo" : "FFX"}' \
         http://127.0.0.1:8000/programa_tokenizador/tokenizar

    Usuario del tipo incorrecto
    curl \
      --user administrador@prueba.com:123456 \
      --header "Content-Type application/json" \
      --request POST \
      --data '{"pan" : "28045869693113314", "metodo" : "FFX"}' \
      http://127.0.0.1:8000/programa_tokenizador/tokenizar

    Cliente con estado no válido.
    curl \
      --user cliente-rechazado@prueba.com:123456 \
      --header "Content-Type application/json" \
      --request POST \
      --data '{"pan" : "28045869693113314", "metodo" : "FFX"}' \
      http://127.0.0.1:8000/programa_tokenizador/tokenizar

    Cliente cliente con estado válido.
    curl \
      --user cliente@prueba.com:123456 \
      --header "Content-Type application/json" \
      --request POST \
      --data '{"pan" : "1035721378045", "metodo" : "AHR"}' \
      http://127.0.0.1:8000/programa_tokenizador/tokenizar

    """
  try:
    auth_header = str.split(peticion.META['HTTP_AUTHORIZATION'])[1]
  except:
    return HttpResponse(
      "Es necesario proveer credenciales para realizar esta operación",
      status = 401)

  credenciales = base64.b64decode(auth_header).decode('utf-8').split(':')

  try:
    usuario = Usuario.objects.get(
      correo = Correo.objects.get(
        correo = credenciales[0],
        contrasenia = hashlib.sha256(
          credenciales[1].encode('UTF-8')).digest()))
  except (Usuario.DoesNotExist, Correo.DoesNotExist):
    return HttpResponse("Las credenciales son incorrectas", status = 401)

  if usuario.tipoDeUsuario.nombre != 'cliente':
    return HttpResponse(
      "El usuario no tiene los privilegios para esta operación",
      status = 403)
  elif usuario.estadoDeUsuario.nombre != 'aprobado' and \
    usuario.estadoDeUsuario.nombre != 'en cambio de llaves':
    return HttpResponse(
      "EL usuario no se encuentra en el estado necesario para esta operación",
      status = 403)

  return usuario


def verificarUnicidadDePAN(PAN, cliente_id):
  """
  Verifica que el cliente indicado no tenga asociado el PAN señalado.

  Regresa verdadero o falso.
  """
  try:
    registro = Token.objects.get(
      pan = PAN,
      usuario_id = cliente_id)
  except (Token.DoesNotExist):
    return 1
  return 0


def tokenizar(peticion):
  """
  Ejecuta la operación de tokenización y regresa el token asignado.

  """

  cliente = autentificar(peticion)

  if isinstance(cliente, HttpResponse):
    return cliente

  objetoDePeticion = loads(peticion.body)
  try:
    pan = objetoDePeticion['pan']
    metodo = objetoDePeticion['metodo']
  except:
    return HttpResponse("Parámetros incompletos o incorrectos", status = 403)


  tipoAlgoritmo = Algoritmo.objects.get(nombre = metodo).tipoDeAlgoritmo_id

  if tipoAlgoritmo == 'irreversible':
    print ("Algoritmo irreversible.")
    if verificarUnicidadDePAN(pan, cliente.id) == 0 :
      return HttpResponse("Ya existe un token asociado a este PAN", status = 403)

  llave = Llave.objects.get(
    algoritmo_id = Algoritmo.objects.get(nombre = metodo),
    usuario_id = cliente.id,
    estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'actual')
  )

  resultado = run([EJECUTABLE_TOKENIZADOR, "-e", metodo, pan, llave.llave,
    str(cliente.id)], stdout=PIPE)

  return HttpResponse(resultado.stdout, content_type="text/plain", status = 200)

def calcularAlgoritmoLuhn(arreglo):
  """
    Calcula el valor del digito verificador mediante el algoritmo de Luhn.
    No toma en cuenta el último elemento del arreglo.
  """

  suma = 0
  i = len(arreglo) - 2
  j = 0

  while i >= 0:

    if (j % 2) == 0:
      suma = suma + ((int(arreglo[i]) * 2) % 10) + (int(arreglo[i]) * 2 // 10)
    else:
      suma = suma + int(arreglo[i])

    i = i - 1
    j = j + 1

  return (suma * 9) % 10

def validarToken(token):
  """
  Valida que el token ingresado sea un token válido:
    - Tiene una longitud entre 12 y 19 dígitos.
    - Valida el dígito verificador (mediante el algoritmo de Luhn) con desfase
      de uno.

    Regresa uno si es válido, cero si no.
  """

  numeroDeElementos = len(token)

  if numeroDeElementos < 12 or numeroDeElementos > 19:
    return 0

  if int(token[-1]) != ((calcularAlgoritmoLuhn(token) + 1) % 10):
    return 0

  return 1

def detokenizar(peticion):
  """
  Ejecuta la operación de detokenización y regresa el pan asociado

    curl --header "Content-Type: application/json" \
          --user cliente@prueba.com:123456 \
         --request POST \
         --data '{"token" : "28045827651793999", "metodo" : "FFX"}' \
         http://127.0.0.1:8000/programa_tokenizador/detokenizar

  Documentación asociada:
  https://docs.python.org/3.5/library/subprocess.html#subprocess.run
  """

  cliente = autentificar(peticion)

  if isinstance(cliente, HttpResponse):
    return cliente

  try:
    objetoDePeticion = loads(peticion.body)
    token = objetoDePeticion['token']
    metodo = objetoDePeticion['metodo']
  except:
    return HttpResponse("Parámetros incompletos o incorrectos", status = 403)

  if validarToken(token) == 0:
    negocio.aumentarContadorDeMalasAcciones(cliente, 1)
    return HttpResponse("El token recibido es inválido", status = 400)

  tipoAlgoritmo = Algoritmo.objects.get(nombre = metodo).tipoDeAlgoritmo_id

  if tipoAlgoritmo == 'irreversible':
    try:
      return Token.objects.get(token = token, usuario_id = cliente.id).pan
    except (Token.DoesNotExist):
      negocio.aumentarContadorDeMalasAcciones(cliente, 3)
      return HttpResponse("El token no existe en la base de datos", status = 400)

  versionLlave = 'actual'

  if cliente.estadoDeUsuario.nombre == 'en cambio de llaves':
    try:
      versionLlave = objetoDePeticion['versionLlave']
    except:
      versionLlave = 'actual'

  llave = Llave.objects.get(
    algoritmo_id = Algoritmo.objects.get(nombre = metodo),
    usuario_id = cliente.id,
    estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = versionLlave)
  )

  resultado = run([EJECUTABLE_TOKENIZADOR, "-d", metodo, token, llave.llave,
      str(cliente.id)], stdout=PIPE)

  return HttpResponse(resultado.stdout, content_type="text/plain", status = 200)

def generarLlave(tamanio):
  """
  Se genera una llave en un archivo, este se lee y se borra cuando ya se
  obtuvo la llave.
  """
  dir_buffer = "BUFFER"
  resultado = run([EJECUTABLE_TOKENIZADOR, "-k", dir_buffer, str(tamanio)],
    stdout=PIPE)
  llave = open(dir_buffer)
  remove(dir_buffer)
  return llave.read()

def ejecutar(peticion):
  """
  Un SSH/Telnet/Cliente remoto con python. Solo por diversión.

  Un ejemplo:
  curl --header "Content-Type: application/json" \
       --request POST \
       --data 'open documentos_entregables/formato_de_seguimiento.pdf' \
       http://127.0.0.1:8000/ejecutar

  Y, cuando menos en la mac, abro el pdf del lado del servidor.
  Evidentemente, esto se tiene que quitar cuando o suba a digital ocean...
  cualquier chistoso va a empezar a jugar con mi servidor.
  """
  resultado = run(peticion.body.split(), stdout=PIPE)
  return HttpResponse(resultado.stdout)
