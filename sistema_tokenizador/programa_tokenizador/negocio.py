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
  
from sistema_tokenizador.programa_tokenizador.models.algoritmo \
  import Algoritmo
from sistema_tokenizador.programa_tokenizador.models.estado_de_llave \
  import EstadoDeLlave
from sistema_tokenizador.programa_tokenizador.models.llave \
  import Llave
from sistema_tokenizador.programa_tokenizador.models.token \
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
  Se encarga de generar todas las llaves de una manera no bloqueante.
  """

  # Se crean las llaves
  llaves = [
  Llave(
    llave = generarLlave(Algoritmo.objects.get(
      nombre = 'FFX').longitudDeLlave),
    criptoperiodo = 10,
    fechaDeCreacion = datetime.today().strftime(
      "%Y-%m-%d %H:%M:%S"),
    algoritmo_id = Algoritmo.objects.get(
      nombre = 'FFX'),
    estadoDeLlave_id = EstadoDeLlave.objects.get(
      nombre = 'actual'),
    usuario_id = cliente.id),
  Llave(
    llave = generarLlave(Algoritmo.objects.get(
      nombre = 'BPS').longitudDeLlave),
    criptoperiodo = 10,
    fechaDeCreacion = datetime.today().strftime(
      "%Y-%m-%d %H:%M:%S"),
    algoritmo_id = Algoritmo.objects.get(
      nombre = 'BPS'),
    estadoDeLlave_id = EstadoDeLlave.objects.get(
      nombre = 'actual'),
    usuario_id = cliente.id),
  Llave(
    llave = generarLlave(Algoritmo.objects.get(
      nombre = 'TKR').longitudDeLlave),
    criptoperiodo = 10,
    fechaDeCreacion = datetime.today().strftime(
      "%Y-%m-%d %H:%M:%S"),
    algoritmo_id = Algoritmo.objects.get(
      nombre = 'TKR'),
    estadoDeLlave_id = EstadoDeLlave.objects.get(
      nombre = 'actual'),
    usuario_id = cliente.id),
  Llave(
    llave = generarLlave(Algoritmo.objects.get(
      nombre = 'AHR').longitudDeLlave),
    criptoperiodo = 10,
    fechaDeCreacion = datetime.today().strftime(
      "%Y-%m-%d %H:%M:%S"),
    algoritmo_id = Algoritmo.objects.get(
      nombre = 'AHR'),
    estadoDeLlave_id = EstadoDeLlave.objects.get(
      nombre = 'actual'),
    usuario_id = cliente.id),
  Llave(
    llave = generarLlave(Algoritmo.objects.get(
      nombre = 'DRBG').longitudDeLlave),
    criptoperiodo = 10,
    fechaDeCreacion = datetime.today().strftime(
      "%Y-%m-%d %H:%M:%S"),
    algoritmo_id = Algoritmo.objects.get(
      nombre = 'DRBG'),
    estadoDeLlave_id = EstadoDeLlave.objects.get(
      nombre = 'actual'),
    usuario_id = cliente.id)]

  for llave in llaves:
    llave.save();

  # Se cambia el estado del cliente
  cliente.estadoDeUsuario = EstadoDeUsuario.objects.get(
    nombre = 'en cambio de llaves')
  cliente.save(force_update=True)
