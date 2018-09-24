"""
funciones.py Funciones de parte pública de sitio,
Aplicación web de sistema tokenizador.
Proyecto Lovelace.
"""

import datetime
import django
import hashlib
import json
import _thread

import sistema_tokenizador.configuraciones as configuraciones
import sistema_tokenizador.programa_tokenizador as programa_tokenizador
import sistema_tokenizador.utilidades as utilidades

from .models.correo import Correo
from .models.estado_de_correo import EstadoDeCorreo
from .models.estado_de_usuario import EstadoDeUsuario
from .models.tipo_de_usuario import TipoDeUsuario
from .models.usuario import Usuario
from .models.vinculo import Vinculo
from ..general import negocio


################################################################################
# Funciones de archivos estáticos ##############################################
################################################################################


def inicio (peticion):
  """Liga a archivo estático de página de inicio.

  Todas las urls de vistas principales pasan por aquí. index.html solamente
  contiene la aplicación de angular. Es el módulo de ngRoute, en el cliente,
  quien hace la resolución a un html en específico."""

  respuesta = open(\
    configuraciones.DIRECTORIO_BASE +
    'sistema_tokenizador/archivos_web/compilados/index.html', 'rb')
  return django.http.HttpResponse(content = respuesta)


@utilidades.privilegiosRequeridos('cliente')
def control (peticion):
  """Liga a página de administración de tokens.

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
  de las utilidades."""

  return inicio(peticion)


@utilidades.privilegiosRequeridos('administrador')
def administracion (peticion):
  """Liga a página de administración.

  Redirige la petición a la función de inicio. Lo importante aquí es la
  necesidad de privilegios para poder pasar por aquí: solamente los
  actores de tipo administrador pueden ver esta página (id = 2).  """

  return inicio(peticion)


################################################################################
# Gestión de sesión ############################################################
################################################################################


def usuarioDeSesion (peticion):
  """ Regresa el usuario de la sesión.

  En caso de no existir, se regresa un http vacío.  """

  if 'usuario' in peticion.session:
    return django.http.HttpResponse(peticion.session['usuario'])
  else:
    return django.http.HttpResponse()


def iniciarSesion (peticion):
  """ Valida las credenciales dadas para iniciar una sesión.

  En caso correcto, registra al usuario en la sesión y regresa el objeto del
  usuario; en caso incorrecto, regresa un http con un código de error.  """

  objetoDePeticion = json.loads(peticion.body)
  usuario = negocio.autentificar(objetoDePeticion)
  if usuario != None:
    if usuario.tipoDeUsuario.nombre == 'administrador':
      peticion.session['usuario'] = \
        django.core.serializers.serialize("json", [usuario])
      return utilidades.respuestaJSON(usuario)
    elif usuario.correo.estadoDeCorreo.nombre == 'no verificado':
      return django.http.HttpResponse("1")
    elif usuario.estadoDeUsuario.nombre == 'en espera':
      return django.http.HttpResponse("2")
    elif usuario.estadoDeUsuario.nombre == 'rechazado':
      return django.http.HttpResponse("3")
    elif usuario.estadoDeUsuario.nombre == 'en lista negra':
      return django.http.HttpResponse("4")
    else:
      peticion.session['usuario'] = \
        django.core.serializers.serialize("json", [usuario])
      return utilidades.respuestaJSON(usuario)
  else:
    return django.http.HttpResponse("0")


def cerrarSesion (peticion):
  """Elimina el objeto usuario de la sesión."""
  del peticion.session['usuario']
  return django.http.HttpResponse()


################################################################################
# Operaciones de clientes ######################################################
################################################################################


def obtenerId (peticion):
  """Regresa el identificador del usuario en sesión."""
  usuario = None
  for objetoDescerializado \
    in django.core.serializers.deserialize("json", peticion.session['usuario']):
    usuario = objetoDescerializado
  return usuario.object.id


def operarCliente (peticion):
  """Función diccionario para operaciones sobre un cliente.

  Sirve como base para realizar las operaciones de
  registrar, actualizar y eliminar a un cliente.  """

  if(peticion.method == 'POST'):
    return registrarCliente(peticion)

  elif (peticion.method == 'PUT'):
    return actualizarCliente(peticion, obtenerId(peticion))

  elif (peticion.method == 'DELETE'):
    return eliminarCliente(peticion, obtenerId(peticion))


def registrarCliente (peticion):
  """Registra a un nuevo cliente en la base de datos.

  Registra a el cliente dado en la base de datos y envía un correo con
  el vínculo de verificación; en caso de éxito se regresa un 0; en
  caso de que el cliente ya exista en la base se regresa un 1.  """

  objetoDePeticion = json.loads(peticion.body)

  try:
    Correo.objects.get(correo = objetoDePeticion['correo'])
    return django.http.HttpResponse("1")
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
  negocio.enviarVinculoDeVerificacionDeRegistro(usuario)
  return django.http.HttpResponse("0")


@utilidades.privilegiosRequeridos('cliente')
def actualizarCliente (peticion, idDeCliente):
  """Actualiza los datos de un cliente en la base de datos.

  Actualiza al cliente dado en la base de datos y envía un correo con
  el vínculo de verificación; en caso de éxito se regresa un 0; en
  caso de que el cliente use un correo utilizado por otro usuario
  se regresa un 1."""

  objetoDePeticion = json.loads(peticion.body)
  cliente = Usuario.objects.get(pk = idDeCliente)

  try:
    correo = Correo.objects.get(correo = objetoDePeticion['correo'])
    if (str(cliente.correo) != objetoDePeticion['correo']):
      return django.http.HttpResponse("1")
  except Correo.DoesNotExist:
    pass

  # Insertar correo
  correo = Correo(
    correo = objetoDePeticion['correo'],
    contrasenia = hashlib.sha256(
      objetoDePeticion['contrasenia'].encode()).digest(),
    estadoDeCorreo = EstadoDeCorreo.objects.get(
      nombre = 'no verificado'),
    vinculo = None)
  correo.save()

  # Insertar usuario
  usuario = Usuario(
    pk = idDeCliente,
    correo = correo,
    tipoDeUsuario = Usuario.objects.get(
      pk = idDeCliente).tipoDeUsuario,
    estadoDeUsuario = Usuario.objects.get(
      pk = idDeCliente).estadoDeUsuario,
    contadorDeMalasAcciones = Usuario.objects.get(
      pk = idDeCliente).contadorDeMalasAcciones)

  usuario.save(force_update=True)

  # Si se cambio el correo, eliminar el correo viejo
  if (str(cliente.correo) != objetoDePeticion['correo']):
    Correo.objects.filter(correo = str(cliente.correo)).delete()
    negocio.enviarVinculoDeVerificacionDeActualizacion(usuario)
    return django.http.HttpResponse("0")
  else:
    correo.estadoDeCorreo = EstadoDeCorreo.objects.get(
      nombre = 'verificado')
    correo.save()
    return django.http.HttpResponse("2")


@utilidades.privilegiosRequeridos('cliente')
def eliminarCliente (peticion, idDeCliente):
  """Elimina al cliente dado.

  Elimina los datos de un cliente en la base de datos y todo lo
  referente a el."""

  cliente = Usuario.objects.get(pk = idDeCliente)
  Usuario.objects.filter(pk = idDeCliente).delete()
  Correo.objects.filter(correo = str(cliente.correo)).delete()
  programa_tokenizador.models.llave.Llave.objects.filter(
    usuario_id = idDeCliente).delete()
  programa_tokenizador.models.token.Token.objects.filter(
    usuario_id = idDeCliente).delete()

  return django.http.HttpResponse("0")


@utilidades.privilegiosRequeridos('cliente')
def eliminarTokens (peticion):
  """Elimina los tokens de un cliente."""
  programa_tokenizador.models.token.Token.objects.filter(
    usuario_id = obtenerId(peticion)).delete()
  return django.http.HttpResponse("0")


@utilidades.privilegiosRequeridos('cliente')
def iniciarRefrescoDeLlaves (peticion):
  """Inicia el refresco de llaves del usuario en sesión.

  Inicia el refresco de llaves, cambiando el estado del usuario,
  sus llaves y sus token mientras que se crean nuevas llaves.  """

  # Se cambia el estado de los tokens y las llaves
  idDeCliente = obtenerId(peticion)
  cliente = Usuario.objects.get(pk = idDeCliente)
  programa_tokenizador.models.token.Token.objects.filter(
    usuario_id = idDeCliente,
    estadoDeToken_id='actual').update(
    estadoDeToken_id='anterior')
  programa_tokenizador.models.llave.Llave.objects.filter(
    usuario_id = idDeCliente,
    estadoDeLlave_id='actual').update(
    estadoDeLlave_id='anterior')

  _thread.start_new_thread(
    programa_tokenizador.negocio.generarLlaves, (cliente,))

  # Se cambia el estado del cliente
  cliente.estadoDeUsuario = EstadoDeUsuario.objects.get(
    nombre = 'en cambio de llaves')
  cliente.save()

  return django.http.HttpResponse("0")


@utilidades.privilegiosRequeridos('cliente')
def terminarRefrescoDeLlaves (peticion):
  """Termina el refresco de llaves."""
  # Si el cliente no está en el estado correcto
  idDeCliente = obtenerId(peticion)
  cliente = Usuario.objects.get(pk = idDeCliente)
  if(str(cliente.estadoDeUsuario) != 'en cambio de llaves'):
    return django.http.HttpResponse("1")

  # Si hay tokens con estado anterior se notifica
  num = len(programa_tokenizador.models.token.Token.objects.filter(
    usuario_id = idDeCliente,
    estadoDeToken_id = 'anterior'))
  if(num > 0):
    return django.http.HttpResponse("2")

  # Eliminar las llaves anteriores del cliente
  programa_tokenizador.models.llave.Llave.objects.filter(
    usuario_id = idDeCliente,
    estadoDeLlave_id = 'anterior').delete()

  # Elimina tokens retokenizados
  programa_tokenizador.models.token.Token.objects.filter(
    usuario_id = idDeCliente,
    estadoDeToken = programa_tokenizador.models\
      .estado_de_token.EstadoDeToken.objects.get(
        nombre = 'retokenizado')).delete()

  # Se cambia el estado del cliente
  cliente.estadoDeUsuario = EstadoDeUsuario.objects.get(
    nombre = 'aprobado')
  cliente.save(force_update=True)

  return django.http.HttpResponse("0")


def verificarCorreoDeRegistro (peticion, vinculo):
  """Verifica el correo asociado al vínculo dado (registro)

  Hace la verificación de fecha y redirige al inicio. El mensaje
  mostrado en inicio depende de la verificación anterior."""
  correo = Correo.objects.get(
    vinculo = Vinculo.objects.get(
      vinculo = vinculo))

  # Anterior a 24 horas, error:
  if datetime.datetime.now() - correo.vinculo.fecha > \
    datetime.timedelta(hours = 24):

    usuario = Usuario.objects.get(
      correo = correo)
    referenciaAnterior = correo.vinculo
    correo.vinculo = None
    correo.save()
    usuario.delete()
    referenciaAnterior.delete()
    correo.delete()
    return django.http.HttpResponseRedirect('/?correo_no_verificado')

  # Operación correcta:
  else:
    correo.estadoDeCorreo = EstadoDeCorreo.objects.get(
      nombre = 'verificado')
    referenciaAnterior = correo.vinculo
    correo.vinculo = None
    correo.save()
    referenciaAnterior.delete()
    return django.http.HttpResponseRedirect('/?correo_verificado')


@utilidades.privilegiosRequeridos('cliente')
def verificarCorreoDeActualizacion (peticion, vinculo):
  """Verifica el correo asociado al vínculo dado (actualización)."""
  correo = Correo.objects.get(
    vinculo = Vinculo.objects.get(vinculo = vinculo))

  correo.estadoDeCorreo = EstadoDeCorreo.objects.get(
    nombre = 'verificado')
  referenciaAnterior = correo.vinculo
  correo.vinculo = None
  correo.save()
  referenciaAnterior.delete()
  return django.http.HttpResponseRedirect('/?nuevo_correo_verificado')


@utilidades.privilegiosRequeridos('cliente')
def verificarCriptoperiodo(peticion):
  """Verifica el criptoperiodo del usuario en sesión.

  Obtiene una llave en estado actual del usuario en sesión y verifica la
  vigencia de la llave. Regresa un 1 en caso de que la llave ya haya caducado. =
  en otro caso."""

  llave = programa_tokenizador.models.llave.Llave.objects.filter(
    usuario = Usuario.objects.get(
      pk = obtenerId(peticion)),
    estadoDeLlave = 'actual')[0]
  if datetime.datetime.now() - llave.fechaDeCreacion > \
    datetime.timedelta(days = llave.criptoperiodo):
    return django.http.HttpResponse("1")
  else:
    return django.http.HttpResponse("0")


################################################################################
# Operaciones de administradores ###############################################
################################################################################


@utilidades.privilegiosRequeridos('administrador')
def obtenerClientesEnEspera (peticion, pagina, limite):
  """Función de paginador para clientes en espera.

  Regresa el rango solicitado de clientes en espera con un correo
  verificado.

  Importante: aquí se muestra cómo hacer, con la API de django,
  una consulta con filtros en dos tablas distintas."""
  todos = Usuario.objects.filter(
    tipoDeUsuario = TipoDeUsuario.objects.get(
      nombre = 'cliente'),
    estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'en espera'),
    correo__in = Correo.objects.filter(
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'))).order_by('correo')
  return utilidades.respuestaJSON(
    todos[(pagina - 1) * limite : pagina * limite])


@utilidades.privilegiosRequeridos('administrador')
def obtenerTotalDeClientesEnEspera (peticion):
  """Regresa el total de clientes en espera con correo verificado."""
  todos = Usuario.objects.filter(
    tipoDeUsuario = TipoDeUsuario.objects.get(
      nombre = 'cliente'),
    estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'en espera'),
    correo__in = Correo.objects.filter(
      estadoDeCorreo = EstadoDeCorreo.objects.get(
        nombre = 'verificado'))).count()
  return django.http.HttpResponse(str(todos))


@utilidades.privilegiosRequeridos('administrador')
def obtenerClientesEnListaNegra (peticion, pagina, limite):
  """Función de paginador para clientes en lista negra.

  Regresa el rango solicitado de clientes en lista negra."""
  todos = Usuario.objects.filter(
    tipoDeUsuario = TipoDeUsuario.objects.get(
      nombre = 'cliente'),
    estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'en lista negra')).order_by('correo')
  return utilidades.respuestaJSON(
    todos[(pagina - 1) * limite : pagina * limite])


@utilidades.privilegiosRequeridos('administrador')
def obtenerTotalDeClientesEnListaNegra (peticion):
  """Regresa el total de clientes en lista negra."""
  todos = Usuario.objects.filter(
    tipoDeUsuario = TipoDeUsuario.objects.get(
      nombre = 'cliente'),
    estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'en lista negra')).count()
  return django.http.HttpResponse(str(todos))


@utilidades.privilegiosRequeridos('administrador')
def obtenerClientesAprobados (peticion, pagina, limite):
  """Función de paginador para clientes aprobados.

  Regresa el rango solicitados de clientes aprobados.

  El objeto Q es para hacer consultas con OR: «filter» y
  «get» funcionan con AND.

  https://docs.djangoproject.com/en/2.1/topics/db/queries/
  #complex-lookups-with-q-objects"""
  todos = Usuario.objects.filter(
    django.db.models.Q(tipoDeUsuario = TipoDeUsuario.objects.get(
      nombre = 'cliente')),
    django.db.models.Q(estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'aprobado')) |
    django.db.models.Q(estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'en cambio de llaves'))).order_by('correo')
  return utilidades.respuestaJSON(
    todos[(pagina - 1) * limite : pagina * limite])


@utilidades.privilegiosRequeridos('administrador')
def obtenerTotalDeClientesAprobados (peticion):
  """Regresa el total de clientes aprobados y en cambio de llaves."""
  todos = Usuario.objects.filter(
    django.db.models.Q(tipoDeUsuario = TipoDeUsuario.objects.get(
      nombre = 'cliente')),
    django.db.models.Q(estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'aprobado')) |
    django.db.models.Q(estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'en cambio de llaves'))).count()
  return django.http.HttpResponse(str(todos))


@utilidades.privilegiosRequeridos('administrador')
def aprobarCliente (peticion, idDeCliente):
  """Cambia el estado del cliente a aprobado y envía notificación."""
  cliente = Usuario.objects.get(pk = idDeCliente)
  cliente.estadoDeUsuario = EstadoDeUsuario.objects.get(
    nombre = 'aprobado')
  cliente.save()
  utilidades.enviarCorreo(cliente.correo.correo,
    "Aviso de aprobación de cuenta - Sistema tokenizador",
    """
    Estimado cliente:

    Su solicitud de cuenta ha sido aprobada. A partir de ahora
    ya puede iniciar sesión en el sistema y usar las opraciones
    de la API para generar tokens.

    Atentamente,
    Departamento de aprobación de cuentas,
    Sistema Tokenizador,
    Proyecto Lovelace.
    """)
  _thread.start_new_thread(
    programa_tokenizador.negocio.generarLlaves, (cliente,))
  return django.http.HttpResponse()


@utilidades.privilegiosRequeridos('administrador')
def rechazarCliente (peticion, idDeCliente):
  """Cambia el estado del cliente a rechazado y envía notificación."""
  cliente = Usuario.objects.get(pk = idDeCliente)
  cliente.estadoDeUsuario = EstadoDeUsuario.objects.get(
    nombre = 'rechazado')
  cliente.save()
  utilidades.enviarCorreo(cliente.correo.correo,
    "Aviso de rechazo de cuenta - Sistema tokenizador",
    """
    Estimado cliente:

    Su solicitud de cuenta ha sido rechazada.

    Atentamente,
    Departamento de aprobación de cuentas,
    Sistema Tokenizador,
    Proyecto Lovelace.
    """)
  return django.http.HttpResponse()


@utilidades.privilegiosRequeridos('administrador')
def vetarCliente (peticion, idDeCliente):
  """Cambia el estado del cliente a en lista negra y envía notificación."""
  cliente = Usuario.objects.get(pk = idDeCliente)
  cliente.estadoDeUsuario = EstadoDeUsuario.objects.get(
    nombre = 'en lista negra')
  cliente.save()
  utilidades.enviarCorreo(cliente.correo.correo,
    "Aviso de vetado de cuenta - Sistema tokenizador",
    """
    Estimado cliente:

    Su cuenta ha sido puesta en la lista negra debido a usos
    incorrectos del sistema.

    Atentamente,
    Departamento de aprobación de cuentas,
    Sistema Tokenizador,
    Proyecto Lovelace.
    """)
  return django.http.HttpResponse()


@utilidades.privilegiosRequeridos('administrador')
def desvetarCliente (peticion, idDeCliente):
  """Cambia el estado del cliente a aprobado y envía notificación.

  TODO:
  ¿Qué pasa con un cliente que antes de pasar a la lista negra se encontraba
  a mitad de un proceso de cambio de llaves? Técnicamente, aquí tendríamos que
  regresarlo a ese estado."""
  cliente = Usuario.objects.get(pk = idDeCliente)
  cliente.estadoDeUsuario = EstadoDeUsuario.objects.get(
    nombre = 'aprobado')
  cliente.save()
  utilidades.enviarCorreo(cliente.correo.correo,
    "Aviso de desvetado de cuenta - Sistema tokenizador",
    """
    Estimado cliente:

    Su cuenta ha sido restablecida. Ahora puede volver a iniciar sesión
    y utilizar la API para tokenizar y detokenizar.

    Atentamente,
    Departamento de aprobación de cuentas,
    Sistema Tokenizador,
    Proyecto Lovelace.
    """)
  return django.http.HttpResponse()

