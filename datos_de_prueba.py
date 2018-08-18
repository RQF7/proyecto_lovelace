"""
  Inserción de datos de prueba,
  Aplicación web para sistema tokenizador.
  Proyecto Lovelace.

  IMPORTANTE: este script supone que los datos base ya se encuentran
  guardados.

  TODO: hacer que esto funcione en cualquier otro lugar que no sea la carpeta
  raíz del proyecto. En la raíz solamente van configuraciones.
"""

import os, django, hashlib

os.environ['DJANGO_SETTINGS_MODULE'] = 'sistema_tokenizador.configuraciones'
django.setup()

from sistema_tokenizador.general.models.tipo_de_usuario import TipoDeUsuario
from sistema_tokenizador.general.models.usuario import Usuario
from datos_base import guardar


if __name__ == '__main__':

  usuarios = [
    Usuario(
      correo = 'usuario@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'usuario')),
    Usuario(
      correo = 'administrador@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'administrador'))]

  guardar(usuarios)
