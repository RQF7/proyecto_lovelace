"""
  Modelo de caso de prueba,
  Tienda en línea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django

class Estado (django.db.models.Model):
  """
  Catálogo con los estados de México.
  Estado de una dirección.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'estado (ubicación) de una dirección',
    max_length = 100,
    primary_key = True)

  def __str__(self):
    """Representación en cadena de un estado."""
    return self.nombre
