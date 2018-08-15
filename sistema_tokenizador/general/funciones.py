"""
  funciones.py Funciones de parte pública de sitio.
  Proyecto Lovelace.
"""

from django.core import serializers
from django.http import HttpResponse
from json import loads
from sistema_tokenizador.configuraciones import DIRECTORIO_BASE


def inicio(peticion):
  """Liga a archivo estático de página de inicio."""
  respuesta = open(\
    DIRECTORIO_BASE +
    'sistema_tokenizador/archivos_web/compilados/index.html')
  return HttpResponse(content = respuesta)
