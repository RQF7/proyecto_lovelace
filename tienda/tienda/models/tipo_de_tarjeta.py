"""
  Modelo de caso de prueba,
  Tienda en línea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django

class TipoDeTarjeta (django.db.models.Model):
  """
  Catálogo de tipos de tarjeta.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'catálogo de tipos de tarjeta',
    max_length = 50,
    primary_key = True)

  def __str__(self):
    """Representación en cadena de un tipo de tarjeta."""
    return self.nombre
