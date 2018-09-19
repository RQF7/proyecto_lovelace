"""
  Operaciones de negocio de backend,
  Aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import hashlib, datetime
from .models.correo import Correo
from .models.estado_de_usuario import EstadoDeUsuario
from .models.usuario import Usuario
from .models.vinculo import Vinculo
from sistema_tokenizador import utilidades
from sistema_tokenizador.configuraciones import DOMINIO
from sistema_tokenizador.programa_tokenizador.models.token import Token

LIMITE_MALAS_ACCIONES = 10
INCREMENTO_TOKEN_INVALIDO = 1
INCREMENTO_TOKEN_INEXISTENTE = 3

def autentificar (usuarioEnPeticion):
  """
  Valida el usuario dado (correo y contraseña).

  En caso de no existir, regresa None; en caso correcto,
  regresa el objeto del usuario.
  """
  try:
    resultado = Usuario.objects.get(
      correo = Correo.objects.get(
        correo = usuarioEnPeticion['correo'],
        contrasenia = hashlib.sha256(
          usuarioEnPeticion['contrasenia'].encode('UTF-8')).digest()))
    return resultado
  except (Usuario.DoesNotExist, Correo.DoesNotExist):
    return None


def enviarVinculoDeVerificacion (usuario, tipo):
  """
  Crea un nuevo vínculo de verificación y lo envía por correo.

  Guarda en la base de datos un hash del correo más la hora
  actual. Envía el vínculo por correo al cliente.

  Técnicamente, poner tantos datos en el código (el mensaje del correo
  electrónico), es una mala práctica, o cuando menos en lenguajes compilados,
  pues un cambio en los datos obliga a recompilar. En este caso, como es
  lenguaje interpretado, no veo por qué sería algo malo.
  """

  fecha = datetime.datetime.now()
  hash = hashlib.sha256()
  hash.update(usuario.correo.correo.encode())
  hash.update(str(fecha).encode())
  vinculo = Vinculo(
    vinculo = hash.hexdigest(),
    fecha = fecha)
  vinculo.save()
  usuario.correo.vinculo = vinculo
  usuario.correo.save()
  utilidades.enviarCorreo(
    usuario.correo.correo,
    "Verificación de correo - Sistema tokenizador",
    """
    Estimado cliente:

    Para poder verificar su correo en el sistema tokenizador debe
    hacer clic en el siguiente vínculo:

    {0}/api/verificar_correo/{1}/{2}

    Atentamente,
    Departamento de verificación de cuentas,
    Sistema Tokenizador,
    Proyecto Lovelace.
    """.format(DOMINIO, tipo, usuario.correo.vinculo.vinculo))

def enviarVinculoDeVerificacionDeRegistro (usuario):
  enviarVinculoDeVerificacion (usuario, "registro")

def enviarVinculoDeVerificacionDeActualizacion (usuario):
  enviarVinculoDeVerificacion (usuario, "actualizacion")

def aumentarContadorDeMalasAcciones(cliente, incremento):
  """
  Incrementa el contador de malas acciones del cliente dado. Después, verifica
  que el contador no haya  sobre pasado el límite de males acciones; de ser así,
  cambia su estado a <<en lista negra>>.
  """

  cliente.contadorDeMalasAcciones = cliente.contadorDeMalasAcciones + incremento
  cliente.save()

  if cliente.contadorDeMalasAcciones > LIMITE_MALAS_ACCIONES:
    cliente.estadoDeUsuario = EstadoDeUsuario.objects.get(
      nombre = 'en lista negra')
    cliente.save()

def verificarUnicidadDePAN(PAN, cliente_id):
  """
  Verifica que el cliente indicado no tenga asociado el PAN señalado.

  Regresa verdadero o falso.
  """
  try:
    registro = Token.objects.get(
      pan = PAN,
      usuario_id = cliente_id)
  except (Token.DoesNotExist):
    return 1
  return 0

def validarToken(token):
  """
  Valida que el token ingresado sea un token válido:
    - Tiene una longitud entre 12 y 19 dígitos.
    - Valida el dígito verificador (mediante el algoritmo de Luhn) con desfase
      de uno.

    Regresa uno si es válido, cero si no.
  """

  numeroDeElementos = len(token)

  if numeroDeElementos < 12 or numeroDeElementos > 19:
    return 0

  if int(token[-1]) != ((utilidades.calcularAlgoritmoLuhn(token) + 1) % 10):
    return 0

  return 1
