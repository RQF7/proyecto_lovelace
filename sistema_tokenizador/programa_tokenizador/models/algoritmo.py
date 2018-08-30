"""
  Modelo de algoritmos tokenizadores,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from .tipo_de_algoritmo import TipoDeAlgoritmo
from django.db import models

class Algoritmo (models.Model):
  """
  Catálogo de algoritmos tokenizadores.

  * FFX
  * BPS
  * TKR
  * DRBG
  * AHR
  """

  nombre = models.CharField(
    verbose_name = 'nombre del algoritmo',
    unique = True,
    max_length = 20)

  longitudDeLlave = models.IntegerField(
    verbose_name = 'Longitud de las llaves para este algoritmo')

  tipoDeAlgoritmo = models.ForeignKey(
    'TipoDeAlgoritmo',
    models.PROTECT,
    verbose_name = 'clasificación del algoritmo')


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return str(self.id) + ' - ' + self.nombre
