"""
  Modelo de registro PAN-token para programa tokenizador,
  Aplicación web de sistena tokenizador.
  Proyecto Lovelace.
"""

import django
from .estado_de_token import EstadoDeToken


def estadoPorDefecto ():
  return EstadoDeToken.objects.get(nombre = 'actual')


class Token (django.db.models.Model):
  """Relación entre PAN-token."""

  token = django.db.models.CharField(
    verbose_name = 'Token',
    max_length = 19)

  pan = django.db.models.CharField(
    verbose_name = 'Número de tarjeta',
    max_length = 19)

  usuario = django.db.models.ForeignKey(
    'general.Usuario',
    django.db.models.PROTECT,
    verbose_name = 'Usuario dueño del token',
    default = None,
    null = True)

  estadoDeToken = django.db.models.ForeignKey(
    'EstadoDeToken',
    django.db.models.PROTECT,
    verbose_name = 'Estado del token',
    default = estadoPorDefecto,
    null = True)

  class Meta:
    unique_together = ('usuario', 'token')

  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return str(self.id) + ' - ' + self.token + ' - ' + self.token
