"""
funciones.py Funciones para módulo de tienda,
Tienda en línea.
Proyecto Lovelace.
"""

import django
import json

from ..tienda import negocio

################################################################################
# Gestión de sesión ############################################################
################################################################################


def usuarioDeSesion (peticion):
  """ Regresa el usuario de la sesión.

  En caso de no existir, se regresa un http vacío."""

  if 'usuario' in peticion.session:
    return django.http.HttpResponse(peticion.session['usuario'])
  else:
    return django.http.HttpResponse()


def iniciarSesion (peticion):
  """Valida las credenciales dadas para iniciar una sesión.

  En caso correcto, registra al usuario en la sesión y regresa el objeto del
  usuario; en caso incorrecto, regresa un http con un código de error.

  Importante: esto funciona de forma distinta a las sesiones del sistema
  tokenizador; ahí se serializaba en la sesión una instancia directa del
  modelo; aquí no se puede hacer eso, dado que el modelo del usuario tiene la
  contraseña; en su lugar, se serializa un diccionario con el nombre y el
  correo del usuario en la sesión."""

  objetoDePeticion = json.loads(peticion.body)
  usuario = negocio.autentificar(objetoDePeticion)
  if usuario != None:
    #if usuario.tipoDeUsuario.nombre == 'administrador':
    #  peticion.session['usuario'] = \
    #    django.core.serializers.serialize("json", [usuario])
    #  return utilidades.respuestaJSON(usuario)
    #elif usuario.correo.estadoDeCorreo.nombre == 'no verificado':
    #  return django.http.HttpResponse("1")
    #elif usuario.estadoDeUsuario.nombre == 'en espera':
    #  return django.http.HttpResponse("2")
    #elif usuario.estadoDeUsuario.nombre == 'rechazado':
    #  return django.http.HttpResponse("3")
    #elif usuario.estadoDeUsuario.nombre == 'en lista negra':
    #  return django.http.HttpResponse("4")
    #else:
    peticion.session['usuario'] = \
      json.dumps({
        'nombre': usuario.nombre,
        'correo': usuario.correo})
    return django.http.HttpResponse(peticion.session['usuario'])
  else:
    return django.http.HttpResponse("0")


def cerrarSesion (peticion):
  """Elimina el objeto usuario de la sesión."""
  del peticion.session['usuario']
  return django.http.HttpResponse()
