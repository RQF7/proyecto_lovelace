"""
  Modelo de usuarios,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from .estado_de_usuario import EstadoDeUsuario
from .tipo_de_usuario import TipoDeUsuario
from django.db import models

class Usuario (models.Model):
  """Representación de un usuario dentro del sistema."""

  correo = models.CharField(
    verbose_name = 'correo electrónico',
    unique = True,
    max_length = 100)

  contrasenia = models.BinaryField(
    verbose_name = 'Hash de contraseña')

  tipoDeUsuario = models.ForeignKey(
    'TipoDeUsuario',
    models.PROTECT,
    verbose_name = 'tipo de usuario')

  estadoDeUsuario = models.ForeignKey(
    'EstadoDeUsuario',
    models.PROTECT,
    verbose_name = 'estado del usuario')


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return str(self.id) + ' - ' + self.correo
