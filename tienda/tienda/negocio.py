"""
Operaciones de negocio de módulo de tienda,
Tienda en línea.
Proyecto Lovelace.
"""

import hashlib
import datetime

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
import tienda.configuraciones as configuraciones
import tienda.utilidades as utilidades


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


def existeUsuario (usuarioEnPeticion):
  """Verifica si un usuario existe."""
  try:
    Usuario.objects.get(correo = usuarioEnPeticion["correo"])
    return 1
  except Usuario.DoesNotExist:
    return 0


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
  return usuario


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
