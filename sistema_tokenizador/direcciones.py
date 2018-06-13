"""
  direcciones.py Configuración de urls del sistema.
  Proyecto Lovelace

  Documentación asociada:
  https://docs.djangoproject.com/en/2.0/topics/http/urls/

  Todas las URLs pasan por esta configuración. Las de vistas (las que en
  algún momento aparecen en la basa de url del navegador) se concentran en
  una sola función de python: general.inicio.

  En realidad es el módulo de angular ngRoute (en el cliente) el que se
  encarga de hacer la resolución (ver js/navegacion.configuracion.js).
"""

from django.contrib import admin
from django.urls import path, include
from django.contrib.staticfiles.urls import staticfiles_urlpatterns

from .programa_tokenizador import funciones as programa_tokenizador

urlpatterns = [
  path('', programa_tokenizador.hola_mundo)
]

urlpatterns += staticfiles_urlpatterns()
