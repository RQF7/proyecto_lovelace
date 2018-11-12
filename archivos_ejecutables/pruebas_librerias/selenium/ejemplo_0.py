"""
  Ejemplo 0 de tutoriales de selenium.
  Proyecto Lovelace.

  Abre una ventana del navegador.
"""

from selenium import webdriver

browser = webdriver.Chrome()
#browser = webdriver.Firefox()

browser.get('http://seleniumhq.org/')
