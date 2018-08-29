"""
  Modelo de registro PAN-token para programa tokenizador,
  Aplicación web de sistena tokenizador.
  Proyecto Lovelace.
"""

from django.db import models

class Registro (models.Model):
  """Relación entre PAN-token."""

  pan = models.CharField(
    verbose_name = 'Número de tarjeta',
    unique = True,
    max_length = 19)

  token = models.CharField(
    verbose_name = 'Token',
    unique = True,
    max_length = 19)


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return str(self.id) + ' - ' + self.token + ' - ' + self.token
