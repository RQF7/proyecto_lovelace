"""
  Modelo de caso de prueba,
  Tienda en línea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django
import tienda.libreria as libreria
from .compra import Compra

class Paquete (django.db.models.Model):
  """
  Paquetes pertenecientes a una compra.
  Realmente esta es una es una parte de compra y se puede ver
  como un conjunto de libros.
  Ya que la relación de compra tenía atributos propios y de N:M
  lo dividí en 2, compra y paquetes.
  """

  libro = django.db.models.ForeignKey('libreria.Libro',
    django.db.models.PROTECT,
    verbose_name = 'libro del pedido',
    null = True)

  compra = django.db.models.ForeignKey('Compra',
    django.db.models.PROTECT,
    verbose_name = 'compra a la que pertenece el pedido',
    null = True)

  numero = django.db.models.PositiveIntegerField(
    verbose_name = 'número de libro',
    default = 1)

  precio_unitario = django.db.models.DecimalField(
    verbose_name = 'precio del libro al momento',
    decimal_places = 2,
    max_digits = 6)

  def __str__(self):
    """Representación en cadena de un paquete."""
    return str(self.numero) + ' - ' + str(self.libro)