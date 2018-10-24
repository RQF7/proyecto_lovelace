"""
Script para captura de aviso de correo de confirmación de registro.
Caso de prueba: tienda de libros en línea.
Proyecto Lovelace.
"""

import time, sys, os, django

# Importar entorno del proyecto:
sys.path.append(os.path.dirname(os.path.realpath(__file__)) + '/../../')
os.environ['DJANGO_SETTINGS_MODULE'] = 'tienda.configuraciones'
django.setup()

from captura_generica_pagina import CapturaGenericaPagina
from tienda.tienda.models.usuario import Usuario

class CapturaAvisoDeCorreo (CapturaGenericaPagina):
  """
  Captura para aviso de envío de correo de verificación de cuenta.
  """

  def __init__ (ego, url, rutaArchivo, nombre, correo):

    CapturaGenericaPagina.__init__(ego, url, rutaArchivo)
    ego.mCorreo = correo
    ego.mNombre = nombre


  def configuracionCapturaExtraGrande (ego):
    """
    Secuencia de configuración inicial.
    """

    CapturaGenericaPagina.configuracionCapturaExtraGrande(ego)
    botonRegistrarse = ego.mNavegador.find_element_by_id('botonRegistrarse')
    botonRegistrarse.click()
    time.sleep(0.5)

    inputDeNombre = ego.mNavegador.find_element_by_name('nombre')
    inputDeNombre.send_keys(ego.mNombre)
    time.sleep(0.5)

    inputDeCorreo = ego.mNavegador.find_element_by_name('correo')
    inputDeCorreo.send_keys(ego.mCorreo)
    time.sleep(0.5)

    inputDeContrasenia = ego.mNavegador.find_element_by_name('contrasenia')
    inputDeContrasenia.send_keys('12345678')
    time.sleep(0.5)

    inputDeConfirmacion = ego.mNavegador.find_element_by_name('confirmacion')
    inputDeConfirmacion.send_keys('12345678')
    time.sleep(0.5)

    botonAceptar = ego.mNavegador.find_element_by_id(
      'formularioBotonOperarUsuario')
    botonAceptar.click()
    time.sleep(0.5)


  def tomarCapturas (ego):
    """
    Paso de toma de capturas.
    """

    CapturaGenericaPagina.tomarCapturas(ego)
    usuario = Usuario.objects.get(correo = ego.mCorreo)
    usuario.delete()


if __name__ == '__main__':

  captura = CapturaAvisoDeCorreo(sys.argv[1], sys.argv[2],
    'UsuarioCapturas', 'capturas@prueba.com')
  captura.tomarCapturas()
