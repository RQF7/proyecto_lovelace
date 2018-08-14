"""
  Ejemplo 4 de selenium
  Proyecto Lovelace

  Lo mismo que en el ejemplo 3, pero en modo silencioso.
"""

import sys
from selenium import webdriver
from selenium.webdriver.chrome.options import Options

if __name__ == '__main__':

  CHROME_PATH = '/usr/bin/chromium'
  CHROMEDRIVER_PATH = '/usr/bin/chromedriver'
  WINDOW_SIZE = "1920,1080"

  chrome_options = Options()
  chrome_options.add_argument("--headless")
  chrome_options.add_argument("--window-size=%s" % WINDOW_SIZE)
  chrome_options.binary_location = CHROME_PATH

  browser = webdriver.Chrome(
    executable_path = CHROMEDRIVER_PATH,
    chrome_options = chrome_options)
  browser.get(sys.argv[1])
  # browser.maximize_window()
  browser.save_screenshot('captura.png')
