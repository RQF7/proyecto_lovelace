"""
  Modelo de usuarios,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import django

class Vinculo (django.db.models.Model):
  """Representación de un vinculo dentro del sistema."""

  vinculo = django.db.models.CharField(
    verbose_name = 'vinculo',
    max_length = 100,
    unique = True)

  fecha = django.db.models.DateTimeField(
    verbose_name = 'fecha del vinculo')

  def __str__(self):
    """Representación en cadena de un vinculo."""
    return str(self.id) + ' - ' + self.vinculo + ' - ' + self.fecha
