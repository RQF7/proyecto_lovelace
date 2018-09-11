"""
  funciones.py Funciones de parte pública de sitio,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import json, hashlib
from .models.correo import Correo
from .models.estado_de_correo import EstadoDeCorreo
from .models.estado_de_usuario import EstadoDeUsuario
from .models.tipo_de_usuario import TipoDeUsuario
from .models.usuario import Usuario
from .models.vinculo import Vinculo
from sistema_tokenizador import utilidades
from sistema_tokenizador.configuraciones import DIRECTORIO_BASE
from sistema_tokenizador.general import negocio
from django.http import HttpResponse, HttpResponseRedirect
from django.db.utils import IntegrityError
from django.core import serializers
from datetime import datetime, timedelta, timezone


def inicio (peticion):
  """
  Liga a archivo estático de página de inicio.

  Todas las urls de vistas principales pasan por aquí. index.html solamente
  contiene la aplicación de angular. Es el módulo de ngRoute, en el cliente,
  quien hace la resolución a un html en específico.
  """

  respuesta = open(\
    DIRECTORIO_BASE +
    'sistema_tokenizador/archivos_web/compilados/index.html', 'rb')
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
    return HttpResponse(peticion.session['usuario'])
  else:
    return HttpResponse()


def iniciarSesion (peticion):
  """
  Valida las credenciales dadas para iniciar una sesión.

  En caso correcto, registra al usuario en la sesión y regresa el objeto del
  usuario; en caso incorrecto, regresa un http con un código de error.
  """

  objetoDePeticion = json.loads(peticion.body)
  usuario = negocio.autentificar(objetoDePeticion)
  if usuario != None:
    if usuario.tipoDeUsuario.nombre == 'administrador':
      peticion.session['usuario'] = serializers.serialize("json", [usuario])
      return utilidades.respuestaJSON(usuario)
    elif usuario.correo.estadoDeCorreo.nombre == 'no verificado':
      return HttpResponse("1")
    elif usuario.estadoDeUsuario.nombre == 'en espera':
      return HttpResponse("2")
    elif usuario.estadoDeUsuario.nombre == 'rechazado':
      return HttpResponse("3")
    elif usuario.estadoDeUsuario.nombre == 'en lista negra':
      return HttpResponse("4")
    else:
      peticion.session['usuario'] = serializers.serialize("json", [usuario])
      return utilidades.respuestaJSON(usuario)
  else:
    return HttpResponse("0")


def cerrarSesion (peticion):
  """Elimina el objeto usuario de la sesión."""
  del peticion.session['usuario']
  return HttpResponse()


def registrarCliente (peticion):
  """
  Registra a un nuevo cliente en la base de datos

  Registra a el cliente dado en la base de datos y envía un correo con
  el vínculo de verificación; en caso de éxito se regresa un 0; en
  caso de que el cliente ya exista en la base se regresa un 1.
  """

  objetoDePeticion = json.loads(peticion.body)

  try:
    Correo.objects.get(correo = objetoDePeticion['correo'])
    return HttpResponse("1")
  except Correo.DoesNotExist:
    pass

  # Inserar correo
  correo = Correo(
    correo = objetoDePeticion['correo'],
    contrasenia = hashlib.sha256(
      objetoDePeticion['contrasenia'].encode()).digest(),
    estadoDeCorreo = EstadoDeCorreo.objects.get(
      nombre = 'no verificado'),
    vinculo = None)
  correo.save()

  usuario = Usuario(
    correo = correo,
    tipoDeUsuario = TipoDeUsuario.objects.get(
      nombre = 'cliente'),
    estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'en espera'),
    contadorDeMalasAcciones = 0)

  usuario.save()
  negocio.enviarVinculoDeVerificacion(usuario)
  return HttpResponse("0")


def verificarCorreo (peticion, vinculo):
  """
  Verifica el correo asociado al vínculo dado

  Hace la verificación de fecha y redirige al inicio. El mensaje
  mostrado en inicio depende de la verificación anterior.
  """
  correo = Correo.objects.get(
    vinculo = Vinculo.objects.get(
      vinculo = vinculo))

  # Anterior a 24 horas, error:
  if datetime.now(timezone.utc) - correo.vinculo.fecha > timedelta(hours = 24):
    usuario = Usuario.objects.get(
      correo = correo)
    correo.vinculo.delete()
    correo.delete()
    usuario.delete()
    return HttpResponseRedirect('/?correo_no_verificado')

  # Operación correcta:
  else:
    correo.estadoDeCorreo = EstadoDeCorreo.objects.get(
      nombre = 'verificado')
    referenciaAnterior = correo.vinculo
    correo.vinculo = None
    correo.save()
    referenciaAnterior.delete()
    return HttpResponseRedirect('/?correo_verificado')
