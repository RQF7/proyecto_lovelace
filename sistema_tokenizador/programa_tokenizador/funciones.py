"""
  funciones.py Definición de funciones externas de módulo de programa
  tokenizador.
  Proyecto Lovelace.
"""

from django.core import serializers
from django.http import HttpResponse
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt
from json import loads
from subprocess import PIPE
from subprocess import run

from sistema_tokenizador.configuraciones import EJECUTABLE_TOKENIZADOR

def hola_mundo(peticion):
  """Prueba inicial de configuración de servidor."""
  return HttpResponse("¡Hola mundo!")


@csrf_exempt
def tokenizar(peticion):
  """
  Ejecuta la operación de tokenización y regresa el token asignado.

  Ejemplo:
  curl --header "Content-Type: application/json" \
       --request POST \
       --data '{"pan" : "28045869693113314", "metodo" : "FFX"}' \
       http://127.0.0.1:8000/programa_tokenizador/tokenizar

  Documentación asociada:
  https://docs.python.org/3.5/library/subprocess.html#subprocess.run
  """
  objetoDePeticion = loads(peticion.body)
  pan = objetoDePeticion['pan']
  metodo = objetoDePeticion['metodo']
  resultado = run([EJECUTABLE_TOKENIZADOR, "-e", metodo, pan, "llave.txt"],
    stdout=PIPE)
  return HttpResponse(resultado.stdout)


@csrf_exempt
def detokenizar(peticion):
  """
  Ejecuta la operación de detokenización y regresa el pan asociado

  Ejemplo:
  curl --header "Content-Type: application/json" \
       --request POST \
       --data '{"token" : "28045851286256503", "metodo": "FFX"}' \
       http://127.0.0.1:8000/programa_tokenizador/detokenizar

  Documentación asociada:
  https://docs.python.org/3.5/library/subprocess.html#subprocess.run
  """
  objetoDePeticion = loads(peticion.body)
  token = objetoDePeticion['token']
  metodo = objetoDePeticion['metodo']
  resultado = run([EJECUTABLE_TOKENIZADOR, "-d", metodo, token, "llave.txt"],
    stdout=PIPE)
  return HttpResponse(resultado.stdout)


@csrf_exempt
def ejecutar(peticion):
  """
  Un SSH/Telnet/Cliente remoto con python. Solo por diversión.

  Un ejemplo:
  curl --header "Content-Type: application/json" \
       --request POST \
       --data 'open documentos_entregables/formato_de_seguimiento.pdf' \
       http://127.0.0.1:8000/ejecutar

  Y, cuando menos en la mac, abro el pdf del lado del servidor.
  """
  resultado = run(peticion.body.split(), stdout=PIPE)
  return HttpResponse(resultado.stdout)
