/**
 * \file
 * \brief Implementación de métodos concretos de un algoritmo tokenizador.
 */

#include "cabeceras/algoritmo_tokenizador.hh"

using namespace Implementaciones;

/**
 * Mapea los argumentos de esta operación (comunes a cualquier función con
 * inverso) a la operación abstracta de tokenización.
 *
 * \return resultado de operación de tokenización.
 */

Arreglo<int> AlgoritmoTokenizador::operar(
  /** Argumentos de entrada, se espera el PAN y la información adicional. */
  const vector<Arreglo<tipo>> &entrada
)
{
  return tokenizar(entrada[0], entrada[1]);
}

/**
 * Mapea los argumentos de esta operación (comunes a cualquier función con
 * inverso) a la operación abstracta de detokenización.
 *
 * \return Resultado de operación de detokenización.
 */

Arreglo<int> AlgoritmoTokenizador::deoperar(
  /** Argumentos de entrada, se espera el token y la información adicional. */
  const vector<Arreglo<tipo>> &entrada
)
{
  return detokenizar(entrada[0], entrada[1]);
}
