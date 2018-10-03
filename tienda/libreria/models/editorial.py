"""
  Modelo de caso de prueba,
  Tienda en linea, módulo de la librería.
  Proyecto Lovelace.
"""

import django

class Editorial (django.db.models.Model):
  """
  Editorial de un libro.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'editorial de un libro',
    max_length = 100,
    primary_key = True)

  def __str__(self):
    """Representación en cadena de una editorial."""
    return self.nombre
