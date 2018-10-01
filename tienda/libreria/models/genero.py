"""
  Modelo de caso de prueba,
  Tienda en linea, módulo de la librería.
  Proyecto Lovelace.
"""

import django

class Genero (django.db.models.Model):
  """
  Género de un libro.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'género de un libro',
    max_length = 50,
    unique = True)

  def __str__(self):
    """Representación en cadena de un género."""
    return self.nombre
