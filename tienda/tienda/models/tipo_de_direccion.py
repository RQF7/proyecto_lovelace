"""
  Modelo de caso de prueba,
  Tienda en linea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django

class TipoDeDireccion (django.db.models.Model):
  """
  Catalogo de tipos de dirección, se tienen:
  "punto de entrega": las direcciones asociadas a usuarios.
  "facturación": las asociadas a una tarjeta bancaria.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'catálogo de tipos de dirección',
    max_length = 50,
    unique = True)

  def __str__(self):
    """Representación en cadena de un tipo de dirección."""
    return self.nombre
