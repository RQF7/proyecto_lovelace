/**
 * \file
 * \brief Implementación de la clase del codificador.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/codificador.hh"

#include "cabeceras/utilidades.hh"
#include <iostream>
#include <iomanip>
#include <vector>
#include <gmpxx.h>
#include <gmp.h>

using namespace std;

/* ========================================================================= */

Codificador::Codificador()
{
}

/* ========================================================================= */

Codificador::Codificador(vector<char> alfabeto)
{
  mAlfabeto = alfabeto;
}

/* ========================================================================= */

void Codificador::colocarAlfabeto(vector<char> alfabeto)
{
  mAlfabeto = alfabeto;
}

/* ========================================================================= */

/**
 * Esta función se encarga de obtener el carácter con valor entero
 * equivalente a la posición del carácter dado dentro del alfabeto
 * de la clase.
 */

char Codificador::codificar(char c)
{
  unsigned char x;
  x = find(mAlfabeto.begin(), mAlfabeto.end(), c) - mAlfabeto.begin();

  if (x >= mAlfabeto.size())
  {
    cout << "ERROR, caracteres inexistentes en el alfabeto.";
    cout << endl;
    exit(-1);
  }
  else return x;
}

/* ========================================================================= */

/**
 * Esta función sirve para obtener el carácter del alfabeto en la
 * posición del valor entero del carácter dado.
 */

char Codificador::decodificar(char c)
{
  return mAlfabeto[c];
}

/* ========================================================================= */

/**
 * Esta función se encarga de regresar una cadena que está formada de la
 * decodificación de la suma modular de la codificación de cada uno de
 * los caracteres de las cadenas dadas en los argumentos.
 */

string Codificador::sumaMod(string cadenaA, string cadenaB)
{
  if(cadenaA == "") return cadenaB;
  if(cadenaB == "") return cadenaA;

  Utilidades util;
  string salida{""};
  unsigned int tam, s;
  int a, b, offset;

  s = mAlfabeto.size();
  offset = cadenaA.size() - cadenaB.size();

  if (offset <= 0) tam = cadenaA.size();
  else             tam = cadenaB.size();

  for (unsigned int i = 0; i < tam; i++)
  {
    a = codificar(cadenaA[i]);
    b = codificar(cadenaB[i - offset]);
    salida += decodificar(util.mod(a + b, s));
  }

  return salida;
}

/* ========================================================================= */

/**
 * Esta función se encarga de regresar una cadena que está formada de la
 * decodificación de la resta modular de la codificación de cada uno de
 * los caracteres de las cadenas dadas en los argumentos.
 * (cadenaA - cadenaB)
 */

string Codificador::restaMod(string cadenaA, string cadenaB)
{
  if(cadenaA == "") return cadenaB;
  if(cadenaB == "") return cadenaA;

  Utilidades util;
  string salida{""};
  unsigned int tam, s;
  int a, b, offset;

  s = mAlfabeto.size();
  offset = cadenaA.size() - cadenaB.size();

  if(offset <= 0) tam = cadenaA.size();
  else            tam = cadenaB.size();

  for(unsigned int i = 0; i < tam; i++)
  {
    a = codificar(cadenaA[i]);
    b = codificar(cadenaB[i - offset]);
    salida += decodificar(util.mod(a - b, s));
  }

  return salida;
}
