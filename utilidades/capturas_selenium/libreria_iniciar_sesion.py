"""
  Script para captura de formulario de inicio de sesión,
  Caso de prueba: tienda de libros en línea.
  Proyecto Lovelace.
"""

import sys, time
from captura_generica_pagina import CapturaGenericaPagina

class CapturaInicioDeSesion (CapturaGenericaPagina):
  """
  Sobreescribe el comportamiento de una captura genérica de página.
  """

  def configuracionCapturaExtraGrande (ego):
    """Abre la ventana del formulario."""
    CapturaGenericaPagina.configuracionCapturaExtraGrande(ego)
    boton = ego.mNavegador.find_element_by_id('botonIniciarSesion')
    boton.click()
    time.sleep(0.5)


if __name__ == '__main__':

  captura = CapturaInicioDeSesion(sys.argv[1], sys.argv[2])
  captura.tomarCapturas()
