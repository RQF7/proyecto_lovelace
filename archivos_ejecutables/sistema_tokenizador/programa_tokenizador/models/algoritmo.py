"""
  Modelo de algoritmos tokenizadores,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import django
from .tipo_de_algoritmo import TipoDeAlgoritmo

class Algoritmo (django.db.models.Model):
  """
  Catálogo de algoritmos tokenizadores.

  * FFX
  * BPS
  * TKR
  * DRBG
  * AHR
  """

  nombre = django.db.models.CharField(
    verbose_name = 'nombre del algoritmo',
    unique = True,
    max_length = 20,
    primary_key = True)

  longitudDeLlave = django.db.models.IntegerField(
    verbose_name = 'Longitud de las llaves para este algoritmo')

  tipoDeAlgoritmo = django.db.models.ForeignKey(
    'TipoDeAlgoritmo',
    django.db.models.PROTECT,
    verbose_name = 'clasificación del algoritmo')


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return self.nombre
