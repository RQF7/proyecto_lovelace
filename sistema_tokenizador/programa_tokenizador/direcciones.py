"""
Configuración de URL de módulo de programa tokenizador.
Aplicación web de sistema tokenizador.
Proyecto Lovelace.
"""

import django

from ..programa_tokenizador import funciones_web

urlpatterns = [

  django.urls.path('tokenizar',
    funciones_web.tokenizar),
  django.urls.path('detokenizar',
    funciones_web.detokenizar),
  django.urls.path('retokenizar',
    funciones_web.retokenizar)

]
