"""
  funciones.py Definición de funciones externas de módulo de programa
  tokenizador.
  Proyecto Lovelace.
"""

from django.http import HttpResponse
from django.shortcuts import render

def hola_mundo(peticion):
  """Prueba inicial de configuración de servidor."""
  return HttpResponse("¡Hola mundo!")
