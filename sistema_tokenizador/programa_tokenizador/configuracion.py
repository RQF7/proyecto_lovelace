"""
  configuracion.py Clase de configuración para módulo de programa tokenizador.
  Proyecto Loevlace.
"""

from django.apps import AppConfig

class Configuracion(AppConfig):
  """Clase de configuración para aplicación general."""
  name = 'sistema_tokenizador.programa_tokenizador'
  verbose_name = 'Módulo que interactúa con programa generador de tokens'
