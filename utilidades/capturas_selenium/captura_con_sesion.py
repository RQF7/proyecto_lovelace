"""
  Clase genérica para pantallas que requieren un inicio de sesión.
  Proyecto Lovelace.
"""

import time
from captura_generica_pagina import CapturaGenericaPagina

class CapturaConSesion (CapturaGenericaPagina):
  """
  Clase para capturas de pantalla que requieren un inicio de sesión.

  Sobreescribe el comportamiento de la clase de captura de página para primero
  iniciar sesión y después tomar capturas.
  """

  def __init__ (ego, urlInicial, rutaArchivo, correo, contrasenia, urlFinal):
    """
    Constructor de clase.

    Llama al constructor de la superclase e inicializa los
    atributos de la clase.
    """

    CapturaGenericaPagina.__init__(ego, urlInicial, rutaArchivo)
    ego.mCorreo = correo
    ego.mContrasenia = contrasenia
    ego.mUrlFinal = urlFinal


  def configuracionCapturaExtraGrande (ego):
    """
    Configuración inicial de capturas.

    Primero inicia sesión en la página actual (la urlInicial) y después abre la
    segunda url para iniciar la toma de capturas.
    """

    CapturaGenericaPagina.configuracionCapturaExtraGrande(ego)
    botonIniciarSesion = ego.mNavegador.find_element_by_id('botonIniciarSesion')
    botonIniciarSesion.click()
    inputDeCorreo = ego.mNavegador.find_element_by_name('correo')
    inputDeCorreo.send_keys(ego.mCorreo)
    inputDeContrasenia = ego.mNavegador.find_element_by_name('contrasenia')
    inputDeContrasenia.send_keys(ego.mContrasenia)
    botonAceptar = \
      ego.mNavegador.find_element_by_id('formularioBotonIniciarSesion')
    botonAceptar.click()
    time.sleep(0.5)
    ego.mNavegador.get(ego.mUrlFinal)
