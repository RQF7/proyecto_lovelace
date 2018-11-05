"""
Script de demostración de aplicación web de sistema tokenizador.
Presentación de TTII.
Proyecto Lovelace.
"""

import os
import subprocess
import sys
import time
from selenium import webdriver
from selenium.webdriver.support import expected_conditions as EC

EJECUTABLE_CHROME = '/usr/bin/chromium'
EJECUTABLE_DRIVER = '/usr/bin/chromedriver'
DIRECCION_BASE = 'http://127.0.0.1:8080'

if __name__ == '__main__':

  if len(sys.argv) != 1:
    DIRECCION_BASE = sys.argv[1]

  servidor = subprocess.Popen(['python', 'administrar_sistema_tokenizador.py',
    'runserver', '0:8080'])

  opcionesDeChrome = webdriver.chrome.options.Options()
  opcionesDeChrome.add_argument("--window-size=1920,1080")
  opcionesDeChrome.binary_location = EJECUTABLE_CHROME

  # Creación de controlador y GET inicial
  controlador = webdriver.Chrome(
    executable_path = EJECUTABLE_DRIVER,
    chrome_options = opcionesDeChrome)
  controlador.get(DIRECCION_BASE)

  # Esperar a que se cargue el html de inicio
  webdriver.support.ui.WebDriverWait(controlador, 10)\
    .until(EC.presence_of_all_elements_located((
      webdriver.common.by.By.CLASS_NAME, 'seccion')))

  # Scroll en la página de inicio
  for i in range(4000):
    controlador.execute_script("""
      var contenidos = document.getElementById('contenidos');
      contenidos.scrollTop += 1;""")

  # Página de documentación
  controlador.find_element_by_id('boton-documentacion').click()
  webdriver.support.ui.WebDriverWait(controlador, 10)\
    .until(EC.presence_of_all_elements_located((
      webdriver.common.by.By.CLASS_NAME, 'seccion')))

  # Scroll en página de documentación
  controlador.execute_script("""
    document.getElementById('contenidos').scrollTop = 0;""")
  for i in range(2800):
    controlador.execute_script("""
      var contenidos = document.getElementById('contenidos');
      contenidos.scrollTop += 1;""")
  for i in range(2800 // 2):
    controlador.execute_script("""
      var contenidos = document.getElementById('contenidos');
      contenidos.scrollTop -= 2;""")

  # Iniciar sesión con administrador
  controlador.find_element_by_id('botonIniciarSesion').click()
  controlador.find_element_by_name('correo')\
    .send_keys('administrador@prueba.com')
  controlador.find_element_by_name('contrasenia')\
    .send_keys('123456')
  controlador.find_element_by_id('formularioBotonIniciarSesion').click()

  # controlador.quit()
  servidor.send_signal('SIGTERM')
