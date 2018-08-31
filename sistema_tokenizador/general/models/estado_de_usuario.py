"""
  Modelo de estados de usuario,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from django.db import models

class EstadoDeUsuario (models.Model):
  """
  Catálogo de estados de usuario.

  Solamente le aplica a los usuarios de tipo cliente. Alunos de
  ellos son «en lista negra», «aprobado», «sin verificar», etc.
  """

  nombre = models.CharField(
    verbose_name = 'nombre del estado de usuario',
    unique = True,
    max_length = 100)


  def __str__(self):
    """Representación en cadena de un tipo de usuario."""
    return str(self.id) + ' - ' + self.nombre
