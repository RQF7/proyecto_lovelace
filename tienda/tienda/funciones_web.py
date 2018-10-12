"""
funciones.py Funciones para módulo de tienda,
Tienda en línea.
Proyecto Lovelace.
"""

import django
import json
import datetime

from ..tienda import negocio
from .models.usuario import Usuario

################################################################################
# Gestión de sesión ############################################################
################################################################################


def usuarioDeSesion (peticion):
  """Regresa el usuario de la sesión.

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


################################################################################
# Operaciones de clientes ######################################################
################################################################################

def operarUsuario (peticion):
  """Función diccionario para operaciones sobre un usuario."""

  if(peticion.method == 'POST'):
    return registrarUsuario(peticion)

#  elif (peticion.method == 'PUT'):
#    return actualizarUsuario(peticion, obtenerId(peticion))
#
#  elif (peticion.method == 'DELETE'):
#    return eliminarUsuario(peticion, obtenerId(peticion))


def registrarUsuario (peticion):
  """Registra a un nuevo usuario en la base de datos.

  Registra al usuario dado en la base de datos y envía un correo con
  el vínculo de verificación

  Regresa
    0 en caso de exito.
    1 en caso de que el usuario ya exista.                 """

  usuarioEnPeticion = json.loads(peticion.body)

  # verifica si ya existe el usuario
  if negocio.existeUsuario(usuarioEnPeticion):
    return django.http.HttpResponse("1")

  # Guarda al usuario
  usuario = negocio.guardarUsuario(usuarioEnPeticion)

  # Envia el vinculo
  negocio.enviarVinculoDeVerificacion(usuario,"registro")

  return django.http.HttpResponse("0")


def verificarCorreoDeRegistro (peticion, vinculo):
  """Verifica el correo asociado al vínculo de registro dado, haciendo
  la verificación de fecha."""
  usuario = Usuario.objects.get(vinculo = vinculo)

  # Anterior a 72 horas, error:
  if datetime.datetime.now() - usuario.fecha > datetime.timedelta(hours = 72):
    usuario.delete()
    return django.http.HttpResponseRedirect('/?correo_no_verificado')

  # Operación correcta:
  else:
    usuario.verificado = 1
    usuario.vinculo = None
    usuario.save()
    return django.http.HttpResponseRedirect('/?correo_verificado')


################################################################################
# Operaciones de carrito #######################################################
################################################################################

def operarCarrito (peticion):
  """Gestión del recurso del carrito."""
  if peticion.method == 'GET':
    return obtenerCarrito(peticion)
  elif peticion.method == 'POST':
    return guardarCarrito(peticion)
  else:
    return django.http.HttpResponseNotAllowed()


def obtenerCarrito (peticion):
  """Regresa el carrito en sesión.

  En caso de no existir, regresa un HTTP vacío."""
  if 'carrito' in peticion.session:
    return django.http.HttpResponse(peticion.session['carrito'])
  else:
    return django.http.HttpResponse()


def guardarCarrito (peticion):
  """Guarda la representación del carrito en las variables de sesión."""
  peticion.session['carrito'] = peticion.body.decode('utf-8')
  return django.http.HttpResponse()
