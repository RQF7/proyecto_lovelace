"""
  Modelo de usuarios,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import django
from .correo import Correo
from .estado_de_usuario import EstadoDeUsuario
from .tipo_de_usuario import TipoDeUsuario

class Usuario (django.db.models.Model):
  """Representación de un usuario dentro del sistema."""

  correo = django.db.models.ForeignKey(
    'Correo',
    django.db.models.PROTECT,
    verbose_name = 'correo electrónico')

  tipoDeUsuario = django.db.models.ForeignKey(
    'TipoDeUsuario',
    django.db.models.PROTECT,
    verbose_name = 'tipo de usuario')

  estadoDeUsuario = django.db.models.ForeignKey(
    'EstadoDeUsuario',
    django.db.models.PROTECT,
    verbose_name = 'estado del usuario',
    null = True)

  contadorDeMalasAcciones = django.db.models.PositiveIntegerField(
    default = 0,
    verbose_name = 'contador de malas acciones')


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return str(self.id) + ' - ' + str(self.correo)
