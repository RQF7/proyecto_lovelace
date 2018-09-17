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
from sistema_tokenizador.programa_tokenizador.models.algoritmo \
  import Algoritmo
from sistema_tokenizador.programa_tokenizador.models.estado_de_llave \
  import EstadoDeLlave
from sistema_tokenizador.programa_tokenizador.models.llave \
  import Llave

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
      correo = 'cliente@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'a')),
    Correo(
      correo = 'administrador@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'a')),
    Correo(
      correo = 'cliente-no-verificado@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'no verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'a')),
    Correo(
      correo = 'cliente-rechazado@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest(),
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'),
      vinculo = Vinculo.objects.get(vinculo = 'd'))]

  guardar(correos)

  usuarios = [
    Usuario(
      correo = Correo.objects.get(
        correo = 'cliente@prueba.com'),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'cliente'),
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'aprobado')),
    Usuario(
      correo = Correo.objects.get(
        correo = 'administrador@prueba.com'),
      tipoDeUsuario = TipoDeUsuario.objects.get(
        nombre = 'administrador'),
      estadoDeUsuario = None),
    Usuario(
      correo = Correo.objects.get(
        correo = 'cliente-no-verificado@prueba.com'),
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
        nombre = 'rechazado'))]

  guardar(usuarios)

  for i in range(20):

    correos = [
      Correo(
        correo = 'cliente-en-lista-negra-' + chr(97 + i) + '@prueba.com',
        contrasenia = hashlib.sha256(b"123456").digest(),
        estadoDeCorreo = EstadoDeCorreo.objects.get(
          nombre = 'verificado')),
      Correo(
        correo = 'cliente-aprobado-' + chr(97 + i) + '@prueba.com',
        contrasenia = hashlib.sha256(b"123456").digest(),
        estadoDeCorreo = EstadoDeCorreo.objects.get(
          nombre = 'verificado')),
      Correo(
        correo = 'cliente-en-espera-' + chr(97 + i) + '@prueba.com',
        contrasenia = hashlib.sha256(b"123456").digest(),
        estadoDeCorreo = EstadoDeCorreo.objects.get(
          nombre = 'verificado'))]

    guardar(correos)

    usuarios = [
      Usuario(
        correo = correos[0],
        tipoDeUsuario = TipoDeUsuario.objects.get(
          nombre = 'cliente'),
        estadoDeUsuario = EstadoDeUsuario.objects.get(
          nombre = 'en lista negra')),
      Usuario(
        correo = correos[1],
        tipoDeUsuario = TipoDeUsuario.objects.get(
          nombre = 'cliente'),
        estadoDeUsuario = EstadoDeUsuario.objects.get(
          nombre = 'aprobado')),
      Usuario(
        correo = correos[2],
        tipoDeUsuario = TipoDeUsuario.objects.get(
          nombre = 'cliente'),
        estadoDeUsuario = EstadoDeUsuario.objects.get(
          nombre = 'en espera'))]

    guardar(usuarios)

  llaves = [
    Llave(
      llave = 'Niq0QQ4j0tOgy4QL9Yeyiw==',
      criptoperiodo = 180,
      fechaDeCreacion = '2018-10-10',
      algoritmo_id = Algoritmo.objects.get(nombre = 'FFX'),
      estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'actual'),
      usuario_id = Usuario.objects.get(
        correo = Correo.objects.get(correo = 'cliente@prueba.com')).id
    ),
    Llave(
      llave = 'Niq0QQ4j1tOgy4QL9Yeyiw==',
      criptoperiodo = 180,
      fechaDeCreacion = '2018-10-10',
      algoritmo_id = Algoritmo.objects.get(nombre = 'BPS'),
      estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'actual'),
      usuario_id = Usuario.objects.get(
        correo = Correo.objects.get(correo = 'cliente@prueba.com')).id
    ),
    Llave(
      llave = 'Niq0QQ4j2tOgy4QL9Yeyiw==',
      criptoperiodo = 180,
      fechaDeCreacion = '2018-10-10',
      algoritmo_id = Algoritmo.objects.get(nombre = 'DRBG'),
      estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'actual'),
      usuario_id = Usuario.objects.get(
        correo = Correo.objects.get(correo = 'cliente@prueba.com')).id
    ),
    Llave(
      llave = 'Niq0QQ4j3tOgy4QL9Yeyiw==',
      criptoperiodo = 180,
      fechaDeCreacion = '2018-10-10',
      algoritmo_id = Algoritmo.objects.get(nombre = 'TKR'),
      estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'actual'),
      usuario_id = Usuario.objects.get(
        correo = Correo.objects.get(correo = 'cliente@prueba.com')).id
    ),
    Llave(
      llave = 'Niq0QQ4j3tOgy4QL9Yeyiw==Niq0QQ4j3tOgy4QL9Yeyiw==',
      criptoperiodo = 180,
      fechaDeCreacion = '2018-10-10',
      algoritmo_id = Algoritmo.objects.get(nombre = 'AHR'),
      estadoDeLlave_id = EstadoDeLlave.objects.get(nombre = 'actual'),
      usuario_id = Usuario.objects.get(
        correo = Correo.objects.get(correo = 'cliente@prueba.com')).id
    )
  ]

  guardar(llaves)
