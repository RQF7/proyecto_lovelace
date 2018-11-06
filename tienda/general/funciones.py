"""
funciones.py Funciones web generales.
Tienda en línea.
Proyecto Lovelace.
"""

import django

import tienda.configuraciones as configuraciones


def inicio (peticion, idDeLibro = ''):
  """Liga a archivo estático de página de inicio.

  Todas las urls de vistas principales pasan por aquí. index.html solamente
  contiene la aplicación de angular. Es el módulo de ngRoute, en el cliente,
  quien hace la resolución a un html en específico."""

  respuesta = open(\
    configuraciones.DIRECTORIO_BASE +
    'tienda/archivos_web/compilados/index.html', 'rb')
  return django.http.HttpResponse(content = respuesta)
