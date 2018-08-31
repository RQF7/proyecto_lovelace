"""
  Modelo de llave para algoritmos tokenizadores,
  Aplicación web de sistena tokenizador.
  Proyecto Lovelace.
"""

from .algoritmo import Algoritmo
from .estado_de_llave import EstadoDeLlave
from ...general.models.usuario import Usuario
from django.db import models
from django.utils import timezone

class Llave (models.Model):
  """
  """

  # OJO: es un char, no un campo binario: las llaves se almacenan codificadas
  # en base 64.
  llave = models.CharField(
    verbose_name = 'representación en base 64 de la llave',
    unique = True,
    max_length = 100)

  criptoperiodo = models.IntegerField(
    verbose_name = 'duración del criptoperiodo en días')

  fechaDeCreacion = models.DateTimeField(
    default = timezone.now,
    verbose_name = 'fecha de creación de la llave')

  algoritmo = models.ForeignKey(
    'Algoritmo',
    models.PROTECT,
    verbose_name = 'Algoritmo asociado')

  # Cuando se borra un usuario se borran sus llaves (models.CASCADE).
  usuario = models.ForeignKey(
    'general.Usuario',
    models.CASCADE,
    verbose_name = 'Usuario asociado a la llave')

  estadoDeLlave = models.ForeignKey(
    'EstadoDeLlave',
    models.PROTECT,
    verbose_name = 'Estado de la llave')
