"""
  Script para captura de aviso de correo de confirmación,
  aplicación web de sistema tokenizador.
  Proyecto Lovelace.
"""

import time, sys, os, django

# Importar entorno del proyecto:
sys.path.append(os.path.dirname(os.path.realpath(__file__)) + '/../../')
os.environ['DJANGO_SETTINGS_MODULE'] = 'sistema_tokenizador.configuraciones'
django.setup()

from captura_generica_pagina import CapturaGenericaPagina
from sistema_tokenizador.general.models.correo import Correo
from sistema_tokenizador.general.models.usuario import Usuario
from sistema_tokenizador.general.models.vinculo import Vinculo

class CapturaAvisoDeCorreo (CapturaGenericaPagina):
  """
  Captura para aviso de envío de correo de verificación de cuenta.

  Sorescribe el comportamiento de una captura genérica de forma que antes
  de la toma de capturas se llegue a la vantana del aviso.
  """

  def __init__ (ego, url, rutaArchivo, usuario):
    """
    Contructor de clase-captura.

    Agrega un parámetro con el nombre de usuario a crear.
    """

    CapturaGenericaPagina.__init__(ego, url, rutaArchivo)
    ego.mUsuario = usuario


  def configuracionCapturaExtraGrande (ego):
    """
    Secuencia de configuración inicial.

    Supone que ya se encuentra en una de las dos páginas públicas (inicio
    o documentación); abre el formulario de registro, lo llena y lo envía,
    después de esto es cuando se toman las capturas.
    """

    CapturaGenericaPagina.configuracionCapturaExtraGrande(ego)
    botonRegistrarse = ego.mNavegador.find_element_by_id('botonRegistrarse')
    botonRegistrarse.click()
    inputDeCorreo = ego.mNavegador.find_element_by_name('correo')
    inputDeCorreo.send_keys(ego.mUsuario)
    inputDeContrasenia = ego.mNavegador.find_element_by_name('contrasenia')
    inputDeContrasenia.send_keys('12345678')
    inputDeConfirmacion = ego.mNavegador.find_element_by_name('confirmacion')
    inputDeConfirmacion.send_keys('12345678')
    botonAceptar = ego.mNavegador.find_element_by_id(
      'formularioBotonRegistrarCliente')
    botonAceptar.click()
    time.sleep(0.5)


  def tomarCapturas (ego):
    """
    Paso de toma de capturas.

    Ejecuta la secuencia de la superclase y después elimina de la base de
    datos el nuevo usuario; esto para poder ejecutar el script varias
    veces.

    Se suponía que esta función no se sobreescribiría. En estos casos es una
    ventaja el no saber cómo definir controles de acceso en python.
    """

    CapturaGenericaPagina.tomarCapturas(ego)
    usuario = Usuario.objects.get(
      correo = Correo.objects.get(correo = ego.mUsuario))
    correo = usuario.correo;
    usuario.delete()
    vinculo = correo.vinculo;
    correo.delete()
    vinculo.delete()


if __name__ == '__main__':

  captura = CapturaAvisoDeCorreo(sys.argv[1], sys.argv[2],
    'capturas@prueba.com')
  captura.tomarCapturas()
