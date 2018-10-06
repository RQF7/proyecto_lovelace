"""
  Modelo de caso de prueba,
  Tienda en línea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django
from .estado import Estado
from .tipo_de_direccion import TipoDeDireccion

class Direccion (django.db.models.Model):
  """
  Una dirección (ubicación).
  """

  tipoDeDireccion = django.db.models.ForeignKey('TipoDeDireccion',
    django.db.models.PROTECT,
    verbose_name = 'tipo de dirección (punto de entrega | facturación)',
    null = True)

  estado = django.db.models.ForeignKey('Estado',
    django.db.models.PROTECT,
    verbose_name = 'estado de la dirección',
    null = True)

  municipio = django.db.models.CharField(
    verbose_name = 'nombre del municipio de la dirección',
    max_length = 100)

  colonia = django.db.models.CharField(
    verbose_name = 'nombre de la colonia de la dirección',
    max_length = 100)

  calle = django.db.models.CharField(
    verbose_name = 'nombre de la calle de la dirección',
    max_length = 100)

  numeroInterior = django.db.models.CharField(
    verbose_name = 'número interior de la calle de la dirección',
    max_length = 5)

  numeroExterior = django.db.models.CharField(
    verbose_name = 'número exterior de la calle de la dirección',
    max_length = 5)

  cp = django.db.models.CharField(
    verbose_name = 'código postal',
    max_length = 8)

  activa = django.db.models.BooleanField(
    verbose_name = 'bandera para saber si la dirección esta activa o inactiva')

  def __str__(self):
    """Representación en cadena de una dirección."""
    return str(self.calle) + ', N. int. '
    + self.numero_interior + ', N. ext. '
    + self.numero_exterior + ', '
    + self.estado + ', CP ' + self.cp