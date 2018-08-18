"""
  Script para captura de página de administración.
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import sys
from captura_con_sesion import CapturaConSesion

if __name__ == '__main__':

  captura = CapturaConSesion(sys.argv[1], sys.argv[2], \
    'administrador@prueba.com', '123456', sys.argv[3])
  captura.tomarCapturas()
