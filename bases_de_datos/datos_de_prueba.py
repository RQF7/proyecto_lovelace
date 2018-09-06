"""
  Inserción de datos de prueba,
  Aplicación web para sistema tokenizador.
  Proyecto Lovelace.

  IMPORTANTE: este script supone que los datos base ya se encuentran
  guardados.
"""

import os, sys, django, hashlib, datetime

sys.path.append(os.path.dirname(os.path.realpath(__file__)) + '/../')
os.environ['DJANGO_SETTINGS_MODULE'] = 'sistema_tokenizador.configuraciones'
django.setup()

from sistema_tokenizador.general.models.estado_de_usuario \
  import EstadoDeUsuario
from sistema_tokenizador.general.models.estado_de_correo \
  import EstadoDeCorreo
from sistema_tokenizador.general.models.tipo_de_usuario \
  import TipoDeUsuario
from sistema_tokenizador.general.models.usuario \
  import Usuario
from sistema_tokenizador.general.models.correo \
  import Correo
from sistema_tokenizador.general.models.vinculo \
  import Vinculo
from datos_base \
  import guardar


if __name__ == '__main__':

  vinculos = [
    Vinculo(vinculo = 'a', fecha = '2018-12-12'),
    Vinculo(vinculo = 'b', fecha = '2018-12-12'),
    Vinculo(vinculo = 'c', fecha = '2018-12-12'),
    Vinculo(vinculo = 'd', fecha = '2018-12-12'),
    Vinculo(vinculo = 'e', fecha = '2018-12-12'),
    Vinculo(vinculo = 'f', fecha = '2018-12-12')]

  guardar(vinculos)

  correos = [
    Correo(
      correo = 'cliente-no-verificado@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'no verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'a')),
    Correo(
      correo = 'cliente-verificado@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'b')),
    Correo(
      correo = 'cliente-en-espera@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'c')),
    Correo(
      correo = 'cliente-rechazado@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'd')),
    Correo(
      correo = 'cliente-en-lista-negra@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'e')),
    Correo(
      correo = 'cliente-aprobado@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'f'))]

  guardar(correos)

  usuarios = [
    Usuario(
      correo = Correo.objects.get(
        correo = 'cliente-no-verificado@prueba.com'),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'aprobado')),
    Usuario(
      correo = Correo.objects.get(
        correo = 'cliente-verificado@prueba.com'),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'aprobado')),
    Usuario(
      correo = Correo.objects.get(
        correo = 'cliente-en-espera@prueba.com'),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'en espera')),
    Usuario(
      correo = Correo.objects.get(
        correo = 'cliente-rechazado@prueba.com'),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'rechazado')),
    Usuario(
      correo = Correo.objects.get(
        correo = 'cliente-en-lista-negra@prueba.com'),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'en lista negra')),
    Usuario(
      correo = Correo.objects.get(
        correo = 'cliente-aprobado@prueba.com'),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'aprobado'))]

  guardar(usuarios)
