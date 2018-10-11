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

  Regresa el rango solicitado de los libros de la base de datos. La
  serialización se hace de forma manual: se arma un arreglo de diccionarios
  con el formato requerido por el cliente; los serializadores de django
  no soportan objetos identados, y manejar un «catálogo de autores» puede
  resultar muy caro en una base de datos muy grande.

  TODO:
    * El nombre del campo debería ser «autores», no «autor».
    * Buscar un serializador de modelos de django que funcione
      con llaves foráneas"""
  todos = Libro.objects.all()
  lista = []
  for libro in todos[(pagina - 1) * limite : pagina * limite]:
    autores = []
    for autor in libro.autor.all():
      autores.append(autor.nombre)
    lista.append({
      'pk': libro.pk,
      'titulo': libro.titulo,
      'precio': str(libro.precio),
      'foto': str(libro.foto),
      'autor': autores})
  return django.http.HttpResponse(json.dumps(lista))


def obtenerTotalDeLibros (peticion):
  """Regresa el total de libros en la base de datos."""
  todos = Libro.objects.all().count()
  return django.http.HttpResponse(str(todos))
