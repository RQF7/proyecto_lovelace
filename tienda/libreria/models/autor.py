"""
  Modelo de caso de prueba,
  Tienda en linea, módulo de la librería.
  Proyecto Lovelace.
"""

import django

class Autor (django.db.models.Model):
  """
  Autor de un libro.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'autor de un libro',
    max_length = 100,
    unique = True)

  def __str__(self):
    """Representación en cadena de un autor de libros."""
    return self.nombre
