"""
  Proyecto Lovelace
  Caso de pruebas
  Estado inicial de base de datos.
  Catálogos de la tienda en línea.
"""

import os, sys, django

sys.path.append(os.path.dirname(os.path.realpath(__file__)) + '/../')
os.environ['DJANGO_SETTINGS_MODULE'] = 'tienda.configuraciones'
django.setup()

from tienda.libreria.models.libro     import Libro
from tienda.libreria.models.autor     import Autor
from tienda.libreria.models.genero    import Genero
from tienda.libreria.models.editorial import Editorial

def guardar_libros(libros):
  """Guarda los libros dados omitiendo errores y creando
  sus editoriales, generos y autores."""
  for [libro, autores] in libros:

    try:
      Genero.objects.get(nombre = str(libro.genero))
    except:
      Genero(nombre = str(libro.genero)).save()
      libro.genero = Genero.objects.get(nombre = str(libro.genero))
      print('Genero "' + str(libro.genero) + '" creado')

    try:
      Editorial.objects.get(nombre = str(libro.editorial))
    except:
      Editorial(nombre = str(libro.editorial)).save()
      libro.editorial = Editorial.objects.get(nombre = str(libro.editorial))
      print('Editorial "' + str(libro.editorial) + '" creada')

    try:
      libro.save()
    except django.db.utils.IntegrityError:
      print('Error en el libro: ' + str(libro))

    for autor in autores:
      try:
        Autor.objects.get(nombre = autor)
      except:
        Autor(nombre = autor).save()
        print('Autor "' + autor + '" creado')
      libro = Libro.objects.get(titulo = str(libro.titulo))
      libro.autor.add(Autor.objects.get(nombre = autor))


if __name__ == '__main__':

  libros = [
    [Libro(
      titulo = '20 poemas de amor y una canción desesperada · Antología Nerudiana',
      editorial = Editorial('ED PORRUA (MEXICO)'),
      genero = Genero('Literatura y estudios literarios'),
      precio = 75,
      anio = 2018,
      paginas = 256,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["Pablo Neruda"]],
    [Libro(
      titulo = 'El libro tachado',
      editorial = Editorial('TURNER DE MEXICO'),
      genero = Genero('Literatura y estudios literarios'),
      precio = 365,
      anio = 2014,
      paginas = 312,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["PATRICIO PRON"]],
    [Libro(
      titulo = 'El esclavo',
      editorial = Editorial('CAMINO ROJO'),
      genero = Genero('Ficción y temas afines'),
      precio = 59,
      anio = 2013,
      paginas = 156,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["Swami Anand Dilvar"]],
    [Libro(
      titulo = 'PEDRO PÁRAMO',
      editorial = Editorial('RM'),
      genero = Genero('Ficción y temas afines'),
      precio = 125,
      paginas = 132,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["Juan Rulfo"]],
    [Libro(
      titulo = 'Pequeño país',
      editorial = Editorial('Salamandra'),
      genero = Genero('Ficción y temas afines'),
      precio = 390,
      anio = 2018,
      paginas = 224,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["Gaël Faye"]],
    [Libro(
      titulo = 'Cuentos de buenas noches para niñas rebeldes',
      editorial = Editorial('Planeta'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 228,
      anio = 2017,
      paginas = 224,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["Elena Favilli"]],
    [Libro(
      titulo = 'Vivir bien la vida',
      editorial = Editorial('Salamandra'),
      genero = Genero('Salud y desarrollo personal'),
      precio = 235,
      anio = 2018,
      paginas = 84,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["J. K. Rowling"]],
    [Libro(
      titulo = 'Las batallas en el desierto',
      editorial = Editorial('Ediciones Era'),
      genero = Genero('Ficción y temas afines'),
      precio = 125,
      anio = 2013,
      paginas = 72,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["José Emilio Pacheco"]],
    [Libro(
      titulo = 'Los hornos de Hitler',
      editorial = Editorial('BOOKET'),
      genero = Genero('Humanidades'),
      precio = 118,
      anio = 2014,
      paginas = 236,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["Olga Lengyel"]],
    [Libro(
      titulo = 'MINDFULNESS PARA PRINCIPIANTES C/CD',
      editorial = Editorial('KAIROS'),
      precio = 400,
      paginas = 212,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["JON KABAT ZINN"]],
    [Libro(
      titulo = 'Momo',
      editorial = Editorial('Loqueleo'),
      genero = Genero('Ficción y temas afines'),
      precio = 159,
      anio = 2017,
      paginas = 256,
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ["Michael Ende"]]]

  guardar_libros(libros)
