"""
  Script para captura de página de administración de cuenta.
  Caso de prueba: tienda de libros en línea.
  Proyecto Lovelace.
"""

import sys
from captura_con_sesion import CapturaConSesion

if __name__ == '__main__':

  captura = CapturaConSesion(sys.argv[1], sys.argv[2], \
    'cliente@prueba.com', '123456', sys.argv[3])
  captura.tomarCapturas()
