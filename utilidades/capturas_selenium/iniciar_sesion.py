"""
  Script para captura de formulario de inicio de sesión,
  aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import sys, time
from captura_generica_pagina import CapturaGenericaPagina

class CapturaInicioDeSesion (CapturaGenericaPagina):
  """
  Sobreescribe el comportamiento de una captura genérica de página.

  La idea original era sobreescribir solamente la captura genérica, pero
  el pánel lateral se sigue viendo en el fondo difuminado. De momento esto
  deja en términos un tanto inútiles a la captura genérica de una página,
  pues es todas las subclases serán hijos suyos.
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
