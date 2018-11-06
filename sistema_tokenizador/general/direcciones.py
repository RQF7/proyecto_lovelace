"""
Configuración de URL de módulo general.
Aplicación web de sistema tokenizador.
Proyecto Lovelace.
"""

import django

from ..general import funciones_web

urlpatterns = [

  # Operaciones de sesión
  django.urls.path('usuario_de_sesion',
    funciones_web.usuarioDeSesion),
  django.urls.path('iniciar_sesion',
    funciones_web.iniciarSesion),
  django.urls.path('cerrar_sesion',
    funciones_web.cerrarSesion),

  # Operaciones de cliente
  django.urls.path('operar_cliente',
    funciones_web.operarCliente),
  django.urls.path('verificar_correo/registro/<vinculo>',
    funciones_web.verificarCorreoDeRegistro),
  django.urls.path('verificar_correo/actualizacion/<vinculo>',
    funciones_web.verificarCorreoDeActualizacion),
  django.urls.path('iniciar_refresco_de_llaves',
    funciones_web.iniciarRefrescoDeLlaves),
  django.urls.path('terminar_refresco_de_llaves',
    funciones_web.terminarRefrescoDeLlaves),
  django.urls.path('eliminar_tokens',
    funciones_web.eliminarTokens),
  django.urls.path('verificar_criptoperiodo',
    funciones_web.verificarCriptoperiodo),

  # Operaciones de administración
  django.urls.path('clientes_en_espera/<int:pagina>/<int:limite>',
    funciones_web.obtenerClientesEnEspera),
  django.urls.path('total_de_clientes_en_espera',
    funciones_web.obtenerTotalDeClientesEnEspera),
  django.urls.path('clientes_en_lista_negra/<int:pagina>/<int:limite>',
    funciones_web.obtenerClientesEnListaNegra),
  django.urls.path('total_de_clientes_en_lista_negra',
    funciones_web.obtenerTotalDeClientesEnListaNegra),
  django.urls.path('clientes_aprobados/<int:pagina>/<int:limite>',
    funciones_web.obtenerClientesAprobados),
  django.urls.path('total_de_clientes_aprobados',
    funciones_web.obtenerTotalDeClientesAprobados),
  django.urls.path('aprobar_cliente/<int:idDeCliente>',
    funciones_web.aprobarCliente),
  django.urls.path('rechazar_cliente/<int:idDeCliente>',
    funciones_web.rechazarCliente),
  django.urls.path('vetar_cliente/<int:idDeCliente>',
    funciones_web.vetarCliente),
  django.urls.path('desvetar_cliente/<int:idDeCliente>',
    funciones_web.desvetarCliente)

]
