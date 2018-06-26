#!/usr/bin/python3

"""
\file
\brief Ejecutable para generar tablas y gráficas con comparaciones
de desempeño.

Existe una función para cada vista distinta. En la función principal solamente
se llaman a las respectivas funciones de reportes.

Proyecto Lovelace.
"""

from matplotlib import pyplot
from numpy import arange
from subprocess import PIPE
from subprocess import run

algoritmos = ['FFX', 'BPS', 'TKR', 'AHR', 'DRBG']
carpetaGeneral = 'reportes'
ejecutabeDePruebas = 'binarios/pruebas_desempenio'

def generarGraficaTiemposUnitarios(tokenizacion, detokenizacion):
  """
  https://matplotlib.org/gallery/lines_bars_and_markers/barchart.html
  """
  indices = arange(len(tokenizacion))
  ancho = 0.35
  figura, ejes = pyplot.subplots()
  barrasTokenizacion = ejes.bar(indices - ancho/2,
    tokenizacion,
    ancho,
    color='#444444',
    label='Tokenización')
  barrasDetokenizacion = ejes.bar(indices + ancho/2,
    detokenizacion,
    ancho,
    color='#777777',
    label='Detokenización')
  ejes.set_ylabel('Tiempos (microsegundos)')
  ejes.yaxis.set_label_coords(-0.12,0.5)
  #ejes.set_title('Tiempos unitarios de tokenización y detokenización')
  ejes.set_xticks(indices)
  ejes.set_xticklabels(tuple(algoritmos))
  ejes.legend(frameon=False)
  ejes.grid(axis='y',
    which='both',
    linewidth=0.2,
    color='#000000',
    alpha=1.0)
  ejes.tick_params(
    axis='both',          # changes apply to the x-axis
    which='both',      # both major and minor ticks are affected
    bottom=False,      # ticks along the bottom edge are off
    top=False,         # ticks along the top edge are off
    left=False,
    labelbottom=True) # labels along the bottom edge are off
  figura.savefig(carpetaGeneral + "/tiempos_unitarios.png",
    dpi=500)


def generarTiemposUnitarios():
  """Genera un archivo .tex con el contenido de la tabla con tiempos
     unitarios para cada algoritmo."""
  archivo = open(carpetaGeneral + '/tiempos_unitarios.tex', 'w')
  tiemposTokenizacion, tiemposDetokenizacion = (), ()
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
        tiemposTokenizacion += tuple([int(linea.split()[-1])])
        archivo.write(linea.split()[-1] + ' & ')
      elif ' descifrado' in linea:
        tiemposDetokenizacion += tuple([int(linea.split()[-1])])
        archivo.write(linea.split()[-1] + " \\\\\\hline \n")

  generarGraficaTiemposUnitarios(tiemposTokenizacion, tiemposDetokenizacion)


if __name__ == '__main__':

  run(['mkdir', '-p', carpetaGeneral])
  generarTiemposUnitarios()
