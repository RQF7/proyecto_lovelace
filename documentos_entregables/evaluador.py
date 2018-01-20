#!/usr/bin/python3
"""
Script para evaluar la salida de hunspell.
Proyecto Lovelace.

Recibe a través de una tubería (ver makefile) la salida de hunspell.
"""

if __name__ == '__main__':

  import fileinput

  aprobado = True
  numErrores = 0
  for cadena in fileinput.input():
    if cadena[0] == '&':
      print('Error: ', cadena[2:])
      aprobado = False
      numErrores += 1

  if aprobado:
    print('Evaluación terminada. Todo en orden.')
    exit(0)
  else:
    print('Evaluación terminada. ' + str(numErrores) + ' error(s).')
    exit(-1)
