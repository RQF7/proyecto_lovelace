"""
  Operaciones de negocio de relacionadas con el programa tokenizador,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import base64, hashlib
from django.core import serializers
from django.shortcuts import render

from datetime import datetime
from subprocess import PIPE
from subprocess import run
from os import remove

from sistema_tokenizador import utilidades

from sistema_tokenizador.general.models.estado_de_usuario \
  import EstadoDeUsuario
from sistema_tokenizador.general.models.usuario \
  import Usuario

from sistema_tokenizador.configuraciones \
  import EJECUTABLE_TOKENIZADOR

from .models.algoritmo \
  import Algoritmo
from .models.estado_de_llave \
  import EstadoDeLlave
from .models.llave \
  import Llave
from .models.token \
  import Token

LIMITE_MALAS_ACCIONES = 10
INCREMENTO_TOKEN_INVALIDO = 1
INCREMENTO_TOKEN_INEXISTENTE = 3


def aumentarContadorDeMalasAcciones(cliente, incremento):
  """
  Incrementa el contador de malas acciones del cliente dado. Después, verifica
  que el contador no haya  sobre pasado el límite de males acciones; de ser así,
  cambia su estado a <<en lista negra>>.
  """

  cliente.contadorDeMalasAcciones = cliente.contadorDeMalasAcciones + incremento
  cliente.save()

  if cliente.contadorDeMalasAcciones > LIMITE_MALAS_ACCIONES:
    cliente.estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'en lista negra')
    cliente.save()


def verificarUnicidadDePAN(PAN, cliente_id):
  """
  Verifica que el cliente indicado no tenga asociado el PAN señalado.

  Regresa verdadero o falso.
  """
  try:
    registro = Token.objects.get(
      pan = PAN,
      usuario_id = cliente_id)
  except (Token.DoesNotExist):
    return 1
  return 0


def validarToken(token):
  """
  Valida que el token ingresado sea un token válido:
    - Tiene una longitud entre 12 y 19 dígitos.
    - Valida el dígito verificador (mediante el algoritmo de Luhn) con desfase
      de uno.

    Regresa uno si es válido, cero si no.
  """

  numeroDeElementos = len(token)

  if numeroDeElementos < 12 or numeroDeElementos > 19:
    return 0

  if int(token[-1]) != ((utilidades.calcularAlgoritmoLuhn(token) + 1) % 10):
    return 0

  return 1


def generarLlave(tamanio):
  """
  Se genera una llave en un archivo, este se lee y se borra cuando ya se
  obtuvo la llave.
  """
  dir_buffer = "BUFFER"
  resultado = run([EJECUTABLE_TOKENIZADOR, "-k", dir_buffer, str(tamanio)],
    stdout=PIPE)
  llave = open(dir_buffer).read()
  remove(dir_buffer)
  return llave


def generarLlaves(cliente):
  """
  Generación de llaves para el cliente dado.

  Se crea una llave para cada uno de los algoritmos del catálogo. Estas llaves
  están asociadas al cliente dado.
  """

  fecha = datetime.utcnow();
  algoritmos = Algoritmo.objects.all()
  for algoritmo in algoritmos:
    llave = Llave(
      llave = generarLlave(algoritmo.longitudDeLlave),
      criptoperiodo = 180,
      fechaDeCreacion = fecha,
      algoritmo = algoritmo,
      estadoDeLlave = EstadoDeLlave.objects.get(
        nombre = 'actual'),
      usuario = cliente)
    llave.save()
