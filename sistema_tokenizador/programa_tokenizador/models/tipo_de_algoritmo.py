"""
  Modelo de clasificaciones de algoritmos tokenizadores,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import django

class TipoDeAlgoritmo (django.db.models.Model):
  """
  Catálogo de tipos de algoritmos tokenizadores.

  * Reversibles
  * Irreversibles
  """

  nombre = django.db.models.CharField(
    verbose_name = 'nombre del tipo de algoritmo',
    unique = True,
    max_length = 100,
    primary_key = True)


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return self.nombre
