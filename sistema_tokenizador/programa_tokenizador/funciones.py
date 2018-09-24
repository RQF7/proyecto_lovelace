"""
funciones.py Definición de funciones externas de módulo de programa
tokenizador.
Proyecto Lovelace.
"""

import base64
import hashlib
import django
import json
import subprocess

import sistema_tokenizador.configuraciones as configuraciones
import sistema_tokenizador.general as general

from .models.algoritmo import Algoritmo
from .models.estado_de_llave import EstadoDeLlave
from .models.estado_de_token import EstadoDeToken
from .models.llave import Llave
from .models.token import Token
from ..programa_tokenizador import negocio


def autentificar (peticion):
  """Verifica las credenciales de la petición dada.

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
         http://127.0.0.1:8000/api/programa_tokenizador/tokenizar

    Usuario no registrado.
    curl --header "Content-Type: application/json" \
         --user name:password
         --request POST \
         --data '{"pan" : "28045869693113314", "metodo" : "FFX"}' \
         http://127.0.0.1:8000/api/programa_tokenizador/tokenizar

    Usuario del tipo incorrecto
    curl \
      --user administrador@prueba.com:123456 \
      --header "Content-Type application/json" \
      --request POST \
      --data '{"pan" : "28045869693113314", "metodo" : "FFX"}' \
      http://127.0.0.1:8000/api/programa_tokenizador/tokenizar

    Cliente con estado no válido.
    curl \
      --user cliente-rechazado@prueba.com:123456 \
      --header "Content-Type application/json" \
      --request POST \
      --data '{"pan" : "28045869693113314", "metodo" : "FFX"}' \
      http://127.0.0.1:8000/api/programa_tokenizador/tokenizar

    Cliente cliente con estado válido.
    curl \
      --user cliente@prueba.com:123456 \
      --header "Content-Type application/json" \
      --request POST \
      --data '{"pan" : "1035721378045", "metodo" : "AHR"}' \
      http://127.0.0.1:8000/api/programa_tokenizador/tokenizar

    """
  try:
    auth_header = str.split(peticion.META['HTTP_AUTHORIZATION'])[1]
  except:
    return django.http.HttpResponse(
      "Es necesario proveer credenciales para realizar esta operación",
      status = 401)

  credenciales = base64.b64decode(auth_header).decode('utf-8').split(':')

  try:
    usuario = general.models.usuario.Usuario.objects.get(
      correo = general.models.correo.Correo.objects.get(
        correo = credenciales[0],
        contrasenia = hashlib.sha256(
          credenciales[1].encode('UTF-8')).digest()))
  except (general.models.usuario.Usuario.DoesNotExist,
    general.models.correo.Correo.DoesNotExist):
    return django.http.HttpResponse("Las credenciales son incorrectas",
      status = 401)

  if usuario.tipoDeUsuario.nombre != 'cliente':
    return django.http.HttpResponse(
      "El usuario no tiene los privilegios para esta operación",
      status = 403)
  elif usuario.estadoDeUsuario.nombre != 'aprobado' and \
    usuario.estadoDeUsuario.nombre != 'en cambio de llaves':
    return django.http.HttpResponse(
      "EL usuario no se encuentra en el estado necesario para esta operación",
      status = 403)

  return usuario


def tokenizar (peticion):
  """Ejecuta la operación de tokenización y regresa el token asignado.

  Si ya se había tokenizado ese PAN, regresa el token creado. Si se encuentra
  en cambio de llaves y tiene el actual y el viejo/retokenizado, se regresa
  el actual. Si está en cambio de llaves y solo tiene el viejo, se regresa
  un error, pidiendo que retokenice."""

  cliente = autentificar(peticion)

  if isinstance(cliente, django.http.HttpResponse):
    return cliente

  objetoDePeticion = json.loads(peticion.body)
  try:
    pan = objetoDePeticion['pan']
    metodo = objetoDePeticion['metodo'].upper()
  except:
    return django.http.HttpResponse("Parámetros incompletos o incorrectos",
      status = 403)

  if negocio.validarPan(pan) == 0:
    return django.http.HttpResponse("El PAN recibido es inválido.",
      status = 400)

  tipoAlgoritmo = Algoritmo.objects.get(nombre = metodo).tipoDeAlgoritmo_id

  ## Si el algoritmo es reversible o es irreversible y el PAN no está registrado
  ## en la base de datos, crear un nuevo token y regresarlo.
  if tipoAlgoritmo == 'reversible' or (tipoAlgoritmo == 'irreversible' and \
    (negocio.verificarUnicidadDePAN(pan, cliente.id) == 1)):
    llave = Llave.objects.get(
      algoritmo_id = Algoritmo.objects.get(nombre = metodo),
      usuario_id = cliente.id,
      estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'actual'))

    resultado = subprocess.run([
      configuraciones.EJECUTABLE_TOKENIZADOR,
      "-e",
      metodo,
      pan,
      llave.llave,
      str(cliente.id)], stdout = subprocess.PIPE)

    return django.http.HttpResponse(resultado.stdout, status = 200)

  ## Si el PAN especificado ya está asociado al cliente, regresar el token si
  ## el estado del cliente es aprobado.
  if cliente.estadoDeUsuario.nombre == 'aprobado':
    return django.http.HttpResponse(
      Token.objects.get(
        usuario_id = cliente.id,
        pan = pan).token,
      status = 403)

  ## Si está en cambio de llaves, puede tener uno o dos tokens asociados a ese
  ## PAN.
  tokens = Token.objects.filter(
    usuario_id = cliente.id,
    pan = pan)

  ## Si solo tiene uno y es el actual, regresar ese token; si el token tiene
  ## otro estado, debe realizar la operacion de retokenizacion para obtener
  ## la nueva versión.
  if len(tokens) == 1:
    if tokens[0].estadoDeToken.nombre == 'actual':
      return django.http.HttpResponse(tokens[0].token, status = 403)
    else:
      return django.http.HttpResponse(
        'Ya existe un token asociado, utilice la función de retokenización',
        status = 400)

  ## Si tiene dos, uno es el actual y otro es el viejo o retokenizado; regresar
  ## el actual.
  if tokens[0].estadoDeToken.nombre == 'actual':
    return django.http.HttpResponse(tokens[0].token, status = 403)
  else:
    return django.http.HttpResponse(tokens[1].token, status = 403)


def detokenizar (peticion):
  """Ejecuta la operación de detokenización y regresa el pan asociado.

  Documentación asociada:
  https://docs.python.org/3.5/library/subprocess.html#subprocess.run"""

  cliente = autentificar(peticion)

  if isinstance(cliente, django.http.HttpResponse):
    return cliente

  try:
    objetoDePeticion = json.loads(peticion.body)
    token = objetoDePeticion['token']
    metodo = objetoDePeticion['metodo'].upper()
  except:
    return django.http.HttpResponse("Parámetros incompletos o incorrectos",
      status = 403)

  if negocio.validarToken(token) == 0:
    negocio.aumentarContadorDeMalasAcciones(
      cliente,
      negocio.INCREMENTO_TOKEN_INVALIDO)
    return django.http.HttpResponse("El token recibido es inválido",
      status = 400)

  tipoAlgoritmo = Algoritmo.objects.get(nombre = metodo).tipoDeAlgoritmo_id

  if tipoAlgoritmo == 'irreversible':
    try:
      return django.http.HttpResponse(
        Token.objects.get(token = token, usuario_id = cliente.id).pan,
        status = 200)
    except (Token.DoesNotExist):
      negocio.aumentarContadorDeMalasAcciones(
        cliente,
        negocio.INCREMENTO_TOKEN_INEXISTENTE)
      return django.http.HttpResponse(
        "El token no existe en la base de datos", status = 400)

  versionLlave = 'actual'

  if cliente.estadoDeUsuario.nombre == 'en cambio de llaves':
    try:
      versionLlave = objetoDePeticion['versionLlave']
    except:
      pass

  llave = Llave.objects.get(
    algoritmo_id = Algoritmo.objects.get(nombre = metodo),
    usuario_id = cliente.id,
    estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = versionLlave))

  resultado = subprocess.run([
    configuraciones.EJECUTABLE_TOKENIZADOR,
    "-d",
    metodo,
    token,
    llave.llave,
    str(cliente.id)], stdout = subprocess.PIPE)

  return django.http.HttpResponse(resultado.stdout, status = 200)


def retokenizar (peticion):
  """Ejecuta la operación de retokenización; regresa el nuevo token.

  Se encarga de, dado un token, obtener la nueva versión al detokenizar con la
  llave anterior y tokenizar el resultado con la llave actual. Obviamente,
  esta operación solo la puede requerir un cliente cuyo estado sea <<en cambio
  de llaves>>."""

  cliente = autentificar(peticion)

  if isinstance(cliente, django.http.HttpResponse):
    return cliente

  try:
    objetoDePeticion = json.loads(peticion.body)
    token = objetoDePeticion['token']
    metodo = objetoDePeticion['metodo'].upper()
  except:
    return django.http.HttpResponse("Parámetros incompletos o incorrectos",
      status = 403)

  if cliente.estadoDeUsuario.nombre != 'en cambio de llaves':
    return django.http.HttpResponse(
      "EL usuario no se encuentra en el estado necesario para esta operación",
      status = 403)

  if negocio.validarToken(token) == 0:
    negocio.aumentarContadorDeMalasAcciones(
      cliente,
      negocio.INCREMENTO_TOKEN_INVALIDO)
    return django.http.HttpResponse("El token recibido es inválido",
      status = 400)

  tipoAlgoritmo = Algoritmo.objects.get(nombre = metodo).tipoDeAlgoritmo_id

  if tipoAlgoritmo == 'irreversible':
    try:
      tokenAnterior = Token.objects.get(
        django.db.models.Q(token = token),
        django.db.models.Q(usuario_id = cliente.id),
        django.db.models.Q(estadoDeToken = EstadoDeToken.objects.get(
          nombre = 'anterior')) |
        django.db.models.Q(estadoDeToken = EstadoDeToken.objects.get(
          nombre = 'retokenizado')))
    except (Token.DoesNotExist):
      negocio.aumentarContadorDeMalasAcciones(
        cliente,
        negocio.INCREMENTO_TOKEN_INEXISTENTE)
      return django.http.HttpResponse(
        "El token no existe en la base de datos", status = 400)

    if tokenAnterior.estadoDeToken.nombre == 'retokenizado':
      return django.http.HttpResponse(
        Token.objects.get(
          pan = tokenAnterior.pan,
          usuario_id = cliente.id,
          estadoDeToken = EstadoDeToken.objects.get(nombre = 'actual')
        ).token, status = 403)

    llaveActual = Llave.objects.get(
      algoritmo_id = Algoritmo.objects.get(nombre = metodo),
      usuario_id = cliente.id,
      estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'actual'))

    nuevoToken = subprocess.run([
      configuraciones.EJECUTABLE_TOKENIZADOR,
      "-e",
      metodo,
      tokenAnterior.pan,
      llaveActual.llave,
      str(cliente.id)], stdout = subprocess.PIPE)

    tokenAnterior.estadoDeToken = EstadoDeToken.objects.get(
      nombre = 'retokenizado')
    tokenAnterior.save()

    return django.http.HttpResponse(nuevoToken.stdout, status = 200)

  else:

    llaveAnterior = Llave.objects.get(
      algoritmo_id = Algoritmo.objects.get(nombre = metodo),
      usuario_id = cliente.id,
      estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'anterior'))

    llaveActual = Llave.objects.get(
      algoritmo_id = Algoritmo.objects.get(nombre = metodo),
      usuario_id = cliente.id,
      estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'actual'))

    pan = subprocess.run([
      configuraciones.EJECUTABLE_TOKENIZADOR,
      "-d",
      metodo,
      token,
      llaveAnterior.llave,
      str(cliente.id)], stdout = subprocess.PIPE)

    nuevoToken = subprocess.run([
      configuraciones.EJECUTABLE_TOKENIZADOR,
      "-e",
      metodo,
      str(int(pan.stdout)),
      llaveActual.llave,
      str(cliente.id)], stdout = subprocess.PIPE)

    return django.http.HttpResponse(nuevoToken.stdout, status = 200)


