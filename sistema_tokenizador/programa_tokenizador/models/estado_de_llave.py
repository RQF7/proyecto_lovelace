"""
  Modelo de estados de una llave,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from django.db import models

class EstadoDeLlave (models.Model):
  """
  Catálogo de estados de llave.

  * Actual
  * Anterior
  """

  nombre = models.CharField(
    verbose_name = 'nombre del estado de la llave',
    unique = True,
    max_length = 100,
    primary_key = True)


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return self.nombre
