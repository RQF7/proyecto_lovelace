"""
  Modelo de registro PAN-token para programa tokenizador,
  Aplicación web de sistena tokenizador.
  Proyecto Lovelace.

  TODO: Actualizar campos que deben ser únicos;
  De momento están así para no matar el script de pruebas de c++.
"""

import django

from .estado_de_token import EstadoDeToken


def estadoPorDefecto ():
  return EstadoDeToken.objects.get(nombre = 'actual')


def usuarioPorDefecto ():
  return Usuario.objects.get(id = 1)


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
