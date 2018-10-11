"""
Funciones comunes de backend,
Tienda en línea.
Proyecto Lovelace.
"""

import django


def respuestaJSON (objeto):
  """Empaqueta el objeto dado como una respuesta HTTP con JSON.

  Ocupa los serializadores de django, que solo están pensados para los propios
  modelos de django; si se quiere serializar algo externo, mejor ocupar
  json.dumps.

  OJO: si el objeto dado no es iterable, es convertido a una lista
  con un solo elemento, para que sea posible serializarlo."""
  try:
    iterador = iter(objeto)
  except TypeError:
    objeto = [objeto]
  return django.http.HttpResponse(
    django.core.serializers.serialize("json", objeto))
