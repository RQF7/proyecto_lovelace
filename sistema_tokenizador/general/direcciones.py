"""
Configuración de URL de módulo general.
Aplicación web de sistema tokenizador.
Proyecto Lovelace.
"""

import django

from ..general import funciones

urlpatterns = [

  # Operaciones de sesión
  django.urls.path('usuario_de_sesion',
    funciones.usuarioDeSesion),
  django.urls.path('iniciar_sesion',
    funciones.iniciarSesion),
  django.urls.path('cerrar_sesion',
    funciones.cerrarSesion),

  # Operaciones de cliente
  django.urls.path('operar_cliente',
    funciones.operarCliente),
  django.urls.path('verificar_correo/registro/<vinculo>',
    funciones.verificarCorreoDeRegistro),
  django.urls.path('verificar_correo/actualizacion/<vinculo>',
    funciones.verificarCorreoDeActualizacion),
  django.urls.path('iniciar_refresco_de_llaves',
    funciones.iniciarRefrescoDeLlaves),
  django.urls.path('terminar_refresco_de_llaves',
    funciones.terminarRefrescoDeLlaves),
  django.urls.path('eliminar_tokens',
    funciones.eliminarTokens),
  django.urls.path('verificar_criptoperiodo',
    funciones.verificarCriptoperiodo),

  # Operaciones de administración
  django.urls.path('clientes_en_espera/<int:pagina>/<int:limite>',
    funciones.obtenerClientesEnEspera),
  django.urls.path('total_de_clientes_en_espera',
    funciones.obtenerTotalDeClientesEnEspera),
  django.urls.path('clientes_en_lista_negra/<int:pagina>/<int:limite>',
    funciones.obtenerClientesEnListaNegra),
  django.urls.path('total_de_clientes_en_lista_negra',
    funciones.obtenerTotalDeClientesEnListaNegra),
  django.urls.path('clientes_aprobados/<int:pagina>/<int:limite>',
    funciones.obtenerClientesAprobados),
  django.urls.path('total_de_clientes_aprobados',
    funciones.obtenerTotalDeClientesAprobados),
  django.urls.path('aprobar_cliente/<int:idDeCliente>',
    funciones.aprobarCliente),
  django.urls.path('rechazar_cliente/<int:idDeCliente>',
    funciones.rechazarCliente),
  django.urls.path('vetar_cliente/<int:idDeCliente>',
    funciones.vetarCliente),
  django.urls.path('desvetar_cliente/<int:idDeCliente>',
    funciones.desvetarCliente)

]
