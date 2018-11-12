"""
Captura del resumen de compra mostrado al finalizar una compra.
Caso de prueba: tienda de libros en línea.
Proyecto Lovelace.
"""

import sys, time
from libreria_direccion_de_entrega import CapturaDeDireccionDeEntrega

class CapturaDeResumenDeCompra (CapturaDeDireccionDeEntrega):
  """
  Sobreescribe el comportamiento de una captura CapturaDeDireccionDeEntrega.
  """

  def configuracionCapturaExtraGrande (ego):
    """Abre la ventana del formulario."""
    super().configuracionCapturaExtraGrande()
    boton = ego.mNavegador.find_element_by_id(
      'botonContinuarFinalizacionDeCompra')
    boton.click()
    time.sleep(0.5)


if __name__ == '__main__':

  captura = CapturaDeResumenDeCompra(sys.argv[1],sys.argv[2],
    'cliente@prueba.com', '123456', sys.argv[3])
  captura.tomarCapturas()
