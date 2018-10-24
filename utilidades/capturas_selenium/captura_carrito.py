"""
  Clase para las capturas relacionadas al proceso de finalizar una compra.
  Caso de prueba: tienda de libros en línea.
  Proyecto Lovelace.
"""

import sys, time
from captura_ventana import CapturaVentana
from captura_con_sesion import CapturaConSesion
from captura_generica_pagina import CapturaGenericaPagina

class CapturaCarrito (CapturaVentana):
  """
  Sobreescribe el comportamiento de una captura de ventana.
  """

  def configuracionCapturaExtraGrande (ego):
    """Abre la ventana del formulario."""
    CapturaGenericaPagina.configuracionCapturaExtraGrande(ego)
    boton1 = ego.mNavegador.find_element_by_id('libro1')
    boton2 = ego.mNavegador.find_element_by_id('libro2')
    boton3 = ego.mNavegador.find_element_by_id('libro3')
    boton4 = ego.mNavegador.find_element_by_id('libro4')
    boton1.click()
    boton2.click()
    boton3.click()
    boton4.click()
    time.sleep(0.5)
    CapturaConSesion.configuracionCapturaExtraGrande(ego)
