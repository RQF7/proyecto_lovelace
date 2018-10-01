"""
configuracion.py Clase de configuración para módulo de la tienda.
Caso de pruebas.
Proyecto Loevlace.
"""

import django

class Configuracion(django.apps.AppConfig):
  """Clase de configuración para la app de la tienda."""
  name = 'tienda.tienda'
  verbose_name = 'Módulo correspondiente a la tienda'
