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

from tienda.libreria.models.genero          import Genero
from tienda.tienda.models.emisor            import Emisor
from tienda.tienda.models.estado            import Estado
from tienda.tienda.models.metodo            import Metodo
from tienda.tienda.models.tipo_de_tarjeta   import TipoDeTarjeta
from tienda.tienda.models.tipo_de_direccion import TipoDeDireccion


def guardar(modelos):
  """Guarda los modelos dados omitiendo errores de integridad
  (entradas duplicadas)."""
  for modelo in modelos:
    try:
      modelo.save()
    except django.db.utils.IntegrityError:
      print('Entrada duplicada: ' + str(modelo))


if __name__ == '__main__':

  emisores = [
    Emisor(nombre = 'VISA'),
    Emisor(nombre = 'MasterCard'),
    Emisor(nombre = 'American Express')]

  guardar(emisores)

  tiposDeTarjeta = [
    TipoDeTarjeta(nombre = 'Débito'),
    TipoDeTarjeta(nombre = 'Crédito')]

  guardar(tiposDeTarjeta)

  tiposDeDireccion = [
    TipoDeDireccion(nombre = 'Punto de entrega'),
    TipoDeDireccion(nombre = 'Facturación')]

  guardar(tiposDeDireccion)

  metodos = [
    Metodo(nombre = 'FFX' ),
    Metodo(nombre = 'BPS' ),
    Metodo(nombre = 'TKR' ),
    Metodo(nombre = 'AHR' ),
    Metodo(nombre = 'DRBG')]

  guardar(metodos)

#  generos = [
#    Genero(nombre = 'Novelas'                   ),
#    Genero(nombre = 'Novelas románticas'        ),
#    Genero(nombre = 'Novelas erótica'           ),
#    Genero(nombre = 'Policial'                  ),
#    Genero(nombre = 'Ficción'                   ),
#    Genero(nombre = 'Aventura'                  ),
#    Genero(nombre = 'Drama'                     ),
#    Genero(nombre = 'Terror'                    ),
#    Genero(nombre = 'Ciencia ficción'           ),
#    Genero(nombre = 'Historias reales'          ),
#    Genero(nombre = 'Infantil'                  ),
#    Genero(nombre = 'Crímenes'                  ),
#    Genero(nombre = 'Comics y novelas gráficas' ),
#    Genero(nombre = 'Tecnología'                ),
#    Genero(nombre = 'Computación'               ),
#    Genero(nombre = 'Matemáticas'               ),
#    Genero(nombre = 'Ciencia'                   ),
#    Genero(nombre = 'Medicina'                  ),
#    Genero(nombre = 'Política y leyes'          ),
#    Genero(nombre = 'Negocios y economía'       ),
#    Genero(nombre = 'Lengua y literatura'       ),
#    Genero(nombre = 'Ciencias sociales'         ),
#    Genero(nombre = 'Psicología'                ),
#    Genero(nombre = 'Filosofía'                 ),
#    Genero(nombre = 'Geografía'                 ),
#    Genero(nombre = 'Historia'                  ),
#    Genero(nombre = 'Poesía'                    ),
#    Genero(nombre = 'Artes'                     ),
#    Genero(nombre = 'Humor'                     ),
#    Genero(nombre = 'Música'                    ),
#    Genero(nombre = 'Religión'                  ),
#    Genero(nombre = 'Investigación'             ),
#    Genero(nombre = 'Casa y hogar'              ),
#    Genero(nombre = 'Cocina y comida'           ),
#    Genero(nombre = 'Familia y relaciones'      ),
#    Genero(nombre = 'Deportes y recreación'     ),
#    Genero(nombre = 'Mascotas y animales'       ),
#    Genero(nombre = 'Autoayuda'                 ),
#    Genero(nombre = 'Biografía y autobiografía' ),
#    Genero(nombre = 'Off topic'                 )]

#  guardar(generos)

  estados = [
    Estado(nombre = 'Ciudad de México'    ),
    Estado(nombre = 'Estado de México'    ),
    Estado(nombre = 'Querétaro'           ),
    Estado(nombre = 'Guerrero'            ),
    Estado(nombre = 'Morelos'             ),
    Estado(nombre = 'Puebla'              ),
    Estado(nombre = 'Chihuahua'           ),
    Estado(nombre = 'Coahuila'            ),
    Estado(nombre = 'Sonora'              ),
    Estado(nombre = 'Durango'             ),
    Estado(nombre = 'Oaxaca'              ),
    Estado(nombre = 'Tamaulipas'          ),
    Estado(nombre = 'Zacatecas'           ),
    Estado(nombre = 'Jalisco'             ),
    Estado(nombre = 'Chiapas'             ),
    Estado(nombre = 'Baja California'     ),
    Estado(nombre = 'Baja California Sur' ),
    Estado(nombre = 'San Luis Potosí'     ),
    Estado(nombre = 'Aguascalientes'      ),
    Estado(nombre = 'Nuevo León'          ),
    Estado(nombre = 'Michoacán'           ),
    Estado(nombre = 'Veracruz'            ),
    Estado(nombre = 'Sinaloa'             ),
    Estado(nombre = 'Campeche'            ),
    Estado(nombre = 'Quintana Roo'        ),
    Estado(nombre = 'Guanajuato'          ),
    Estado(nombre = 'Tlaxcala'            ),
    Estado(nombre = 'Yucatán'             ),
    Estado(nombre = 'Nayarit'             ),
    Estado(nombre = 'Tabasco'             ),
    Estado(nombre = 'Hidalgo'             ),
    Estado(nombre = 'Colima'              )]

  guardar(estados)
