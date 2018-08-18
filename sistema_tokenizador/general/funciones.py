"""
  funciones.py Funciones de parte pública de sitio.
  Proyecto Lovelace.
"""

import json
from django.http import HttpResponse
from sistema_tokenizador import utilidades
from sistema_tokenizador.configuraciones import DIRECTORIO_BASE
from sistema_tokenizador.general import negocio


def inicio (peticion):
  """
  Liga a archivo estático de página de inicio.

  Todas las urls de vistas principales pasan por aquí. index.html solamente
  contiene la aplicación de angular. Es el módulo de ngRoute, en el cliente,
  quien hace la resolución a un html en específico.
  """
  respuesta = open(\
    DIRECTORIO_BASE +
    'sistema_tokenizador/archivos_web/compilados/index.html')
  return HttpResponse(content = respuesta)


def iniciarSesion (peticion):
  """
  Valida las credenciales dadas para iniciar una sesión.

  En caso correcto, registra al usuario en la sesión y regresa el objeto del
  usuario; en caso incorrecto, regresa un http vacío.

  Ojo, lo que se guarda en la sesión y se regresa no es una instancia de
  Usuario, sino que es un diccionario con el correo y el id del tipo de usuario.
  El Usuario no es serializable por el atributo de la contraseña.
  """
  objetoDePeticion = json.loads(peticion.body)
  usuario = negocio.autenticar(objetoDePeticion)
  if usuario != None:
    usuarioSerializable = {
      'correo': usuario.correo,
      'tipoDeUsuario': usuario.tipoDeUsuario.pk};
    peticion.session['usuario'] = usuarioSerializable
    return HttpResponse(json.dumps(usuarioSerializable))
  else:
    return HttpResponse()


def cerrarSesion (peticion):
  """Elimina el objeto usuario de la sesión."""
  del peticion.session['usuario']
  return HttpResponse()
