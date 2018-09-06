"""
  Estado inicial de base de datos,
  Aplicación web para sistema tokenizador.
  Proyecto Lovelace.

  Catálogos y registros no editables desde aplicación.
"""

import os, sys, django

sys.path.append(os.path.dirname(os.path.realpath(__file__)) + '/../')
os.environ['DJANGO_SETTINGS_MODULE'] = 'sistema_tokenizador.configuraciones'
django.setup()

from sistema_tokenizador.general.models.estado_de_usuario \
  import EstadoDeUsuario
from sistema_tokenizador.general.models.estado_de_correo \
  import EstadoDeCorreo
from sistema_tokenizador.general.models.tipo_de_usuario \
  import TipoDeUsuario
from sistema_tokenizador.programa_tokenizador.models.algoritmo \
  import Algoritmo
from sistema_tokenizador.programa_tokenizador.models.contador \
  import Contador
from sistema_tokenizador.programa_tokenizador.models.estado_de_llave \
  import EstadoDeLlave
from sistema_tokenizador.programa_tokenizador.models.estado_de_token \
  import EstadoDeToken
from sistema_tokenizador.programa_tokenizador.models.tipo_de_algoritmo \
  import TipoDeAlgoritmo


def guardar(modelos):
  """Guarda los modelos dados omitiendo errores de integridad
  (entradas duplicadas)."""
  for modelo in modelos:
    try:
      modelo.save()
    except django.db.utils.IntegrityError:
      print('Entrada duplicada: ' + str(modelo))


if __name__ == '__main__':

  tiposDeUsuario = [
    TipoDeUsuario(nombre = 'cliente'),
    TipoDeUsuario(nombre = 'administrador')]

  guardar(tiposDeUsuario)

  estadosDeUsuario = [
    EstadoDeUsuario(nombre = 'en espera'),
    EstadoDeUsuario(nombre = 'aprobado'),
    EstadoDeUsuario(nombre = 'rechazado'),
    EstadoDeUsuario(nombre = 'en cambio de llaves'),
    EstadoDeUsuario(nombre = 'en lista negra')]

  guardar(estadosDeUsuario)

  estadosDeToken = [
    EstadoDeToken(nombre = 'actual'),
    EstadoDeToken(nombre = 'anterior'),
    EstadoDeToken(nombre = 'retokenizado')]

  guardar(estadosDeToken)

  estadosDeLlave = [
    EstadoDeLlave(nombre = 'actual'),
    EstadoDeLlave(nombre = 'anterior')]

  guardar(estadosDeLlave)

  estadosDeCorreo = [
    EstadoDeCorreo(nombre = 'verificado'),
    EstadoDeCorreo(nombre = 'no verificado')]

  guardar(estadosDeCorreo)

  tiposDeAlgoritmos = [
    TipoDeAlgoritmo(nombre = 'reversible'),
    TipoDeAlgoritmo(nombre = 'irreversible')]

  guardar(tiposDeAlgoritmos)

  # TODO: verificar longitudes de llaves.
  algoritmos = [
    Algoritmo(
      nombre = 'FFX',
      longitudDeLlave = 16,
      tipoDeAlgoritmo = tiposDeAlgoritmos[0]),
    Algoritmo(
      nombre = 'BPS',
      longitudDeLlave = 16,
      tipoDeAlgoritmo = tiposDeAlgoritmos[0]),
    Algoritmo(
      nombre = 'TKR',
      longitudDeLlave = 16,
      tipoDeAlgoritmo = tiposDeAlgoritmos[1]),
    Algoritmo(
      nombre = 'AHR',
      longitudDeLlave = 32,
      tipoDeAlgoritmo = tiposDeAlgoritmos[1]),
    Algoritmo(
      nombre = 'DRBG',
      longitudDeLlave = 16,
      tipoDeAlgoritmo = tiposDeAlgoritmos[1]),
  ]

  guardar(algoritmos)

  contadores = [
    Contador(
      nombre = 'contador de tkr',
      valor = 0)]

  guardar (contadores)
