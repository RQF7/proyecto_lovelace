"""
  funciones.py Funciones de parte pública de sitio,
  Aplicación web de sistema tokenizador.
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


@utilidades.privilegiosRequeridos(1)
def administracionDeTokens (peticion):
  """
  Liga a página de administración de tokens.

  Redirige la petición a la función de inicio. Lo importante aquí es la
  necesidad de privilegios para poder pasar por aquí: solamente los
  actores de tipo usuario pueden ver esta página (id = 1).

  Esta es la primera función que usa la notación de decoradores de python
  (la llamada a la función decoradora con un «@» antes de la definición
  decorada). La escritura del arroba es pura azúcar a nivel de sitaxis; es
  equivalente a esto:

    def administracionDeTokens (peticion):
      return inicio(peticion)
    administracionDeTokens =
      utilidades.privilegiosRequeridos(administracionDeTokens, 1)

  Más sobre el propio decorador en su definición, esto es, en el archivo
  de las utilidades.
  """

  return inicio(peticion)


@utilidades.privilegiosRequeridos(2)
def administracion (peticion):
  """
  Liga a página de administración.

  Redirige la petición a la función de inicio. Lo importante aquí es la
  necesidad de privilegios para poder pasar por aquí: solamente los
  actores de tipo administrador pueden ver esta página (id = 2).
  """

  return inicio(peticion)


def usuarioDeSesion (peticion):
  """
  Regresa el usuario de la sesión.

  En caso de no existir, se regresa un http vacío.
  """

  if 'usuario' in peticion.session:
    return HttpResponse(json.dumps(peticion.session['usuario']))
  else:
    return HttpResponse()


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
  usuario = negocio.autentificar(objetoDePeticion)
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
