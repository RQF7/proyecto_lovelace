"""
  Script para captura de pantalla de inicio,
  Caso de prueba: tienda de libros en línea.
  Proyecto Lovelace.
"""

import sys
from captura_generica_pagina import CapturaGenericaPagina

if __name__ == '__main__':

  captura = CapturaGenericaPagina(sys.argv[1], sys.argv[2])
  captura.tomarCapturas()
