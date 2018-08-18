"""
  Operaciones de negocio de backend,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import hashlib
from .models.usuario import Usuario

def autenticar (usuarioEnPeticion):
  """
  Valida el usuario dado (correo y contraseña).

  En caso de no existir, regresa None; en caso correcto,
  regresa el objeto del usuario.
  """
  try:
    usuario = Usuario.objects.get(
      correo = usuarioEnPeticion['correo'],
      contrasenia = hashlib.sha256(
        usuarioEnPeticion['contrasenia'].encode('UTF-8')).digest())
    return usuario
  except Usuario.DoesNotExist:
    return None
