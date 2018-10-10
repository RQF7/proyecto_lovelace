"""
Datos de prueba para tienda en línea.
Proyecto Lovelace.
"""

import os, sys, django, hashlib

sys.path.append(os.path.dirname(os.path.realpath(__file__)) + '/../')
os.environ['DJANGO_SETTINGS_MODULE'] = 'tienda.configuraciones'
django.setup()

from tienda.tienda.models.usuario import Usuario

from tienda_catalogos \
  import guardar

if __name__ == '__main__':

  usuarios = [
    Usuario(
      nombre = 'Cliente',
      correo = 'cliente@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest())]

  guardar(usuarios)
