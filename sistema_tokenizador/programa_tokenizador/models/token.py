"""
  Modelo de registro PAN-token para programa tokenizador,
  Aplicación web de sistena tokenizador.
  Proyecto Lovelace.

  TODO: Actualizar campos que deben ser únicos;
  De momento están así para no matar el script de pruebas de c++.
"""

from .estado_de_token import EstadoDeToken
from ...general.models.usuario import Usuario
from django.db import models

class Token (models.Model):
  """Relación entre PAN-token."""

  token = models.CharField(
    verbose_name = 'Token',
    max_length = 19)

  pan = models.CharField(
    verbose_name = 'Número de tarjeta',
    max_length = 19)

  # TODO:
  # ¿Cambiar tipo de llave foránea a models.CASCADE?
  usuario = models.ForeignKey(
    'general.Usuario',
    models.PROTECT,
    verbose_name = 'Usuario dueño del token')

  estadoDeToken = models.ForeignKey(
    'EstadoDeToken',
    models.PROTECT,
    verbose_name = 'Estado del token')


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return str(self.id) + ' - ' + self.token + ' - ' + self.token
