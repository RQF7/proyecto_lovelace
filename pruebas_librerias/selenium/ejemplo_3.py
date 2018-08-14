"""
  Ejemplo 3 de selenium
  Proyecto Lovelace

  Toma una captura de pantalla de la url que llega como argumento
"""

import sys
from selenium import webdriver

if __name__ == '__main__':

  browser = webdriver.Chrome()
  browser.get(sys.argv[1])
  browser.maximize_window()
  browser.save_screenshot('captura.png')
