/**
 * \file
 * \brief Definición de un algoritmo tokenizador reversible.
 */

#include "cabeceras/algoritmo_tokenizador_reversible.hh"
#include "cabeceras/utilidades_tarjetas.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../utilidades/cabeceras/utilidades_matematicas.hh"

using namespace Implementaciones;

/**
 * Corta el PAN en tres partes: identificador de banco, número de cuenta
 * y dígito verificador. Solamente se pasa el número de cuenta al
 * método concreto de los implementadores. El token es el resultado de
 * concatenar el id del banco, el número de cuenta cifrado y el dígito
 * verificador (con un desfase de 1).
 *
 * \return Token del PAN dado.
 */

ArregloDeDigitos AlgoritmoTokenizadorReversible::tokenizarIntermedio(
  const ArregloDeDigitos& pan     /**< PAN a tokenizar */
)
{
  auto division = pan
    / Arreglo<unsigned int>{6, pan.obtenerNumeroDeElementos() - 1};
  auto temporal = static_cast<ArregloDeDigitos>(division[0])
    + tokenizar(static_cast<ArregloDeDigitos>(division[1]));
  return temporal + ArregloDeDigitos{modulo(algoritmoDeLuhn(temporal) + 1, 10)};
}

/**
 * Pasa al método concreto la fracción del token correspondiente al
 * número de cuenta. El PAN resultado se arma concatenando la salida
 * de la operación inversa del método concreto con el identificador
 * del banco y con el resultado del algoritmo de Luhn.
 *
 * \return PAN del token dado.
 */

ArregloDeDigitos AlgoritmoTokenizadorReversible::detokenizarIntermedio(
  const ArregloDeDigitos& token       /**< Token a detokenizar. */
)
{
  auto division = token
    / Arreglo<unsigned int>{6, token.obtenerNumeroDeElementos() - 1};
  auto temporal = static_cast<ArregloDeDigitos>(division[0])
    + detokenizar(static_cast<ArregloDeDigitos>(division[1]));
  return temporal + ArregloDeDigitos{algoritmoDeLuhn(temporal)};
}
