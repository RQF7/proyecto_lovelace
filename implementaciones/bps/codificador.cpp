/* ========================================================================= */
/* ============================== Codificador ============================== */
/* ======================================================================daz */

/**
 * Proyecto Lovelace.
 * 
 * \file
 * \brief Implementación de la clase del codificador.
 * 
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

Codificador::Codificador(){}

/* ========================================================================= */

Codificador::Codificador(vector<char> alfabeto)
{
  m_ALFABETO = alfabeto;
}

/* ========================================================================= */

void Codificador::setAlfabeto(vector<char> alfabeto)
{
  m_ALFABETO = alfabeto;
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
  x = find(m_ALFABETO.begin(),m_ALFABETO.end(),c)-m_ALFABETO.begin();
  
  if(x >= m_ALFABETO.size())
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
  return m_ALFABETO[c];
}

/* ========================================================================= */
/**
 * Esta función se encarga de regresar una cadena que esta formado de la 
 * decodificación de la suma modular de la codificación de cada uno de 
 * los caracteres de las cadenas dadas en los argumentos.
 */
string Codificador::sumaMod(string cadena_a, string cadena_b)
{
  if(cadena_a == "") return cadena_b;
  if(cadena_b == "") return cadena_a;

  Utilidades util;
  string salida{""};
  unsigned int tam, s;
  int a, b, offset;
  
  s = m_ALFABETO.size();
  offset = cadena_a.size() - cadena_b.size();
  
  if(offset <= 0) tam = cadena_a.size();
  else            tam = cadena_b.size();
 
  for(unsigned int i=0; i<tam; i++)
  {
    a = codificar(cadena_a[i]);
    b = codificar(cadena_b[i-offset]);
    salida += decodificar(util.mod(a+b,s));
  }
  
  return salida;
}

/* ========================================================================= */
/**
 * Esta función se encarga de regresar una cadena que esta formado de la 
 * decodificación de la resta modular de la codificación de cada uno de 
 * los caracteres de las cadenas dadas en los argumentos. 
 * (cadena_a - cadena_b)
 */
string Codificador::restaMod(string cadena_a, string cadena_b)
{
  if(cadena_a == "") return cadena_b;
  if(cadena_b == "") return cadena_a;

  Utilidades util;
  string salida{""};
  unsigned int tam, s;
  int a, b, offset;
  
  s = m_ALFABETO.size();
  offset = cadena_a.size() - cadena_b.size();
  
  if(offset <= 0) tam = cadena_a.size();
  else            tam = cadena_b.size();
 
  for(unsigned int i=0; i<tam; i++)
  {
    a = codificar(cadena_a[i]);
    b = codificar(cadena_b[i-offset]);
    salida += decodificar(util.mod(a-b,s));
  }
  
  return salida;
}

/* ========================================================================= */
