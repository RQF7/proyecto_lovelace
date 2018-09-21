"""
  direcciones.py Configuración de urls del sistema.
  Proyecto Lovelace

  Documentación asociada:
  https://docs.djangoproject.com/en/2.0/topics/http/urls/

  Todas las URLs pasan por esta configuración. Las de vistas (las que en
  algún momento aparecen en la basa de url del navegador) se concentran en
  una sola función de python: general.inicio.

  En realidad es el módulo de angular ngRoute (en el cliente) el que se
  encarga de hacer la resolución (ver js/navegacion.configuracion.js).
"""

import django
from django.contrib.staticfiles.urls import staticfiles_urlpatterns

from .general import funciones as general
from .programa_tokenizador import funciones as programa_tokenizador

urlpatterns = [

  # Vistas
  django.urls.path('', general.inicio, name = 'inicio'),
  django.urls.path('documentación', general.inicio),
  django.urls.path('control', general.control),
  django.urls.path('administración', general.administracion),

  # Operaciones de sesión
  django.urls.path('api/usuario_de_sesion',
    general.usuarioDeSesion),
  django.urls.path('api/iniciar_sesion',
    general.iniciarSesion),
  django.urls.path('api/cerrar_sesion',
    general.cerrarSesion),
  django.urls.path('api/operar_cliente',
    general.operarCliente),
  django.urls.path('api/verificar_correo/registro/<vinculo>',
    general.verificarCorreoDeRegistro),
  django.urls.path('api/verificar_correo/actualizacion/<vinculo>',
    general.verificarCorreoDeActualizacion),
  django.urls.path('api/iniciar_refresco_de_llaves',
    general.iniciarRefrescoDeLlaves),
  django.urls.path('api/terminar_refresco_de_llaves',
    general.terminarRefrescoDeLlaves),
  django.urls.path('api/eliminar_tokens',
    general.eliminarTokens),

  # Operaciones de administración
  django.urls.path('api/clientes_en_espera/<int:pagina>/<int:limite>',
    general.obtenerClientesEnEspera),
  django.urls.path('api/total_de_clientes_en_espera',
    general.obtenerTotalDeClientesEnEspera),
  django.urls.path('api/clientes_en_lista_negra/<int:pagina>/<int:limite>',
    general.obtenerClientesEnListaNegra),
  django.urls.path('api/total_de_clientes_en_lista_negra',
    general.obtenerTotalDeClientesEnListaNegra),
  django.urls.path('api/clientes_aprobados/<int:pagina>/<int:limite>',
    general.obtenerClientesAprobados),
  django.urls.path('api/total_de_clientes_aprobados',
    general.obtenerTotalDeClientesAprobados),
  django.urls.path('api/aprobar_cliente/<int:idDeCliente>',
    general.aprobarCliente),
  django.urls.path('api/rechazar_cliente/<int:idDeCliente>',
    general.rechazarCliente),
  django.urls.path('api/vetar_cliente/<int:idDeCliente>',
    general.vetarCliente),
  django.urls.path('api/desvetar_cliente/<int:idDeCliente>',
    general.desvetarCliente),

  # Operaciones de programa tokenizador
  django.urls.path('programa_tokenizador/tokenizar',
    programa_tokenizador.tokenizar),
  django.urls.path('programa_tokenizador/detokenizar',
    programa_tokenizador.detokenizar),
  django.urls.path('programa_tokenizador/retokenizar',
    programa_tokenizador.retokenizar),
  django.urls.path('ejecutar',
    programa_tokenizador.ejecutar)

]

urlpatterns += staticfiles_urlpatterns()
