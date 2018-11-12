"""
  Clase genérica para toma de capturas,
  Proyecto Lovelace.
"""

import os
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from subprocess import run

class CapturaGenerica:
  """
  Clase genérica para toma de capturas.

  Esta clase es totalmente virtual (en un lenguaje de c++, no sé cómo declarar
  ese tipo de cosas en python). La idea es que las capturas concretas hereden
  el comportamiento principal de esta clase. Las funciones que deberían
  extnderse son las 5 de configuraciones.

  El orden de la toma de captuas es de mayor a menor, por lo que la
  configuración inicial se debe de sobreescribir en la configuración de
  la captura extra grande.
  """

  mEjecutableChrome = '/usr/bin/chromium'
  mEjecutableDriver = '/usr/bin/chromedriver'
  mArchivoTemporal = 'captura.png'

  def __init__ (ego, url, rutaArchivo):
    """
    Constructor de clase.

    Configura chrome en modo silencioso y abre una instancia en la url
    dada. Toma las rutas de los ejecutables de chrome y del driver de las
    cadenas miembro.
    """

    partes = rutaArchivo.split('_1920x1080')
    ego.mRutaArchivo = partes[0]
    opcionesDeChrome = Options()
    opcionesDeChrome.add_argument("--headless")
    opcionesDeChrome.add_argument("--window-size=1920,1080")
    opcionesDeChrome.binary_location = ego.mEjecutableChrome
    ego.mNavegador = webdriver.Chrome(
      executable_path = ego.mEjecutableDriver,
      chrome_options = opcionesDeChrome)
    ego.mNavegador.get(url)


  def configuracionCapturaExtraGrande (ego):
    """Captura de 1920 x 1080."""
    pass


  def configuracionCapturaGrande (ego):
    """Captura de 1280 x 800."""
    ego.mNavegador.set_window_size(1280, 800)


  def configuracionCapturaMediana (ego):
    """Captura de 960 x 900."""
    ego.mNavegador.set_window_size(960, 900)


  def configuracionCapturaChica (ego):
    """Captura de 600 x 900."""
    ego.mNavegador.set_window_size(600, 900)


  def configuracionCapturaExtraChica (ego):
    """Captura de 480 x 800."""
    ego.mNavegador.set_window_size(480, 800)


  def guardarCaptura (ego, sufijo):
    """
    Instrucciones para guardar una captura.

    Ocupa el sufijo para agregarlo al nombre del archivo.
    Guarda la captura en el archivo temporal y después pasa al archivo destino
    mediante un filtro de escala de grises de imagemagick.
    """
    ego.mNavegador.save_screenshot(ego.mArchivoTemporal)
    run(['convert', ego.mArchivoTemporal, '-colorspace', 'Gray',
      ego.mRutaArchivo + sufijo])


  def tomarCapturas (ego):
    """
    Ciclo de toma de capturas.

    Esta función no se deberpia poder sobreescribir. Ejecuta las configuraciones
    de forma secuencial y va guardando las capturas. Al final cierra la instancia
    del navegador y elimina el archivo temporal.
    """

    ego.configuracionCapturaExtraGrande()
    ego.guardarCaptura('_1920x1080.png')

    ego.configuracionCapturaGrande()
    ego.guardarCaptura('_1280x800.png')

    ego.configuracionCapturaMediana()
    ego.guardarCaptura('_960x900.png')

    ego.configuracionCapturaChica()
    ego.guardarCaptura('_600x900.png')

    ego.configuracionCapturaExtraChica()
    ego.guardarCaptura('_480x800.png')

    ego.mNavegador.quit()
    os.remove(ego.mArchivoTemporal)
