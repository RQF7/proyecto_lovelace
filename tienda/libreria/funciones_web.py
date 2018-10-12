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
      'existencias': libro.existencias,
      'autor': autores})
  return django.http.HttpResponse(json.dumps(lista))


def operarLibro (peticion, idDeLibro):
  """Índice de métodos para el recurso libro."""
  if peticion.method == 'GET':
    return obtenerLibro(peticion, idDeLibro)
  else:
    return django.http.HttpResponseNotAllowed()


def obtenerLibro (peticion, idDeLibro):
  """Regresa los datos completos del libro dado.

  A diferencia de «obtenerLibros», aquí se regresan casi todos los campos
  del modelo. También aquí se tiene que hacer una serialización manual (vía
  diccionario)."""
  libro = Libro.objects.get(pk = idDeLibro)
  autores = []
  for autor in libro.autor.all():
    autores.append(autor.nombre)
  return django.http.HttpResponse(json.dumps({
    'pk': libro.pk,
    'titulo': libro.titulo,
    'precio': str(libro.precio),
    'foto': str(libro.foto),
    'existencias': libro.existencias,
    'genero': libro.genero.nombre,
    'editorial': libro.editorial.nombre,
    'edicion': libro.edicion,
    'anio': libro.anio,
    'paginas': libro.paginas,
    'autor': autores}))


def obtenerTotalDeLibros (peticion):
  """Regresa el total de libros en la base de datos."""
  todos = Libro.objects.all().count()
  return django.http.HttpResponse(str(todos))
