"""
Captura de formulario para registrar a un usuario.
Caso de prueba: tienda de libros en línea.
Proyecto Lovelace.
"""

import sys, time
from captura_generica_pagina import CapturaGenericaPagina

class CapturaRegistrarUsuario (CapturaGenericaPagina):

  def configuracionCapturaExtraGrande (ego):
    """Abre la ventana del formulario."""
    CapturaGenericaPagina.configuracionCapturaExtraGrande(ego)
    boton = ego.mNavegador.find_element_by_id('botonRegistrarse')
    boton.click()
    time.sleep(0.5)


if __name__ == '__main__':

  captura = CapturaRegistrarUsuario(sys.argv[1], sys.argv[2])
  captura.tomarCapturas()
