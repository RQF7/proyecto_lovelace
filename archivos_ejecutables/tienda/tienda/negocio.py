"""
Operaciones de negocio de módulo de tienda,
Tienda en línea.
Proyecto Lovelace.
"""


import datetime
import hashlib
import json
import requests

import tienda.configuraciones as configuraciones
import tienda.utilidades as utilidades

from .models.compra import Compra
from .models.direccion import Direccion
from .models.emisor import Emisor
from .models.estado import Estado
from .models.metodo import Metodo
from .models.paquete import Paquete
from .models.tarjeta import Tarjeta
from .models.tipo_de_direccion import TipoDeDireccion
from .models.tipo_de_tarjeta import TipoDeTarjeta
from .models.usuario import Usuario


def autentificar (usuarioEnPeticion):
  """Valida el usuario dado (correo y contraseña).

  En caso de no existir, regresa None; en caso correcto,
  regresa el objeto del usuario."""
  try:
    resultado = Usuario.objects.get(
      correo = usuarioEnPeticion['correo'],
      contrasenia = hashlib.sha256(
        usuarioEnPeticion['contrasenia'].encode('UTF-8')).digest())
    return resultado
  except Usuario.DoesNotExist:
    return None


def correoPreviamenteRegistrado (usuarioEnPeticion, pk = None):
  """ Verifica si un usuario ya esta registrado.
      Si se da una pk, se excluye el registro con la misma. """
  try:
    if pk != None:
      Usuario.objects.exclude(pk = pk).get(
        correo = usuarioEnPeticion["correo"])
    else:
      Usuario.objects.get(correo = usuarioEnPeticion["correo"])
    return True
  except Usuario.DoesNotExist:
    return False


def crearVinculoDeVerificacion (correo):
  """Crea un nuevo vínculo de verificación."""
  fecha = datetime.datetime.utcnow()
  hash = hashlib.sha256()
  hash.update(correo.encode())
  hash.update(str(fecha).encode())
  return {"vinculo":hash.hexdigest(),"fecha":fecha}


def enviarVinculoDeVerificacion (usuario, tipo):
  """Envia el vínculo de verificación al usuario dado."""
  utilidades.enviarCorreo(
    usuario.correo,
    "Verificación de correo - Librería",
    """
    Estimado usuario:

    Para poder verificar su correo en la librería debe hacer clic
    en el siguiente vínculo:

    {0}/api/tienda/verificar_correo/{1}/{2}

    Atentamente,
    Departamento de verificación de cuentas,
    Tienda en línea.
    Proyecto Lovelace.
    """.format(configuraciones.DOMINIO, tipo, usuario.vinculo))


def guardarUsuario (usuarioEnPeticion):
  """ Función para guardar un usuario en petición en la BD,
      la función retorna el objeto usuario.                  """
  vinculo = crearVinculoDeVerificacion(usuarioEnPeticion["correo"])
  usuario = Usuario(
    nombre = usuarioEnPeticion["nombre"],
    correo = usuarioEnPeticion["correo"],
    contrasenia = hashlib.sha256(
      usuarioEnPeticion["contrasenia"].encode('UTF-8')).digest(),
    vinculo = vinculo["vinculo"],
    fecha = vinculo["fecha"],
    verificado = 0)
  usuario.save()
  enviarVinculoDeVerificacion(usuario,"registro")


def actualizarUsuario (usuarioEnPeticion, pk):
  """ Función para actualizar a un usuario en la BD,
      la función retorna una bandera para saber si la
      actualización abarco al correo del usuario.     """

  usuario = Usuario.objects.get(pk = pk)

  if usuario.correo == usuarioEnPeticion["correo"]:
    usuario.nombre = usuarioEnPeticion["nombre"]
    usuario.contrasenia = hashlib.sha256(
      usuarioEnPeticion["contrasenia"].encode('UTF-8')).digest()
    banderaCorreoModificado = True
  else:
    vinculo = crearVinculoDeVerificacion(usuarioEnPeticion["correo"])
    usuario.nombre = usuarioEnPeticion["nombre"]
    usuario.correo = usuarioEnPeticion["correo"]
    usuario.contrasenia = hashlib.sha256(
      usuarioEnPeticion["contrasenia"].encode('UTF-8')).digest()
    usuario.vinculo = vinculo["vinculo"]
    usuario.fecha = vinculo["fecha"]
    usuario.verificado = False
    enviarVinculoDeVerificacion(usuario,"actualizacion")
    banderaCorreoModificado = False

  usuario.save(force_update = True)

  return banderaCorreoModificado


def crearDireccion (direccion):
  """Genera una nueva diercción en la base de datos.

  Recibe un objeto de tipo diccionario con los datos de la nueva dirección;
  regresa la instancia de la dirección ya guardada en la base."""
  direccion = Direccion(
    tipoDeDireccion = TipoDeDireccion.objects.get(nombre = 'Facturación'),
    estado = Estado.objects.get(pk = direccion['fields']['estado']),
    municipio = direccion['fields']['municipio'],
    colonia = direccion['fields']['colonia'],
    calle = direccion['fields']['calle'],
    cp = direccion['fields']['cp'],
    activa = True,
    numeroInterior = direccion['fields']['numeroInterior'],
    numeroExterior = direccion['fields']['numeroExterior'])
  direccion.save()
  return direccion


def tokenizar (numeroDeTarjeta, metodo):
  """Realiza una operación de tokenización.

  Hace un post al sistema tokenizador. Para la conexión se ocupan los valores
  definidos en las configuraciones de la tienda: url, usuario y contrasenia.
  En caso de error, se levanta una excepción de error de sistema.
  """
  peticion = requests.post(
    configuraciones.SISTEMA_TOKENIZADOR
    + '/api/programa_tokenizador/tokenizar',
    auth = (configuraciones.USUARIO_ST, configuraciones.CONTRASENIA_ST),
    data = json.dumps({'pan': numeroDeTarjeta, 'metodo': metodo}))
  if peticion.status_code != 200:
    raise SystemError(
      'Error en tokenización: {0}'.format(peticion.status_code))
  return peticion.text.replace('\n','')


def detokenizar (token, metodo):
  """Realiza una operación de detokenización.

  Hace un post al sistema tokenizador.
  En caso de error, se levanta una excepción de error de sistema.
  """
  peticion = requests.post(
    configuraciones.SISTEMA_TOKENIZADOR
    + '/api/programa_tokenizador/detokenizar',
    auth = (configuraciones.USUARIO_ST, configuraciones.CONTRASENIA_ST),
    data = json.dumps({'token': token, 'metodo': metodo}))
  if peticion.status_code != 200:
    raise SystemError(
      'Error en detokenización: {0}'.format(peticion.status_code))
  return peticion.text.replace('\n','')

