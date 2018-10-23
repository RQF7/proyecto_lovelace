"""
Captura de formulario para elegir la forma de pago al finalizar una compra.
Caso de prueba: tienda de libros en línea.
Proyecto Lovelace.
"""

import sys
from libreria_carrito import CapturaDeCarrito

if __name__ == '__main__':

  captura = CapturaDeCarrito(sys.argv[1], sys.argv[2],
    'cliente@prueba.com', '123456', sys.argv[3],
    'botonFinalizarCompra')
  captura.tomarCapturas()
