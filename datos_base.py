"""
  Estado inicial de base de datos,
  Aplicación web para sistema tokenizador.
  Proyecto Lovelace.

  Catálogos y registros no editables desde aplicación.

  TODO: hacer que esto funcione en cualquier otro lugar que no sea la carpeta
  raíz del proyecto. En la raíz solamente van configuraciones.
"""

import os, django

os.environ['DJANGO_SETTINGS_MODULE'] = 'sistema_tokenizador.configuraciones'
django.setup()

from sistema_tokenizador.general.models.tipo_de_usuario import TipoDeUsuario


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
    TipoDeUsuario(nombre = 'usuario'),
    TipoDeUsuario(nombre = 'administrador')]

  guardar(tiposDeUsuario)
