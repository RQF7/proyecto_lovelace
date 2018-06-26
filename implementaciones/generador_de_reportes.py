#!/usr/bin/python3

"""
\file
\brief Ejecutable para generar tablas y gráficas con comparaciones
de desempeño.

Existe una función para cada vista distinta. En la función principal solamente
se llaman a las respectivas funciones de reportes.

Proyecto Lovelace.
"""

from subprocess import PIPE
from subprocess import run

algoritmos = ['FFX', 'BPS', 'TKR', 'AHR', 'DRBG']
carpetaGeneral = 'reportes'
ejecutabeDePruebas = 'binarios/pruebas_desempenio'

def generarTabla():
  """Genera un archivo .tex con el conrenido de la tabla con tiempos
     unitarios para cada algoritmo."""
  archivo = open(carpetaGeneral + '/tabla.tex', 'w')
  for algoritmo in algoritmos:
    resultado = run([ejecutabeDePruebas,
      '127.0.0.1',
      '3306',
      'administrador_lovelace_pruebas',
      'l0v3lac3-padmin',
      algoritmo,
      '1'],
      stdout=PIPE)
    archivo.write(algoritmo + ' & ')
    for linea in resultado.stdout.decode('UTF-8').splitlines():
      print(linea)
      if ' cifrado' in linea:
        archivo.write(linea.split()[-1] + ' & ')
      elif ' descifrado' in linea:
        archivo.write(linea.split()[-1] + " \\\\\\hline \n")


if __name__ == '__main__':

  run(['mkdir', '-p', carpetaGeneral])
  generarTabla()
