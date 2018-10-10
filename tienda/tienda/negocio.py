"""
Operaciones de negocio de módulo de tienda,
Tienda en línea.
Proyecto Lovelace.
"""

import hashlib

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
