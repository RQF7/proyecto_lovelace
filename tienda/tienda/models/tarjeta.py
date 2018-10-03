"""
  Modelo de caso de prueba,
  Tienda en linea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django
from .direccion import Direccion

class Tarjeta (django.db.models.Model):
  """
  Un tarjeta bancaria.
  """

  token = django.db.models.CharField(
    verbose_name = 'token de la tarjeta',
    max_length = 20)

  terminacion = django.db.models.CharField(
    verbose_name = 'terminación de el número de la tarjeta',
    max_length = 4)

  metodo = django.db.models.ForeignKey('Metodo',
    django.db.models.PROTECT,
    verbose_name = 'método con el que se genero el token',
    null = True)

  titular = django.db.models.CharField(
    verbose_name = 'titular de la tarjeta',
    max_length = 100)

  direccion = django.db.models.ForeignKey('Direccion',
    django.db.models.PROTECT,
    verbose_name = 'dirección asociada a la tarjeta',
    null = True)

  expiracion = django.db.models.DateField(
    verbose_name = 'fecha de expiración de la tarjeta')

  def __str__(self):
    """Representación en cadena de una tarjeta."""
    return str(self.token) + '(' + str(self.metodo) + ')'
