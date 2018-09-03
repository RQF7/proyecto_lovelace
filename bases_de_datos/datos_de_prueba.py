"""
  Inserción de datos de prueba,
  Aplicación web para sistema tokenizador.
  Proyecto Lovelace.

  IMPORTANTE: este script supone que los datos base ya se encuentran
  guardados.
"""

import os, sys, django, hashlib

sys.path.append(os.path.dirname(os.path.realpath(__file__)) + '/../')
os.environ['DJANGO_SETTINGS_MODULE'] = 'sistema_tokenizador.configuraciones'
django.setup()

from sistema_tokenizador.general.models.estado_de_usuario \
  import EstadoDeUsuario
from sistema_tokenizador.general.models.tipo_de_usuario \
  import TipoDeUsuario
from sistema_tokenizador.general.models.usuario \
  import Usuario
from datos_base \
  import guardar


if __name__ == '__main__':

  usuarios = [
    Usuario(
      correo = 'cliente@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'aprobado')),
    Usuario(
      correo = 'cliente-no-verificado@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'no verificado')),
    Usuario(
      correo = 'cliente-no-aprobado@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'verificado')),
    Usuario(
      correo = 'cliente-rechazado@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'rechazado')),
    Usuario(
      correo = 'cliente-en-lista-negra@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'en lista negra')),
    Usuario(
      correo = 'administrador@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'administrador'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'aprobado'))]

  guardar(usuarios)
