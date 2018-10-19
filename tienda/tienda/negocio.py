"""
Operaciones de negocio de módulo de tienda,
Tienda en línea.
Proyecto Lovelace.
"""

import hashlib
import datetime

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


def existeCorreo (usuarioEnPeticion, pk):
  """Verifica si un usuario existe."""
  try:
    Usuario.objects.exclude(pk = pk).get(correo = usuarioEnPeticion["correo"])
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


def actualizarUsuario (usuarioEnPeticion, pk):
  """ La función regresa 1 si se modifico el correo y 0 si no """
  usuario = Usuario.objects.get(pk = pk)
  if usuario.correo == usuarioEnPeticion["correo"]:
    usuario.nombre = usuarioEnPeticion["nombre"]
    usuario.contrasenia = hashlib.sha256(
      usuarioEnPeticion["contrasenia"].encode('UTF-8')).digest()
    usuario.save(force_update=True)
    correoActualizado = "2"
  else:
    vinculo = crearVinculoDeVerificacion(usuarioEnPeticion["correo"])
    usuario = Usuario(pk = pk,
    nombre = usuarioEnPeticion["nombre"],
    correo = usuarioEnPeticion["correo"],
    contrasenia = hashlib.sha256(
      usuarioEnPeticion["contrasenia"].encode('UTF-8')).digest(),
    vinculo = vinculo["vinculo"],
    fecha = vinculo["fecha"],
    verificado = 0)
    enviarVinculoDeVerificacion(usuario,"actualizacion")
    usuario.save(force_update=True)
    correoActualizado = "0"
  return {"usuario":usuario, "correoActualizado":correoActualizado}

