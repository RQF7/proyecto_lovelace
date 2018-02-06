#!/usr/bin/python3
"""
Pequeñas modificaciones a svgs de visual paradigm.
Proyecto Lovelace.
"""

if __name__ == '__main__':

  import sys, os

  ruta_origen = sys.argv[1]
  ruta_destino = ruta_origen.replace('svg', 'png')

  archivo_origen = open(ruta_origen, 'r')
  contador_linea_original = 0
  for linea in archivo_origen:
    contador_linea_original += 1
    if 'Powered ByVisual Paradigm Community Edition' in linea:
      break;

  linea_min = contador_linea_original - 2
  linea_max = contador_linea_original + 12

  archivo_origen.close()
  archivo_origen = open(ruta_origen, 'r')
  archivo_temporal = open('temporal.svg', 'w');
  contador_linea_destino = 0
  for linea in archivo_origen:
    contador_linea_destino += 1
    if contador_linea_destino < linea_min or contador_linea_destino > linea_max:
      archivo_temporal.write(linea)

  archivo_origen.close()
  archivo_temporal.close()

  os.system('mv temporal.svg ' + ruta_origen)
  os.system('inkscape --export-width=1000 --export-png=' + ruta_destino + ' ' + ruta_origen)
