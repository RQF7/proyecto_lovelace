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
      foto = '9789700767567.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Pablo Neruda']],

  
    [Libro(
      titulo = 'Vivir bien la vida',
      editorial = Editorial('Salamandra'),
      genero = Genero('Salud y desarrollo personal'),
      precio = 235,
      anio = 2018,
      paginas = 84,
      foto = '9788498388435.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['J. K. Rowling']],

  
    [Libro(
      titulo = 'Pequeño país',
      editorial = Editorial('Salamandra'),
      genero = Genero('Ficción y temas afines'),
      precio = 390,
      anio = 2018,
      paginas = 224,
      foto = '9788498388350.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Gaël Faye']],

  
    [Libro(
      titulo = 'Los hornos de Hitler',
      editorial = Editorial('BOOKET'),
      genero = Genero('Humanidades'),
      precio = 118,
      anio = 2014,
      paginas = 236,
      foto = '9786070721786.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Olga Lengyel']],

  
    [Libro(
      titulo = 'El libro tachado',
      editorial = Editorial('TURNER DE MEXICO'),
      genero = Genero('Literatura y estudios literarios'),
      precio = 365,
      anio = 2014,
      paginas = 312,
      foto = '9788415832287.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['PATRICIO PRON']],

  
    [Libro(
      titulo = 'PEDRO PÁRAMO',
      editorial = Editorial('RM'),
      genero = Genero('Ficción y temas afines'),
      precio = 125,
      paginas = 132,
      foto = '9789685208550.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Juan Rulfo']],

  
    [Libro(
      titulo = 'Momo',
      editorial = Editorial('Loqueleo'),
      genero = Genero('Ficción y temas afines'),
      precio = 159,
      anio = 2017,
      paginas = 256,
      foto = '9786070133039.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Michael Ende']],

  
    [Libro(
      titulo = 'Cuentos de buenas noches para niñas rebeldes',
      editorial = Editorial('Planeta'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 228,
      anio = 2017,
      paginas = 224,
      foto = '9786070739798.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Elena Favilli']],

  
    [Libro(
      titulo = 'MINDFULNESS PARA PRINCIPIANTES C/CD',
      editorial = Editorial('KAIROS'),
      precio = 400,
      paginas = 212,
      foto = '9788499882390.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['JON KABAT ZINN']],

  
    [Libro(
      titulo = 'Las batallas en el desierto',
      editorial = Editorial('Ediciones Era'),
      genero = Genero('Ficción y temas afines'),
      precio = 125,
      anio = 2013,
      paginas = 72,
      foto = '9786074450552.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['José Emilio Pacheco']],

  
    [Libro(
      titulo = 'Casadas con el Imperio',
      editorial = Editorial('La Esfera de los Libros'),
      genero = Genero('Biografía e historias reales'),
      precio = 599,
      anio = 2018,
      paginas = 480,
      foto = '9788491642176.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Pilar Tejera Osuna']],

  
    [Libro(
      titulo = 'Chanoc',
      editorial = Editorial('Editorial Porrúa México'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 150,
      anio = 2018,
      paginas = 364,
      foto = '9786070930836.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Ángel Mora Suárez']],

  
    [Libro(
      titulo = 'CARTAS A TOMAS SEGOVIA',
      editorial = Editorial('FONDO D CUL ECONOMICA (ME)'),
      genero = Genero('Biografía e historias reales'),
      precio = 199,
      paginas = 200,
      foto = '9789681685751.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Octavio Paz']],

  
    [Libro(
      titulo = 'Un sol más vivo. Antología poética',
      editorial = Editorial('Ediciones Era'),
      genero = Genero('Literatura y estudios literarios'),
      precio = 289,
      anio = 2013,
      paginas = 336,
      foto = '9786074450156.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Octavio Paz']],

  
    [Libro(
      titulo = 'Lo mejor de Octavio Paz',
      editorial = Editorial('Booket'),
      genero = Genero('Literatura y estudios literarios'),
      precio = 198,
      anio = 2018,
      paginas = 392,
      foto = '9786070753558.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Octavio Paz']],

  
    [Libro(
      titulo = 'El esclavo',
      editorial = Editorial('CAMINO ROJO'),
      genero = Genero('Ficción y temas afines'),
      precio = 59,
      anio = 2013,
      paginas = 156,
      foto = '9789708070607.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Swami Anand Dilvar']],

  
    [Libro(
      titulo = 'LOS 43 DE IGUALA',
      editorial = Editorial('COLOFON'),
      genero = Genero('Sociedad y ciencias sociales'),
      precio = 225,
      paginas = 163,
      foto = '9789688678640.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['SERGIO GONZALEZ RODRIGUEZ']],

  
    [Libro(
      titulo = 'El artista adolescente que confundía el mundo con un cómic',
      editorial = Editorial('Literatura Random House'),
      genero = Genero('Ficción y temas afines'),
      precio = 209,
      anio = 2017,
      paginas = 190,
      foto = '9786073156486.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Sergio González Rodríguez']],

  
    [Libro(
      titulo = 'EL SENDERO DE LOS GATOS',
      editorial = Editorial('FONDO D CUL ECONOMICA (ME)'),
      genero = Genero('Ficción y temas afines'),
      precio = 60,
      paginas = 121,
      foto = '9789681642280.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['SERGIO GONZALEZ RODRIGUEZ']],

  
    [Libro(
      titulo = 'Charlie Parker: Tiempos oscuros',
      editorial = Editorial('Tusquets Editores México'),
      genero = Genero('Ficción y temas afines'),
      precio = 398,
      anio = 2018,
      paginas = 480,
      foto = '9786070750427.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['John Connolly']],

  
    [Libro(
      titulo = 'Infecciosa',
      editorial = Editorial('RANDOM HOUSE MONDADORI'),
      precio = 89,
      paginas = 200,
      foto = '9786074299175.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['SERGIO GONZALEZ RODRIGUEZ']],

  
    [Libro(
      titulo = 'Perfil asesino',
      editorial = Editorial('Tusquets Editores México'),
      precio = 139,
      paginas = 368,
      foto = '9786074213065.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['JOHN CONNOLLY']],

  
    [Libro(
      titulo = 'CAMINO BLANCO, EL',
      editorial = Editorial('Tusquets Editores México'),
      genero = Genero('Ficción y temas afines'),
      precio = 148,
      paginas = 464,
      foto = '7502268180911.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['JOHN CONNOLLY']],

  
    [Libro(
      titulo = 'PODER DE LAS TINIEBLAS, EL',
      editorial = Editorial('Tusquets Editores México'),
      precio = 199,
      paginas = 400,
      foto = '9786074217933.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['JOHN CONNOLLY']],

  
    [Libro(
      titulo = 'La sociedad literaria del pastel de piel de patata de Guernsey',
      editorial = Editorial('Salamandra'),
      genero = Genero('Ficción y temas afines'),
      precio = 390,
      anio = 2018,
      paginas = 304,
      foto = '9788498388770.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Annie / Shaffer Barrows']],

  
    [Libro(
      titulo = 'CUERVOS',
      editorial = Editorial('Tusquets Editores México'),
      precio = 55,
      paginas = 384,
      foto = '9786074214123.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['JOHN CONNOLLY']],

  
    [Libro(
      titulo = 'Insomnia',
      editorial = Editorial('Debolsillo'),
      genero = Genero('Ficción y temas afines'),
      precio = 399,
      anio = 2018,
      paginas = 896,
      foto = '9786073167871.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Stephen King']],

  
    [Libro(
      titulo = 'Mr Mercedes',
      editorial = Editorial('Debolsillo'),
      genero = Genero('Ficción y temas afines'),
      precio = 299,
      anio = 2016,
      paginas = 494,
      foto = '9786073146241.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Stephen King']],

  
    [Libro(
      titulo = 'Poesía completa',
      editorial = Editorial('Debolsillo'),
      genero = Genero('Literatura y estudios literarios'),
      precio = 299,
      anio = 2018,
      paginas = 472,
      foto = '9786073158862.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Alejandra Pizarnik']],

  
    [Libro(
      titulo = 'Pequeñas ideas antes de vivir en pareja',
      editorial = Editorial('Maeva Ediciones'),
      genero = Genero('Salud y desarrollo personal'),
      precio = 190,
      anio = 2018,
      paginas = 116,
      foto = '9788416363605.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Bom & Bon']],

  
    [Libro(
      titulo = 'Las nueve revelaciones',
      editorial = Editorial('Vergara'),
      genero = Genero('Salud y desarrollo personal'),
      precio = 299,
      anio = 2018,
      paginas = 320,
      foto = '9786073165761.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['James Redfield']],

  
    [Libro(
      titulo = 'Al Abordaje Pirata… ',
      editorial = Editorial('ICB Editores'),
      genero = Genero('Sociedad y ciencias sociales'),
      precio = 642,
      anio = 2017,
      paginas = 124,
      foto = '9788490214817.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Silvia Riera Caldado']],

  
    [Libro(
      titulo = 'Ciencia, tecnología, sociedad y valores',
      editorial = Editorial('Grupo Editorial Patria'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 225,
      anio = 2017,
      paginas = 136,
      foto = '9786077446101.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Francisco José Paoli Bolio']],

  
    [Libro(
      titulo = 'Las ciencias sociales',
      editorial = Editorial('TRILLAS'),
      precio = 66,
      paginas = 110,
      foto = '9789682437045.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Francisco José Paoli Bolio']],

  
    [Libro(
      titulo = 'Programación orientada a objetos con Java usando BlueJ',
      editorial = Editorial('Pearson Educación'),
      genero = Genero('Computación e informática'),
      precio = 720,
      anio = 2017,
      paginas = 666,
      foto = '9788490355312.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['David J. Barnes']],

  
    [Libro(
      titulo = 'Cómo programar en C++',
      editorial = Editorial('Pearson Educación'),
      genero = Genero('Computación e informática'),
      precio = 1150,
      anio = 2014,
      paginas = 720,
      foto = '9786073227391.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Paul J. Deitel']],

  
    [Libro(
      titulo = 'PROGRAMACION ORIENTADA A OBJETOS CON JAVA ',
      editorial = Editorial('PRENTICE HALL/PEARSON'),
      genero = Genero('Computación e informática'),
      precio = 406,
      paginas = 582,
      foto = '9788483223505.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['DAVID J. BARNES']],

  
    [Libro(
      titulo = 'E COMMERCE NEGOCIOS TECNOLOGIA SOCIEDAD',
      editorial = Editorial('PRENTICE HALL/PEARSON'),
      precio = 500,
      paginas = 899,
      foto = '9786074420494.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['KENNETH C. LAUDON']],

  
    [Libro(
      titulo = 'Sistemas de información gerencial',
      editorial = Editorial('Pearson Educación'),
      genero = Genero('Computación e informática'),
      precio = 510,
      anio = 2016,
      paginas = 680,
      foto = '9786073236966.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Jane P. / Laudon Laudon']],

  
    [Libro(
      titulo = 'El arte de la guerra',
      editorial = Editorial('Grupo Editorial Tomo'),
      genero = Genero('Sociedad y ciencias sociales'),
      precio = 55,
      anio = 2017,
      paginas = 156,
      foto = '9789706661630.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Sun Tzu']],

  
    [Libro(
      titulo = 'ESSENTIALS OF MANAGEMENT INFORMATION SYSTEMS',
      editorial = Editorial('PRENTICE HALL/PEARSON'),
      precio = 628,
      paginas = 481,
      foto = '9780136110996.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['KENNETH C. LAUDON']],

  
    [Libro(
      titulo = 'Temas de Física para bachilleratos tecnológicos',
      editorial = Editorial('Grupo Editorial Patria'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 225,
      anio = 2017,
      paginas = 216,
      foto = '9786077447153.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Héctor Pérez Montiel']],

  
    [Libro(
      titulo = 'El arte de escuchar',
      editorial = Editorial('Paidós'),
      genero = Genero('Sociedad y ciencias sociales'),
      precio = 199,
      anio = 2018,
      paginas = 228,
      foto = '9786077475187.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Erich Fromm']],

  
    [Libro(
      titulo = 'Física 3',
      editorial = Editorial('Grupo Editorial Patria'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 190,
      anio = 2014,
      paginas = 228,
      foto = '9786074383621.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['HECTOR PEREZ MONTIEL']],

  
    [Libro(
      titulo = 'Fluyan mis lágrimas, dijo el policía',
      editorial = Editorial('Minotauro'),
      genero = Genero('Ficción y temas afines'),
      precio = 248,
      anio = 2017,
      paginas = 268,
      foto = '9786070744327.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Philip K. Dick']],

  
    [Libro(
      titulo = '¿Sueñan los androides con ovejas eléctricas?',
      editorial = Editorial('Minotauro'),
      genero = Genero('Ficción y temas afines'),
      precio = 248,
      anio = 2017,
      paginas = 272,
      foto = '9786070743603.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Philip K. Dick']],

  
    [Libro(
      titulo = 'Blade Runner',
      editorial = Editorial('Edhasa'),
      genero = Genero('Ficción y temas afines'),
      precio = 349,
      anio = 2017,
      paginas = 268,
      foto = '9788435021296.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Philip Kindred Dick']],

  
    [Libro(
      titulo = 'Tratado de Derecho Civil Tomo VII',
      editorial = Editorial('Editorial Porrúa México'),
      genero = Genero('Derecho civil'),
      precio = 390,
      anio = 2018,
      paginas = 316,
      foto = '9786070917554.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Julián Güitrón Fuentevilla']],

  
    [Libro(
      titulo = 'El hombre en el castillo',
      editorial = Editorial('Minotauro'),
      genero = Genero('Ficción y temas afines'),
      precio = 248,
      anio = 2017,
      paginas = 264,
      foto = '9786070743979.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Philip K. Dick']],

  
    [Libro(
      titulo = 'Albur y neurociencia',
      editorial = Editorial('Ediciones Obelisco'),
      genero = Genero('Matemáticas y ciencia'),
      precio = 250,
      anio = 2018,
      paginas = 104,
      foto = '9788491113416.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Juan Antonio Barrera Méndez']],

  
    [Libro(
      titulo = 'P.D. Desde París (Ella y Él)',
      editorial = Editorial('Planeta'),
      genero = Genero('Ficción y temas afines'),
      precio = 288,
      anio = 2018,
      paginas = 312,
      foto = '9786070752490.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Marc Levy']],

  
    [Libro(
      titulo = 'Huesos de lagartija',
      editorial = Editorial('EDICIONES SM'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 144,
      anio = 2016,
      paginas = 224,
      foto = '9786072420762.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Federico Navarrete']],

  
    [Libro(
      titulo = 'Margarita',
      editorial = Editorial('Ediciones Idampa'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 349,
      anio = 2018,
      paginas = 34,
      foto = '9788494684647.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Rubén Darío']],

  
    [Libro(
      titulo = 'Los cuatro acuerdos',
      editorial = Editorial('EDICIONES URANO'),
      genero = Genero('Salud y desarrollo personal'),
      precio = 265,
      anio = 2009,
      paginas = 156,
      foto = '9786079513979.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Miguel Ruiz']],

  
    [Libro(
      titulo = 'Regina',
      editorial = Editorial('PENGUIN RANDOM HOUSE'),
      genero = Genero('Ficción y temas afines'),
      precio = 329,
      paginas = 712,
      foto = '9786073130325.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Antonio Velasco Piña']],

  
    [Libro(
      titulo = 'El retorno de lo sagrado',
      editorial = Editorial('Penguin Random House Grupo Editorial'),
      genero = Genero('Ficción y temas afines'),
      precio = 149,
      anio = 2009,
      paginas = 194,
      foto = '9786071102386.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Antonio Velasco Piña']],

  
    [Libro(
      titulo = 'Los siete rayos',
      editorial = Editorial('Penguin Random House Grupo Editorial'),
      genero = Genero('Ficción y temas afines'),
      precio = 129,
      anio = 2010,
      paginas = 145,
      foto = '9786071105264.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Antonio Velasco Piña']],

  
    [Libro(
      titulo = 'El terror',
      editorial = Editorial('Roca Editorial'),
      genero = Genero('Ficción y temas afines'),
      precio = 399,
      anio = 2018,
      paginas = 766,
      foto = '9788417167998.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Dan Simmons']],

  
    [Libro(
      titulo = 'Los reyes de la arena',
      editorial = Editorial('Plaza Janés'),
      genero = Genero('Ficción y temas afines'),
      precio = 299,
      anio = 2018,
      paginas = 408,
      foto = '9786073161008.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['George R. R. Martin']],

  
    [Libro(
      titulo = 'Danza de dragones : Canción de hielo y fuego 5',
      editorial = Editorial('Penguin Random House Grupo Editorial'),
      genero = Genero('Ficción y temas afines'),
      precio = 339,
      anio = 2015,
      paginas = 1136,
      foto = '9786073130240.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['George R. R. Martin']],

  
    [Libro(
      titulo = 'Choque de reyes',
      editorial = Editorial('ED RANDOM HOUSE/PLAZA Y JANES'),
      genero = Genero('Ficción y temas afines'),
      precio = 439,
      paginas = 927,
      foto = '9786073108409.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['George R. R. Martin']],

  
    [Libro(
      titulo = 'Los viajes de Tuf',
      editorial = Editorial('Ediciones B'),
      genero = Genero('Ficción y temas afines'),
      precio = 349,
      anio = 2013,
      paginas = 548,
      foto = '9788466652247.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['George R. R. Martin']],

  
    [Libro(
      titulo = 'Medicina de urgencias',
      editorial = Editorial('MEDICA PANAMERICANA'),
      genero = Genero('Medicina'),
      precio = 1075,
      anio = 2018,
      paginas = 900,
      foto = '9786078546091.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Isauro Ramón Gutiérrez Vázquez']],

  
    [Libro(
      titulo = 'Medicina holística chica en tu vida diaria',
      editorial = Editorial('Grupo Editorial Tomo'),
      genero = Genero('Salud y desarrollo personal'),
      precio = 229,
      anio = 2017,
      paginas = 544,
      foto = '9786074158328.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Steven Cardoza']],

  
    [Libro(
      titulo = 'Deadpool dibujando al mercenario bocón',
      editorial = Editorial('Panini Books'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 699,
      anio = 2018,
      paginas = 188,
      foto = '9786075288024.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Matthew K. Manning']],

  
    [Libro(
      titulo = 'Batman. La historia visual',
      editorial = Editorial('DORLING KINDERSLEY'),
      genero = Genero('Ficción y temas afines'),
      precio = 880,
      anio = 2015,
      paginas = 352,
      foto = '9780241240014.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Matthew K. Manning']],

  
    [Libro(
      titulo = 'Don Abundio, el del Potrero',
      editorial = Editorial('Diana'),
      genero = Genero('Ficción y temas afines'),
      precio = 198,
      anio = 2017,
      paginas = 256,
      foto = '9786070744242.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Catón']],

  
    [Libro(
      titulo = 'Teologías para ateos',
      editorial = Editorial('Diana'),
      genero = Genero('Humanidades'),
      precio = 228,
      anio = 2018,
      paginas = 248,
      foto = '9786070751790.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Catón']],

  
    [Libro(
      titulo = 'Judy Moody está de mal humor',
      editorial = Editorial('Penguin Random House Grupo Editorial'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 159,
      anio = 2014,
      paginas = 167,
      foto = '9786071113009.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['PETER H. REYNOLDS']],

  
    [Libro(
      titulo = 'Soda Stereo: La biografía total',
      editorial = Editorial('Grijalbo'),
      genero = Genero('Biografía e historias reales'),
      precio = 249,
      anio = 2018,
      paginas = 288,
      foto = '9786073168885.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Marcelo Fernández Bitar']],

  
    [Libro(
      titulo = 'Paul McCartney la biografía',
      editorial = Editorial('Malpaso'),
      genero = Genero('Biografía e historias reales'),
      precio = 745,
      anio = 2018,
      paginas = 836,
      foto = '9788416420353.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Philip Norman']],

  
    [Libro(
      titulo = 'Partículas elementales',
      editorial = Editorial('Booket'),
      genero = Genero('Matemáticas y ciencia'),
      precio = 199,
      anio = 2018,
      paginas = 256,
      foto = '9786077475538.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Gerardt Hooft']],

  
    [Libro(
      titulo = 'Inglés sin maestro',
      editorial = Editorial('Selector'),
      genero = Genero('Enseñanza de la lengua inglesa (ELT)(*)'),
      precio = 150,
      anio = 2018,
      paginas = 224,
      foto = '9786074535372.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Mónica Stevens']],

  
    [Libro(
      titulo = '500 años después... de una larga siesta',
      editorial = Editorial('Editorial Porrúa México'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 75,
      anio = 2015,
      paginas = 40,
      foto = '9786070902987.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['M. B. Brozon']],

  
    [Libro(
      titulo = 'El método Catfulness',
      editorial = Editorial('EDICIONES URANO'),
      genero = Genero('Salud y desarrollo personal'),
      precio = 175,
      anio = 2017,
      paginas = 96,
      foto = '9788479539832.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Paolo Valentino']],

  
    [Libro(
      titulo = 'Introducción a la computación',
      editorial = Editorial('Grupo Editorial Patria'),
      genero = Genero('Infantiles, juveniles y didácticos'),
      precio = 335,
      anio = 2013,
      paginas = 394,
      foto = '9786074383379.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Jorge Vasconcelos Santillán']],

  
    [Libro(
      titulo = 'Nietzsche voluntad de poder',
      editorial = Editorial('Clave Editorial'),
      genero = Genero('Humanidades'),
      precio = 249,
      anio = 2018,
      paginas = 112,
      foto = '9786074374247.jpg',
      edicion = 1,
      esEditor = 0,
      existencias = 10),
    ['Gerardo Martínez Cristerna']]]

  guardar_libros(libros)
