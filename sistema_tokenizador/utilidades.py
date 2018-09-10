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
from smtplib import SMTP_SSL


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
  Fábrica de decoradores para vistas con privilegios.

  Permite decorar las funciones de vistas (todas las definiciones de funciones
  que hay en cualquier funciones.py) para reestringir el uso de esa función
  a cierto tipo de usuario. El argumento recibido es un entero que representa
  el identificador de los tipos de usuarios que deben poder acceder a la
  función.

  Si no hay ningún usuario en sesión o el usuario de sesión no tiene los
  privilegios necesarios, se regresa un 304 para obligar al cliente a ir
  a la pantalla de inicio de sesión.

  Las fábricas de decoradores se ven, en el código cliente, igual que
  un decorador normal. En su papel de fábrica, debe de regresar un decorador.
  Las fábricas de decoradores se utilizan para que las funciones decoradoras
  puedan recibir parámetros (en este caso el tipo de usuario de los
  privilegios). Cuando el decorador no recibe parámetros se pude utilizar
  sin la fábrica.

  Definitivamente, mi función favorita.
  """

  def decorador (funcion):

    @wraps(funcion)
    def envolturaDePrivilegios(peticion, *argumentos, **argumentosEnDiccionario):

      if 'usuario' not in peticion.session:
        return HttpResponseRedirect('/?siguiente=' + peticion.path)

      elif peticion.session['usuario']['tipoDeUsuario'] != tipoDeUsuario:
        return HttpResponseRedirect('/?siguiente=' + peticion.path)

      else:
        return funcion(peticion, *argumentos, **argumentosEnDiccionario)

    # Retorno de función decoradora, decorador.
    return envolturaDePrivilegios

  # Retorno de función fábrica, privilegiosRequeridos.
  return decorador


def enviarCorreo(destinatario, asunto, cuerpo):
  """
  """
  #servidor = SMTP_SSL('ricardo-quezada.159.65.96.59.xip.io', 465)
  #servidor.login()
  pass
