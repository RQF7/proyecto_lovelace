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

from django.contrib import admin
from django.urls import path, include
from django.contrib.staticfiles.urls import staticfiles_urlpatterns

from .general import funciones as general
from .programa_tokenizador import funciones as programa_tokenizador

urlpatterns = [

  # Vistas
  path('', general.inicio, name = 'inicio'),
  path('documentación', general.inicio),
  path('control', general.control),
  path('administración', general.administracion),

  # Operaciones de sesión
  path('api/usuario_de_sesion', general.usuarioDeSesion),
  path('api/iniciar_sesion', general.iniciarSesion),
  path('api/cerrar_sesion', general.cerrarSesion),
  path('api/registrar_cliente', general.registrarCliente),
  path('api/verificar_correo/<vinculo>', general.verificarCorreo),

  # Operaciones de administración
  path('api/clientes_en_espera/<int:pagina>/<int:limite>',
    general.obtenerClientesEnEspera),
  path('api/total_de_clientes_en_espera',
    general.obtenerTotalDeClientesEnEspera),
  path('api/clientes_en_lista_negra/<int:pagina>/<int:limite>',
    general.obtenerClientesEnListaNegra),
  path('api/total_de_clientes_en_lista_negra',
    general.obtenerTotalDeClientesEnListaNegra),
  path('api/clientes_aprobados/<int:pagina>/<int:limite>',
    general.obtenerClientesAprobados),
  path('api/total_de_clientes_aprobados',
    general.obtenerTotalDeClientesAprobados),
  path('api/aprobar_cliente/<int:idDeCliente>',
    general.aprobarCliente),
  path('api/rechazar_cliente/<int:idDeCliente>',
    general.rechazarCliente),
  path('api/vetar_cliente/<int:idDeCliente>',
    general.vetarCliente),
  path('api/desvetar_cliente/<int:idDeCliente>',
    general.desvetarCliente),

  # Operaciones de programa tokenizador
  path('programa_tokenizador/tokenizar', programa_tokenizador.tokenizar),
  path('programa_tokenizador/detokenizar', programa_tokenizador.detokenizar),
  path('ejecutar', programa_tokenizador.ejecutar)

]

urlpatterns += staticfiles_urlpatterns()
