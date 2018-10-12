"""
Configuración de URL de módulo de tienda.
Tienda en línea.
Proyecto Lovelace.
"""

import django

from ..tienda import funciones_web

urlpatterns = [

  # Operaciones de sesión
  django.urls.path('usuario_de_sesion',
    funciones_web.usuarioDeSesion),
  django.urls.path('iniciar_sesion',
    funciones_web.iniciarSesion),
  django.urls.path('cerrar_sesion',
    funciones_web.cerrarSesion),

  # Operaciones de carrito
  django.urls.path('carrito',
    funciones_web.operarCarrito),
  django.urls.path('compra',
    funciones_web.registrarCompra),

  # Operaciones sobre tarjetas
  django.urls.path('tarjetas',
    funciones_web.obtenerTarjetas),

  # Opeaciones sobre direcciones
  django.urls.path('direcciones',
    funciones_web.obtenerDirecciones),

]
