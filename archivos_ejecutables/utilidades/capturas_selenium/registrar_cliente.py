"""
  Script para captura de formulario de registro de clientes,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import sys, time
from captura_generica_pagina import CapturaGenericaPagina

class CapturaRegistrarCliente (CapturaGenericaPagina):
  """
  Sobreescribe el comportamiento de una captura genérica de página.

  TODO: crear clase abstracta que abarque a el inicio de sesión y el registro:
  el identificador del botón se puede recibir como parámetro.
  """

  def configuracionCapturaExtraGrande (ego):
    """Abre la ventana del formulario."""
    CapturaGenericaPagina.configuracionCapturaExtraGrande(ego)
    boton = ego.mNavegador.find_element_by_id('botonRegistrarse')
    boton.click()
    time.sleep(0.5)


if __name__ == '__main__':

  captura = CapturaRegistrarCliente(sys.argv[1], sys.argv[2])
  captura.tomarCapturas()
