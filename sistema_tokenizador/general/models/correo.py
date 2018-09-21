"""
  Modelo de usuarios,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import django
from .estado_de_correo import EstadoDeCorreo
from .vinculo import Vinculo

class Correo (django.db.models.Model):
  """
  Representación de un correo dentro del sistema.

  OJO: la llave primaria es el mismo correo. Esto implica que al intentar
  insertar un correo duplicado, lo que pasa en realidad es una actualización del
  campo ya existente.
  """

  correo = django.db.models.CharField(
    verbose_name = 'correo electrónico',
    unique = True,
    max_length = 100,
    primary_key = True)

  contrasenia = django.db.models.BinaryField(
    verbose_name = 'Hash de contraseña')

  estadoDeCorreo = django.db.models.ForeignKey(
    'EstadoDeCorreo',
    django.db.models.PROTECT,
    verbose_name = 'estado del correo')

  vinculo = django.db.models.ForeignKey(
    'Vinculo',
    django.db.models.PROTECT,
    verbose_name = 'vinculo',
    null = True)


  def __str__(self):
    """Representación en cadena de un correo."""
    return self.correo
