"""
configuracion.py Clase de configuración para módulo general.
Tienda en línea.
Proyecto Loevlace.
"""

import django

class Configuracion(django.apps.AppConfig):
  """Clase de configuración para aplicación general."""
  name = 'tienda.general'
  verbose_name = 'Módulo de funciones comunes'
