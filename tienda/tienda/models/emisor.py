"""
  Modelo de caso de prueba,
  Tienda en línea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django

class Emisor (django.db.models.Model):
  """
  Catálogo de emisores de tarjetas.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'catálogo de emisores de tarjetas',
    max_length = 50,
    primary_key = True)

  def __str__(self):
    """Representación en cadena de un emisor de tarjetas."""
    return self.nombre
