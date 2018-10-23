"""
Captura de formulario para elegir la forma de pago al finalizar una compra.
Caso de prueba: tienda de libros en línea.
Proyecto Lovelace.
"""

import sys, time
from libreria_carrito import CapturaDeCarrito

class CapturaDeFormaDePago (CapturaDeCarrito):
  """
  Sobreescribe el comportamiento de una captura CapturaDeCarrito.
  """

  def configuracionCapturaExtraGrande (ego):
    """Abre la ventana del formulario."""
    super().configuracionCapturaExtraGrande()
    boton = ego.mNavegador.find_element_by_id('botonFinalizarCompra')
    boton.click()
    time.sleep(0.5)


if __name__ == '__main__':

  captura = CapturaDeFormaDePago(sys.argv[1], sys.argv[2],
    'cliente@prueba.com', '123456', sys.argv[3])
  captura.tomarCapturas()
