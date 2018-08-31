"""
  Modelo de contador para programa tokenizador,
  Aplicación web de sistena tokenizador.
  Proyecto Lovelace.
"""

from django.db import models

class Contador (models.Model):
  """
  Estado interno para TKR

  TKR utiliza una tupla de esta tabla para almacenar el estado interno
  de la función RN. El registro se crea en «/datos_base.py».
  """

  nombre = models.CharField(
    verbose_name = 'nombre del contador',
    unique = True,
    max_length = 100)

  valor = models.BigIntegerField(
    verbose_name = 'valor del contador')


  def __str__(self):
    """Representación en cadena de un contador."""
    return str(self.id) + ' - ' + self.nombre + ' - ' + str(self.valor)
