"""
  Script para captura de página de administración de tokens.
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import sys
from captura_con_sesion import CapturaConSesion

if __name__ == '__main__':

  captura = CapturaConSesion(sys.argv[1], sys.argv[2], \
    'cliente@prueba.com', '123456', sys.argv[3])
  captura.tomarCapturas()
