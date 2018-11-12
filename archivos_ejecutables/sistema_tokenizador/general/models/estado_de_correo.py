"""
  Modelo de estados de usuario,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import django

class EstadoDeCorreo (django.db.models.Model):
  """
  Catálogo de estados de correo.

  Los estados son «verificado», «no verificado».
  """

  nombre = django.db.models.CharField(
    verbose_name = 'nombre del estado de correo',
    unique = True,
    max_length = 50,
    primary_key = True)


  def __str__(self):
    """Representación en cadena de un estado del correo."""
    return self.nombre
