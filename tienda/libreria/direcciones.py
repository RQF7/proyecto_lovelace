"""
Configuración de URL de módulo de librería.
Tienda en línea.
Proyecto Lovelace.
"""

import django

from ..libreria import funciones_web

urlpatterns = [

  django.urls.path('libros/<int:pagina>/<int:limite>',
    funciones_web.obtenerLibros),
  django.urls.path('total_de_libros',
    funciones_web.obtenerTotalDeLibros)

]
