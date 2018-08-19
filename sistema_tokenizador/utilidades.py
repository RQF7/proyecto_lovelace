"""
  Funciones comunes de backend,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

from urllib.parse import urlparse, urlunparse
from django.http import HttpResponse, HttpResponseRedirect, QueryDict
from django.core import serializers
from urllib import parse
from functools import wraps


def respuestaJSON (objeto):
  """
  Empaqueta el objeto dado como una respuesta HTTP con JSON.

  Ocupa los serializadores de django, que solo están pensados para los propios
  modelos de django; si se quiere serializar algo externo, mejor ocupar
  json.dumps.

  TODO: ¿Por qué no estoy ocupando JSONResponse, de django?

  OJO: si el objeto dado no es iterable, es convertido a una lista
  con un solo elemento, para que sea posible serializarlo.
  """
  try:
    iterador = iter(objeto)
  except TypeError:
    objeto = [objeto]
  return HttpResponse(serializers.serialize("json", objeto))


def privilegiosRequeridos (tipoDeUsuario):
  """

  Definitivamente, mi función favorita.
  """
  def decorador (funcion):
    @wraps(funcion)
    def envolturaDePrivilegios(peticion, *argumentos, **argumentosEnDiccionario):
      """
      * https://docs.python.org/3.7/library/urllib.parse.html
      * entorno_virtual/lib/python3.6/site-packages/django/
        contrib/auth/decorators.py
      * entorno_virtual/lib/python3.6/site-packages/django/
        contrib/auth/views.py
      """
      if 'usuario' not in peticion.session:
        #from django.contrib.auth.views import redirect_to_login
        #return redirect_to_login(
        #    peticion.path, '/', 'siguiente')
        return HttpResponseRedirect('/?siguiente=' + peticion.path)

      elif peticion.session['usuario']['tipoDeUsuario'] != tipoDeUsuario:
        # TODO: terminar de definir requerimiento no funcional
        return HttpResponseRedirect('/?siguiente=' + peticion.path)

      else:
        return funcion(peticion, *argumentos, **argumentosEnDiccionario)
    return envolturaDePrivilegios
  return decorador
