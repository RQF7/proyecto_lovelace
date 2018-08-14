"""
  Ejemplo 1 de tutoriales de selenium.
  Proyecto Lovelace.

  Abre una ventana de yahoo y busca «seleniumhq».
"""

from selenium import webdriver
from selenium.webdriver.common.keys import Keys

browser = webdriver.Firefox()

browser.get('http://www.yahoo.com')
assert 'Yahoo' in browser.title

elem = browser.find_element_by_name('p')  # Find the search box
elem.send_keys('seleniumhq' + Keys.RETURN)

#browser.quit()
