"""
  Modelo de usuarios,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from .estado_de_usuario import EstadoDeUsuario
from .tipo_de_usuario import TipoDeUsuario
from .correo import Correo
from django.db import models

class Usuario (models.Model):
  """Representación de un usuario dentro del sistema."""

  correo = models.ForeignKey(
    'Correo',
    models.PROTECT,
    verbose_name = 'correo electrónico')

  tipoDeUsuario = models.ForeignKey(
    'TipoDeUsuario',
    models.PROTECT,
    verbose_name = 'tipo de usuario')

  estadoDeUsuario = models.ForeignKey(
    'EstadoDeUsuario',
    models.PROTECT,
    verbose_name = 'estado del usuario')

  contadorDeMalasAcciones = models.PositiveIntegerField(
    default = 0,
    verbose_name = 'contador de malas acciones')


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return str(self.id) + ' - ' + self.correo
