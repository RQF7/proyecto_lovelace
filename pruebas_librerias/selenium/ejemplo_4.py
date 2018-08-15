"""
  Ejemplo 4 de selenium
  Proyecto Lovelace

  Lo mismo que en el ejemplo 3, pero en modo silencioso.

  Este es el script que utiliza el makefile principal para generar capturas de
  pantalla para la documentación. Recibe como argumentos la url y el nombre
  del archivo de imagen destino.

  El tamaño por defecto es 1920x1080, después toma capturas de 4 tamaños más
  pequeños, (los lugares en donde están las cotas de CSS).

  La captura tomada la procesa con imagemagick para ponerla en escala de grises
  (y que así vaya con el estilo del reporte técnico).
"""

import sys, os, time
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from subprocess import run

if __name__ == '__main__':

  EJECUTABLE_CHROME = '/usr/bin/chromium'
  EJECUTABLE_DRIVER = '/usr/bin/chromedriver'
  TAMANIO_INICIAL = "1920,1080"
  archivoDestino = sys.argv[2]
  partes = archivoDestino.split('.')
  archivoTemporal = 'captura.png'

  opcionesDeChrome = Options()
  opcionesDeChrome.add_argument("--headless")
  opcionesDeChrome.add_argument("--window-size=%s" % TAMANIO_INICIAL)
  opcionesDeChrome.binary_location = EJECUTABLE_CHROME

  navegador = webdriver.Chrome(
    executable_path = EJECUTABLE_DRIVER,
    chrome_options = opcionesDeChrome)
  navegador.get(sys.argv[1])
  navegador.save_screenshot(archivoTemporal)
  run(['convert', archivoTemporal, '-colorspace', 'Gray', archivoDestino])

  # 1280x800
  navegador.set_window_size(1280, 800)
  time.sleep(1)
  navegador.save_screenshot(partes[0] + '_1280x800.' + partes[1])
  run(['convert', archivoTemporal, '-colorspace', 'Gray', archivoDestino])

  # 960x900
  navegador.set_window_size(960, 900)
  time.sleep(1)
  navegador.save_screenshot(archivoTemporal)
  run(['convert', archivoTemporal, '-colorspace', 'Gray', \
    partes[0] + '_960x900.' + partes[1]])

  # 600x960
  navegador.set_window_size(600, 900)
  time.sleep(1)
  navegador.save_screenshot(archivoTemporal)
  run(['convert', archivoTemporal, '-colorspace', 'Gray', \
    partes[0] + '_600x900.' + partes[1]])

  # 480x853
  navegador.set_window_size(480, 800)
  time.sleep(1)
  navegador.save_screenshot(archivoTemporal)
  run(['convert', archivoTemporal, '-colorspace', 'Gray', \
    partes[0] + '_480x800.' + partes[1]])

  navegador.quit()
  os.remove(archivoTemporal)
