"""
  configuracion.py Clase de configuración para módulo general.
  Proyecto Loevlace.
"""

import django

class Configuracion(django.apps.AppConfig):
  """Clase de configuración para aplicación general."""
  name = 'sistema_tokenizador.general'
  verbose_name = 'Módulo de funciones comunes'
