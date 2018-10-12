"""
direcciones.py Configuración de urls del sistema.
Tienda en línea.
Proyecto Lovelace.

Documentación asociada:
https://docs.djangoproject.com/en/2.0/topics/http/urls/
"""

import django
import tienda.general as general

urlpatterns = [

  # Operaciones de módulo general
  django.urls.path('api/tienda/',
    django.urls.include(
      'tienda.tienda.direcciones')),

  # Operaciones de módulo general
  django.urls.path('api/libreria/',
    django.urls.include(
      'tienda.libreria.direcciones')),

  # URLs estáticas
  django.urls.path('',
    general.funciones.inicio),
  django.urls.path('carrito',
    general.funciones.inicio),
  django.urls.path('cuenta',
    general.funciones.inicio),
  django.urls.path('libro/<int:idDeLibro>',
    general.funciones.inicio),

]

# Excepción para reglas de import.
# Sin este import hay un error al llamar a la función de más abajo. Aún y
# cuando tiene el path completo.
from django.contrib.staticfiles.urls import staticfiles_urlpatterns
urlpatterns += django.contrib.staticfiles.urls.staticfiles_urlpatterns()
