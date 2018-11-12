"""
Captura de formulario para agregar un método de pago.
Caso de prueba: tienda de libros en línea.
Proyecto Lovelace.
"""

import sys
from captura_ventana import CapturaVentana

if __name__ == '__main__':

  captura = CapturaVentana(sys.argv[1], sys.argv[2],
    'cliente@prueba.com', '123456', sys.argv[3],
    'boton-agregar-metodo-de-pago')
  captura.tomarCapturas()
