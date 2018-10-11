"""
funciones.py Funciones para módulo de librería,
Tienda en línea.
Proyecto Lovelace.
"""

import django
import json

import tienda.utilidades as utilidades

from .models.libro import Libro


def obtenerLibros (peticion, pagina, limite):
  """Función de paginador para catálogo de libros.

  Regresa el rango solicitado de los libros de la base de datos."""
  todos = Libro.objects.all()
  return utilidades.respuestaJSON(
    todos[(pagina - 1) * limite : pagina * limite])


def obtenerTotalDeLibros (peticion):
  """Regresa el total de libros en la base de datos."""
  todos = Libro.objects.all().count()
  return django.http.HttpResponse(str(todos))
  
