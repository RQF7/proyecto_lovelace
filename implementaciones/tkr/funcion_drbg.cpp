/**
 * \file
 * \brief Definición de función que interactúa con DRBG, tipo TKR.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/funcion_drbg.hh"
#include "../drbg/cabeceras/drbg.hh"

using namespace Implementaciones;
using namespace std;

/**
 * Construye una nueva instancia con el generador dado. Los clientes son los
 * responsables de la gestión de la memoria.
 */

FuncionDRBG::FuncionDRBG(
  DRBG *drbg              /**< Referencia a generador pseudoaleatorio. */
)
: mDrbg {drbg}
{
}

/**
 * La idea es muy simple: pedir n bytes aleatorios e irles sacando
 * módulo 10 antes de ponerlos en el arreglo resultado.
 *
 * \return Token pseudoaleatorio.
 */

ArregloDeDigitos FuncionDRBG::operar(
  const vector<unsigned int>& entrada   /** Recibe la longitud del resultado. */
)
{
  Arreglo<unsigned char> aleatorios = mDrbg->operar({entrada[0]});
  ArregloDeDigitos resultado(entrada[0]);
  for (unsigned int i = 0; i < entrada[0]; i++)
    resultado[i] = aleatorios[i] % 10;
  return resultado;
}
