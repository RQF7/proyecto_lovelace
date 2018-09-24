"""
Configuración de URL de módulo de programa tokenizador.
Aplicación web de sistema tokenizador.
Proyecto Lovelace.
"""

import django

from ..programa_tokenizador import funciones

urlpatterns = [

  django.urls.path('tokenizar',
    funciones.tokenizar),
  django.urls.path('detokenizar',
    funciones.detokenizar),
  django.urls.path('retokenizar',
    funciones.retokenizar)

]
