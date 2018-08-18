"""
  Funciones comúnes de backend,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from django.http import HttpResponse
from django.core import serializers

def respuestaJSON (objeto):
  """
  Empaqueta el objeto dado como una respuesta HTTP con JSON.

  Ocupa los serializadores de django, que solo están pensados para los propios
  modelos de django; si se quiere serializar algo externo, mejor ocupar
  json.dumps.

  OJO: si el objeto dado no es iterable, es convertido a una lista
  con un solo elemento, para que sea posible serializarlo.
  """
  try:
    iterador = iter(objeto)
  except TypeError:
    objeto = [objeto]
  return HttpResponse(serializers.serialize("json", objeto))
