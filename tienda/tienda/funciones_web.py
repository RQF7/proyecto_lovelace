"""
funciones.py Funciones para módulo de tienda,
Tienda en línea.
Proyecto Lovelace.
"""

import datetime
import django
import json

import tienda.utilidades as utilidades
import tienda.libreria as libreria

from .models.compra import Compra
from .models.direccion import Direccion
from .models.paquete import Paquete
from .models.tarjeta import Tarjeta
from .models.usuario import Usuario
from ..tienda import negocio


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
    peticion.session['usuario'] = \
      json.dumps({
        'pk': usuario.pk,
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


def registrarCompra (peticion):
  """Registra una compra del cliete en sesión.

  TODO:
  * Agregar decorador de privilegios.
  """

  objetoDePeticion = json.loads(peticion.body)
  carrito = json.loads(peticion.session['carrito'])
  identificador = json.loads(peticion.session['usuario'])['pk']

  # Registrar compra
  compra = Compra(
    fecha = datetime.datetime.now(),
    tarjeta = Tarjeta.objects.get(pk = objetoDePeticion['tarjeta']),
    usuario = Usuario.objects.get(pk = identificador),
    direccion = Direccion.objects.get(pk = objetoDePeticion['direccion']))
  compra.save()

  # Registrar libros de compra
  for libro in carrito['libros']:
    paquete = Paquete(
      libro = libreria.models.libro.Libro.objects.get(pk = libro['pk']),
      compra = compra,
      numero = libro['cantidad'],
      precio_unitario = libro['precio'])
    paquete.save()

    # Restar de existencias
    paquete.libro.existencias -= paquete.numero;
    paquete.libro.save()

  del peticion.session['carrito']
  return django.http.HttpResponse()


################################################################################
# Operaciones sobre tarjetas ###################################################
################################################################################

def obtenerTarjetas (peticion):
  """Regresa arreglo con las tarjetas del usuario en sesión.

  TODO:
  *  El campo «tarjeta», del usuario, debería de ser «tarjetas»: por algo es un
     campo muchos a muchos.
  *  Falta agregar decorador con permisos.
  """
  identificador = json.loads(peticion.session['usuario'])['pk']
  tarjetas = Usuario.objects.get(pk = identificador).tarjeta.filter(
    activa = True)
  return utilidades.respuestaJSON(tarjetas)


################################################################################
# Operaciones sobre direcciones ################################################
################################################################################

def obtenerDirecciones (peticion):
  """Regresa arreglo con las direcciones del usuario en sesión.

  TODO:
  *  El campo «tdireccion», del usuario, debería de ser «direcciones»: por
     algo es un campo muchos a muchos.
  *  Falta agregar decorador con permisos.
  """
  identificador = json.loads(peticion.session['usuario'])['pk']
  direcciones = Usuario.objects.get(pk = identificador).direccion.filter(
    activa = True)
  return utilidades.respuestaJSON(direcciones)
