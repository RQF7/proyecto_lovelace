"""
direcciones.py Configuración de urls del sistema.
Sistema tokenizador.
Proyecto Lovelace.

Documentación asociada:
https://docs.djangoproject.com/en/2.0/topics/http/urls/

Todas las URLs pasan por esta configuración. Las de vistas (las que en
algún momento aparecen en la basa de url del navegador) se concentran en
una sola función de python: general.inicio.

En realidad es el módulo de angular ngRoute (en el cliente) el que se
encarga de hacer la resolución (ver js/navegacion.configuracion.js).
"""

import django
import sistema_tokenizador.general as general

urlpatterns = [

  # Operaciones de módulo general
  django.urls.path('api/general/',
    django.urls.include(
      'sistema_tokenizador.general.direcciones')),

  # Operaciones de programa tokenizador
  django.urls.path('api/programa_tokenizador/',
    django.urls.include(
      'sistema_tokenizador.programa_tokenizador.direcciones')),

  # URLs estáticas
  django.urls.path('', general.funciones.inicio, name = 'inicio'),
  django.urls.path('documentación', general.funciones.inicio),
  django.urls.path('control', general.funciones.control),
  django.urls.path('administración', general.funciones.administracion),

]

# Excepción para reglas de import.
# Sin este import hay un error al llamar a la función de más abajo. Aún y
# cuando tiene el path completo.
from django.contrib.staticfiles.urls import staticfiles_urlpatterns
urlpatterns += django.contrib.staticfiles.urls.staticfiles_urlpatterns()
