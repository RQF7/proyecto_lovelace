"""
  Modelo de llave para algoritmos tokenizadores,
  Aplicación web de sistena tokenizador.
  Proyecto Lovelace.
"""

import django
import sistema_tokenizador.general as general

from .algoritmo import Algoritmo
from .estado_de_llave import EstadoDeLlave


class Llave (django.db.models.Model):
  """
  """

  # OJO: es un char, no un campo binario: las llaves se almacenan codificadas
  # en base 64.
  llave = django.db.models.CharField(
    verbose_name = 'representación en base 64 de la llave',
    unique = True,
    max_length = 100)

  criptoperiodo = django.db.models.IntegerField(
    verbose_name = 'duración del criptoperiodo en días')

  fechaDeCreacion = django.db.models.DateTimeField(
    default = django.utils.timezone.now,
    verbose_name = 'fecha de creación de la llave')

  algoritmo = django.db.models.ForeignKey(
    'Algoritmo',
    django.db.models.PROTECT,
    verbose_name = 'Algoritmo asociado')

  # Cuando se borra un usuario se borran sus llaves (models.CASCADE).
  usuario = django.db.models.ForeignKey(
    'general.Usuario',
    django.db.models.CASCADE,
    verbose_name = 'Usuario asociado a la llave')

  estadoDeLlave = django.db.models.ForeignKey(
    'EstadoDeLlave',
    django.db.models.PROTECT,
    verbose_name = 'Estado de la llave')
