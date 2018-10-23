"""
  Script para captura de la pagina de carrito,
  Caso de prueba: tienda de libros en línea.
  Proyecto Lovelace.
"""

import sys, time
from captura_carrito import CapturaCarrito

class CapturaDeCarrito (CapturaCarrito):
  """
  Sobreescribe el comportamiento de una captura CapturaCarrito.
  """

  def configuracionCapturaExtraGrande (ego):
    """Abre la ventana del formulario."""
    super().configuracionCapturaExtraGrande()
    boton = ego.mNavegador.find_element_by_id('botonCarrito')
    boton.click()
    time.sleep(0.5)


if __name__ == '__main__':

  captura = CapturaDeCarrito(sys.argv[1], sys.argv[2],
    'cliente@prueba.com', '123456', sys.argv[3])
  captura.tomarCapturas()
