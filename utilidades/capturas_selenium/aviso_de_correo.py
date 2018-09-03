"""
  Script para captura de aviso de correo de confirmación,
  aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import time, sys
from captura_generica_pagina import CapturaGenericaPagina

class CapturaAvisoDeCorreo (CapturaGenericaPagina):
  """
  """

  def __init__ (ego, url, rutaArchivo, usuario):
    """
    """
    CapturaGenericaPagina.__init__(ego, url, rutaArchivo)
    ego.mUsuario = usuario


  def configuracionCapturaExtraGrande (ego):
    """
    """
    CapturaGenericaPagina.configuracionCapturaExtraGrande(ego)
    botonRegistrarse = ego.mNavegador.find_element_by_id('botonRegistrarse')
    botonRegistrarse.click()
    inputDeCorreo = ego.mNavegador.find_element_by_name('correo')
    inputDeCorreo.send_keys(ego.mUsuario)
    inputDeContrasenia = ego.mNavegador.find_element_by_name('contrasenia')
    inputDeContrasenia.send_keys('12345678')
    inputDeConfirmacion = ego.mNavegador.find_element_by_name('confirmacion')
    inputDeConfirmacion.send_keys('12345678')
    botonAceptar = ego.mNavegador.find_element_by_id(
      'formularioBotonRegistrarCliente')
    botonAceptar.click()
    time.sleep(0.5)


if __name__ == '__main__':

  captura = CapturaAvisoDeCorreo(sys.argv[1], sys.argv[2],
    'capturas@prueba.com')
  captura.tomarCapturas()
