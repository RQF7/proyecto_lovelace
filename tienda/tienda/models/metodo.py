"""
  Modelo de caso de prueba,
  Tienda en linea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django

class Metodo (django.db.models.Model):
  """
  Catálogo de métodos de tokenización:
  FFX, BPS, TKR, AHR y DRBG.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'metodo con el que se tokenizó una tarjeta',
    max_length = 20,
    primary_key = True)

  def __str__(self):
    """Representación en cadena del método de tokenización."""
    return self.nombre
