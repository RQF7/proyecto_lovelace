"""
Datos de prueba para tienda en línea.
Proyecto Lovelace.
"""

import os, sys, django, hashlib

sys.path.append(os.path.dirname(os.path.realpath(__file__)) + '/../')
os.environ['DJANGO_SETTINGS_MODULE'] = 'tienda.configuraciones'
django.setup()

from tienda.tienda.models.estado import Estado
from tienda.tienda.models.emisor import Emisor
from tienda.tienda.models.direccion import Direccion
from tienda.tienda.models.metodo import Metodo
from tienda.tienda.models.tarjeta import Tarjeta
from tienda.tienda.models.tipo_de_direccion import TipoDeDireccion
from tienda.tienda.models.tipo_de_tarjeta import TipoDeTarjeta
from tienda.tienda.models.usuario import Usuario

from tienda_catalogos import guardar


if __name__ == '__main__':

  usuarios = [
    Usuario(
      nombre = 'Cliente',
      correo = 'cliente@prueba.com',
      contrasenia = hashlib.sha256(b"123456").digest())]


  guardar(usuarios)

  direcciones = [
    Direccion(
      tipoDeDireccion = TipoDeDireccion.objects.get(
        nombre = 'Facturación'),
      estado = Estado.objects.get(nombre = 'Chiapas'),
      municipio = "Tapachula",
      colonia = "Regeneración Nacional",
      calle = "Lázaro Cárdenas",
      numeroInterior = 8,
      numeroExterior = 4,
      cp = "58697",
      activa = True),
    Direccion(
      tipoDeDireccion = TipoDeDireccion.objects.get(
        nombre = 'Facturación'),
      estado = Estado.objects.get(nombre = 'Estado de México'),
      municipio = "Ixtapan de la Sal",
      colonia = "Centro",
      calle = "Reforma",
      numeroInterior = 34,
      numeroExterior = 98,
      cp = "99835",
      activa = True),
    Direccion(
      tipoDeDireccion = TipoDeDireccion.objects.get(
        nombre = 'Punto de entrega'),
      estado = Estado.objects.get(nombre = 'Guerrero'),
      municipio = "Ometepec",
      colonia = "Obrera",
      calle = "Independencia",
      numeroInterior = 99,
      numeroExterior = 97,
      cp = "96783",
      activa = True),
    Direccion(
      tipoDeDireccion = TipoDeDireccion.objects.get(
        nombre = 'Punto de entrega'),
      estado = Estado.objects.get(nombre = 'Guerrero'),
      municipio = "Pilcaya",
      colonia = "El Platanar",
      calle = "Carretera a Tetipac",
      numeroInterior = 33,
      numeroExterior = 2,
      cp = "99835",
      activa = True)]

  guardar(direcciones)

  # !!
  # ¿Qué pasa con las bunas prácticas?
  # Debería ser «direcciones», no «direccion».
  usuarios[0].direccion.add(direcciones[2])
  usuarios[0].direccion.add(direcciones[3])
  usuarios[0].save()

  tarjetas = [
    Tarjeta(
      token = "123456789123456",
      terminacion = "8765",
      metodo = Metodo.objects.get(nombre = "FFX"),
      emisor = Emisor.objects.get(nombre = "VISA"),
      titular = "Ricardo Quezada Figueroa",
      direccion = direcciones[0],
      tipoDeTarjeta = TipoDeTarjeta.objects.get(nombre = "Débito"),
      activa = True),
    Tarjeta(
      token = "98765432123456",
      terminacion = "5698",
      metodo = Metodo.objects.get(nombre = "AHR"),
      emisor = Emisor.objects.get(nombre = "MasterCard"),
      titular = "Nombre de Prueba",
      direccion = direcciones[1],
      tipoDeTarjeta = TipoDeTarjeta.objects.get(nombre = "Débito"),
      activa = True)]

  guardar(tarjetas)
