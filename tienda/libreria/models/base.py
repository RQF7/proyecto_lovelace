"""
  Modelo de caso de prueba,
  Tienda en linea, módulo de la librería.
  Proyecto Lovelace.
"""

import django

class BaseL (django.db.models.Model):
  """
  Descripción
  """

  nombre = django.db.models.CharField(
    verbose_name = 'nombre',
    max_length = 20)

  attr = django.db.models.IntegerField(
    verbose_name = 'attr')

  def __str__(self):
    """Representación en cadena de un tipo de ... ."""
    return self.nombre
