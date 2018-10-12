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

  # Operaciones de cliente
  django.urls.path('operar_usuario',
    funciones_web.operarUsuario),
  django.urls.path('verificar_correo/registro/<vinculo>',
    funciones_web.verificarCorreoDeRegistro),

  # Operaciones de carrito
  django.urls.path('carrito',
    funciones_web.operarCarrito),
  django.urls.path('compra',
    funciones_web.registrarCompra),

  # Operaciones sobre tarjetas
  django.urls.path('tarjetas',
    funciones_web.obtenerTarjetas),
  django.urls.path('tarjeta/<int:idDeTarjeta>',
    funciones_web.operarTarjeta),

  # Opeaciones sobre direcciones
  django.urls.path('direcciones',
    funciones_web.obtenerDirecciones),
  django.urls.path('direccion/<int:idDeDireccion>',
    funciones_web.operarDireccion),

]
