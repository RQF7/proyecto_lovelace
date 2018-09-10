"""
  Modelo de usuarios,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from .estado_de_correo import EstadoDeCorreo
from .vinculo import Vinculo
from django.db import models

class Correo (models.Model):
  """
  Representación de un correo dentro del sistema.

  OJO: la llave primaria es el mismo correo. Esto implica que al intentar
  insertar un correo duplicado, lo que pasa en realidad es una actualización del
  campo ya existente.
  """

  correo = models.CharField(
    verbose_name = 'correo electrónico',
    unique = True,
    max_length = 100,
    primary_key = True)

  contrasenia = models.BinaryField(
    verbose_name = 'Hash de contraseña')

  estadoDeCorreo = models.ForeignKey(
    'EstadoDeCorreo',
    models.PROTECT,
    verbose_name = 'estado del correo')

  vinculo = models.ForeignKey(
    'Vinculo',
    models.PROTECT,
    verbose_name = 'vinculo',
    null = True)


  def __str__(self):
    """Representación en cadena de un correo."""
    return self.correo
