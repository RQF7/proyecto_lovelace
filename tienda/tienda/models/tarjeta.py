"""
  Modelo de caso de prueba,
  Tienda en línea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django
from .emisor import Emisor
from .direccion import Direccion
from .tipo_de_tarjeta import TipoDeTarjeta

class Tarjeta (django.db.models.Model):
  """
  Una tarjeta bancaria.
  """

  token = django.db.models.CharField(
    verbose_name = 'token de la tarjeta',
    max_length = 20)

  terminacion = django.db.models.CharField(
    verbose_name = 'terminación de el número de la tarjeta',
    max_length = 4)

  metodo = django.db.models.ForeignKey('Metodo',
    django.db.models.PROTECT,
    verbose_name = 'método con el que se generó el token',
    null = True)

  emisor = django.db.models.ForeignKey('Emisor',
    django.db.models.PROTECT,
    verbose_name = 'emisor de la tarjeta',
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

  tipo_de_tarjeta = django.db.models.ForeignKey('TipoDeTarjeta',
    django.db.models.PROTECT,
    verbose_name = 'tipo de tarjeta',
    null = True)

  activa = django.db.models.BooleanField(
    verbose_name = 'bandera para saber si la tarjeta esta activa o inactiva')

  def __str__(self):
    """Representación en cadena de una tarjeta."""
    return str(self.token) + '(' + str(self.metodo) + ')'
