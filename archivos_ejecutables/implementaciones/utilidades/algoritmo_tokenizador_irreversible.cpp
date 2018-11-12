/**
 * \file
 * \brief Definición de un algoritmo tokenizador irrreversible.
 */

#include "cabeceras/algoritmo_tokenizador_irreversible.hh"
#include "cabeceras/utilidades_tarjetas.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"

using namespace Implementaciones;

/**
 * Solo manda a llamar a la operación de tokenización de las clases concretas
 * pasándole todo el PAN.
 *
 * \return Token del PAN dado.
 */

ArregloDeDigitos AlgoritmoTokenizadorIrreversible::tokenizarIntermedio(
  const ArregloDeDigitos& pan   /**< PAN a tokenizar */
)
{
  return tokenizar(pan);
}

/**
 * Solo manda a llamar a la operación de detokenización de las clases concretas
 * pasándole todo el token.
 *
 * \return PAN del token dado.
 */

ArregloDeDigitos AlgoritmoTokenizadorIrreversible::detokenizarIntermedio(
  const ArregloDeDigitos& token     /**< Token a detokenizar. */
)
{
  return detokenizar(token);
}
