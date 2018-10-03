"""
  Modelo de caso de prueba,
  Tienda en linea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django
from .tarjeta import Tarjeta
from .usuario import Usuario

class Compra (django.db.models.Model):
  """
  Compra de libros
  """

  fecha = django.db.models.DateField(
    verbose_name = 'fecha de la compra')

  tarjeta = django.db.models.ForeignKey('Tarjeta',
    django.db.models.PROTECT,
    verbose_name = 'tarjeta con la que se hizo la compra',
    null = True)

  usuario = django.db.models.ForeignKey('Usuario',
    django.db.models.PROTECT,
    verbose_name = 'el usuario que hizo la compra',
    null = True)

  def __str__(self):
    """Representación en cadena de la compra."""
    return str(self.usuario)
    + ' - ' + str(self.tarjeta)
    + ' - ' + str(self.fecha)
