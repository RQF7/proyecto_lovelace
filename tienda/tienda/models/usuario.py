"""
  Modelo de caso de prueba,
  Tienda en línea, módulo de la tienda.
  Proyecto Lovelace.
"""

import django
from .tarjeta import Tarjeta
from .direccion import Direccion

class Usuario (django.db.models.Model):
  """
  Descripción
  """

  nombre = django.db.models.CharField(
    verbose_name = 'nombre del usuario',
    max_length = 100)

  telefono = django.db.models.CharField(
    verbose_name = 'teléfono del usuario',
    max_length = 14)

  correo = django.db.models.CharField(
    verbose_name = 'correo electrónico',
    primary_key = True,
    max_length = 100)

  contrasenia = django.db.models.BinaryField(
    verbose_name = 'hash de contraseña')

  tarjeta = django.db.models.ManyToManyField(Tarjeta)

  direccion = django.db.models.ManyToManyField(Direccion)

  def __str__(self):
    """Representación en cadena de un tipo de ... ."""
    return self.nombre
