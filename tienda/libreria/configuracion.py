"""
configuracion.py Clase de configuración para módulo de la librería.
Caso de pruebas.
Proyecto Loevlace.
"""

import django

class Configuracion(django.apps.AppConfig):
  """Clase de configuración para la app de la librería."""
  name = 'tienda.libreria'
  verbose_name = 'Módulo correspondiente a la librería'
