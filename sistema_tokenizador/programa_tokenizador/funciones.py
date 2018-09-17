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
from json import loads
from subprocess import PIPE
from subprocess import run
import base64

from sistema_tokenizador.general.models.correo import Correo
from sistema_tokenizador.general.models.usuario import Usuario

from sistema_tokenizador.configuraciones import EJECUTABLE_TOKENIZADOR

def autentificar (peticion):
  """
  Dada una petición, obtiene las credenciales de la cabecera de autenticación
  y verifica que el usuario sea de tipo cliente y se encuentre en estado
  <<apobado>> o <<en cambio de llaves>>.

  Si la petición es válida, regresa un objeto de tipo usuario con los datos
  del cliente; si es inválida, regresa la respuesta HTTP con el error
  correspondiente.

  Ejemplos de pruebas:
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
      --data '{"pan" : "28045869693113314", "metodo" : "FFX"}' \
      http://127.0.0.1:8000/programa_tokenizador/tokenizar

    """
  try:
    auth_header = str.split(peticion.META['HTTP_AUTHORIZATION'])[1]
  except:
    return HttpResponse("401 - Credenciales no provistas")

  credenciales = base64.b64decode(auth_header).decode('utf-8').split(':')

  try:
    usuario = Usuario.objects.get(
      correo = Correo.objects.get(
        correo = credenciales[0],
        contrasenia = hashlib.sha256(
          credenciales[1].encode('UTF-8')).digest()))
  except (Usuario.DoesNotExist, Correo.DoesNotExist):
    return HttpResponse("401 - credenciales incorrectas")

  if usuario.tipoDeUsuario.nombre != 'cliente':
    return HttpResponse("403 - usuario no es tipo cliente")
  elif usuario.estadoDeUsuario.nombre != 'aprobado' and usuario.estadoDeUsuario.nombre != 'en cambio de llaves':
    return HttpResponse("403 - Todo mal: estado incorrecto")

  return usuario


def tokenizar(peticion):
  """
  Ejecuta la operación de tokenización y regresa el token asignado.

  """

  resultado = autentificar(peticion)

  if isintance(resultado, HttpResponse):
    return resultado

  auth_header = str.split(peticion.META['HTTP_AUTHORIZATION'])[1]
  credenciales = base64.b64decode(auth_header).decode('utf-8').split(':')

  print('Credenciales:', credenciales)
  usuario = autentificar(credenciales[0], credenciales[1])

  if usuario != None:
    if usuario.tipoDeUsuario.nombre != 'cliente':
      return HttpResponse("403 - usuario no es tipo cliente")
    elif usuario.estadoDeUsuario.nombre != 'aprobado' and usuario.estadoDeUsuario.nombre != 'en cambio de llaves':
      return HttpResponse("403 - Todo mal: estado incorrecto")
  else:
    return HttpResponse("401 - credenciales incorrectas")

  objetoDePeticion = loads(peticion.body)
  pan = objetoDePeticion['pan']
  metodo = objetoDePeticion['metodo']

  return HttpResponse("200 - TODO BIEN")


  ##resultado = run([EJECUTABLE_TOKENIZADOR, "-e", metodo, pan, "llave.txt"],
  ## stdout=PIPE)
  ##return HttpResponse(resultado.stdout)
  #return HttpResponse("All is fine")


def detokenizar(peticion):
  """
  Ejecuta la operación de detokenización y regresa el pan asociado

  Ejemplo:
  curl --header "Content-Type: application/json" \
       --request POST \
       --data '{"token" : "28045851286256503", "metodo": "FFX"}' \
       http://127.0.0.1:8000/programa_tokenizador/detokenizar

  Documentación asociada:
  https://docs.python.org/3.5/library/subprocess.html#subprocess.run
  """
  objetoDePeticion = loads(peticion.body)
  token = objetoDePeticion['token']
  metodo = objetoDePeticion['metodo']
  resultado = run([EJECUTABLE_TOKENIZADOR, "-d", metodo, token, "llave.txt"],
    stdout=PIPE)
  return HttpResponse(resultado.stdout)


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
