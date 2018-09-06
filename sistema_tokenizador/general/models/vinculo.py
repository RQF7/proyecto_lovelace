"""
  Modelo de usuarios,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from django.db import models

class Vinculo (models.Model):
  """Representación de un vinculo dentro del sistema."""

  vinculo = models.CharField(
    verbose_name = 'vinculo',
    max_length = 100)

  fecha = models.DateField(
    verbose_name = 'fecha del vinculo')

  def __str__(self):
    """Representación en cadena de un vinculo."""
    return str(self.id) + ' - ' + self.vinculo + ' - ' + self.fecha
