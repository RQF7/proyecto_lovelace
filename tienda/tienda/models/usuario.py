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
  Un usuario de la tienda.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'nombre del usuario',
    max_length = 100)

  correo = django.db.models.CharField(
    verbose_name = 'correo electrónico',
    primary_key = True,
    max_length = 100)

  contrasenia = django.db.models.BinaryField(
    verbose_name = 'hash de contraseña')

  verificado = django.db.models.BooleanField(
    verbose_name = 'bandera para saber si el usuario esta verificado')

  tarjeta = django.db.models.ManyToManyField(
    Tarjeta,
    blank = True)

  direccion = django.db.models.ManyToManyField(
    Direccion,
    blank = True)

  vinculo = django.db.models.CharField(
    verbose_name = 'vinculo de verificación',
    max_length = 100,
    unique = True,
    null = True)

  fecha = django.db.models.DateTimeField(
    verbose_name = 'fecha de creación del vinculo')

  def __str__(self):
    """Representación en cadena de un usuario."""
    return self.nombre
