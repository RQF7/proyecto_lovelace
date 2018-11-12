"""
Script de cron para verificaciones de expiración.
Aplicación web de sistema tokenizador.
Proyecto Lovelace.
"""

import django_cron

from ..models.estado_de_usuario import EstadoDeUsuario
from ..models.usuario import Usuario
from ...general import negocio


class ExpiracionDeLlaves (django_cron.CronJobBase):
  """Clase de trabajo de cron para verificaciones de expiraciones.

  Para que sea efectiva, debe de estar definidia en el arreglo CRON_CLASSES,
  en las configuraciones del proyecto."""


  RUN_EVERY_MINS = 60 * 24
  schedule = django_cron.Schedule(
    run_every_mins = RUN_EVERY_MINS)
  code = 'sistema_tokenizador.expiracion_de_llaves'


  def do(self):
    """Verificación de expiración de llaves.

    Hace la verificación para cada cliente aprobado de la base de datos. En caso
    necesario, envía correo con advertencia."""
    clientes = Usuario.objects.get(
      estadoDeUsuario = EstadoDeUsuario.objects.get(
        nombre = 'aprobado'))
    for cliente in clientes:
      if negocio.verificarCriptoperiodo(cliente):
        negocio.enviarRecordatorioDeRefresco(cliente)

