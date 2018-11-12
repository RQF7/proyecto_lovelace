"""
  Modelo de estados de usuario,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import django

class EstadoDeUsuario (django.db.models.Model):
  """
  Catálogo de estados de usuario.

  Solamente le aplica a los usuarios de tipo cliente. Alunos de
  ellos son «en lista negra», «aprobado», «sin verificar», etc.
  """

  nombre = django.db.models.CharField(
    verbose_name = 'nombre del estado de usuario',
    unique = True,
    max_length = 100,
    primary_key = True)


  def __str__(self):
    """Representación en cadena de un estado de usuario."""
    return self.nombre
