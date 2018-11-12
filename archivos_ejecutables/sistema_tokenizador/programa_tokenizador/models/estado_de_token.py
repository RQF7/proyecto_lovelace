"""
  Modelo de estados de un token,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import django

class EstadoDeToken (django.db.models.Model):
  """
  Catálogo de estados de token.

  * Actual
  * Anterior
  * Retokenizado
  """

  nombre = django.db.models.CharField(
    verbose_name = 'nombre del estado del token',
    unique = True,
    max_length = 100,
    primary_key = True)


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return self.nombre
