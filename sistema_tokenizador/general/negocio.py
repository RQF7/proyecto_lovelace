"""
Operaciones de negocio de módulo general,
Aplicación web de sistema tokenizador.
Proyecto Lovelace.
"""

import datetime
import hashlib

import sistema_tokenizador.configuraciones as configuraciones
import sistema_tokenizador.programa_tokenizador as programa_tokenizador
import sistema_tokenizador.utilidades as utilidades

from .models.correo import Correo
from .models.usuario import Usuario
from .models.vinculo import Vinculo


def autentificar (usuarioEnPeticion):
  """Valida el usuario dado (correo y contraseña).

  En caso de no existir, regresa None; en caso correcto,
  regresa el objeto del usuario."""
  try:
    return Usuario.objects.get(
      correo = Correo.objects.get(
        correo = usuarioEnPeticion['correo'],
        contrasenia = hashlib.sha256(
          usuarioEnPeticion['contrasenia'].encode('UTF-8')).digest()))
  except (Usuario.DoesNotExist, Correo.DoesNotExist):
    return None


def enviarVinculoDeVerificacion (usuario, tipo):
  """Crea un nuevo vínculo de verificación y lo envía por correo.

  Guarda en la base de datos un hash del correo más la hora
  actual. Envía el vínculo por correo al cliente.

  Técnicamente, poner tantos datos en el código (el mensaje del correo
  electrónico), es una mala práctica, o cuando menos en lenguajes compilados,
  pues un cambio en los datos obliga a recompilar. En este caso, como es
  lenguaje interpretado, no veo por qué sería algo malo."""

  fecha = datetime.datetime.utcnow()
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

    {0}/api/general/verificar_correo/{1}/{2}

    Atentamente,
    Departamento de verificación de cuentas,
    Sistema Tokenizador,
    Proyecto Lovelace.
    """.format(configuraciones.DOMINIO, tipo, usuario.correo.vinculo.vinculo))


def enviarVinculoDeVerificacionDeRegistro (usuario):
  enviarVinculoDeVerificacion (usuario, "registro")


def enviarVinculoDeVerificacionDeActualizacion (usuario):
  enviarVinculoDeVerificacion (usuario, "actualizacion")


def verificarCriptoperiodo (usuario):
  """Verifica el criptoperiodo del usuario dado.

  Obtiene una llave en estado actual del usuario dado y verifica la
  vigencia de la llave. Regresa verdadero en caso de que la llave ya haya
  caducado; falso en otro caso."""

  llave = programa_tokenizador.models.llave.Llave.objects.filter(
    usuario = usuario,
    estadoDeLlave = 'actual')[0]
  if datetime.datetime.now() - llave.fechaDeCreacion > \
    datetime.timedelta(days = llave.criptoperiodo):
    return True
  else:
    return False


def enviarRecordatorioDeRefresco (usuario):
  """Envía correo de advertencia de llaves expiradas."""
  utilidades.enviarCorreo(
    usuario.correo.correo,
    "Advertencia de llaves expiradas - Sistema tokenizador",
    """
    Estimado cliente:

    Sus llaves han expirado. Es necesario iniciar el proceso de refresco de
    llaves para retokenizar sus tokens.

    Atentamente,
    Departamento de gestión de llaves,
    Sistema Tokenizador,
    Proyecto Lovelace.
    """)
