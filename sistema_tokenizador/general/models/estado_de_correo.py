"""
  Modelo de estados de usuario,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from django.db import models

class EstadoDeCorreo (models.Model):
  """
  Catálogo de estados de correo.

  Los estados son «verificado», «no verificado».
  """

  nombre = models.CharField(
    verbose_name = 'nombre del estado de correo',
    unique = True,
    max_length = 50)


  def __str__(self):
    """Representación en cadena de un estado del correo."""
    return str(self.id) + ' - ' + self.nombre
