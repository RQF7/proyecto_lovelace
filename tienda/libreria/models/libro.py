"""
  Modelo de caso de prueba,
  Tienda en linea, módulo de la librería.
  Proyecto Lovelace.
"""

import django
from .autor     import Autor
from .genero    import Genero
from .editorial import Editorial

class Libro (django.db.models.Model):
  """
  Un libro.
  """

  titulo = django.db.models.CharField(
    verbose_name = 'titulo de un libro',
    max_length = 100)

  autor = django.db.models.ManyToManyField(Autor)

  esEditor = django.db.models.BooleanField(
    verbose_name = 'Bandera para saber si el autor en verdad es un editor')

  genero = django.db.models.ForeignKey('Genero',
    django.db.models.PROTECT,
    verbose_name = 'genero del libro',
    null = True)

  editorial = django.db.models.ForeignKey('Editorial',
    django.db.models.PROTECT,
    verbose_name = 'editorial del libro',
    null = True)

  edicion = django.db.models.PositiveIntegerField(
    verbose_name = 'número de edición del libro',
    default = 1)

  anio = django.db.models.PositiveIntegerField(
    verbose_name = 'año de publicación')

  paginas = django.db.models.PositiveIntegerField(
    verbose_name = 'número de paginas del libro')

  existencias = django.db.models.PositiveIntegerField(
    verbose_name = 'número de libros que se tienen',
    default = 1)

  precio = django.db.models.DecimalField(
    verbose_name = 'precio del libro',
    decimal_places = 2,
    max_digits = 6)

  oferta = django.db.models.CharField(
    verbose_name = 'descripción alguna oferta sobre el libro',
    max_length = 1000)

  def __str__(self):
    """Representación en cadena de un autor de libros."""
    return self.nombre
