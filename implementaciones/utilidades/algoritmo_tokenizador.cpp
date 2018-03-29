/**
 * \file
 * \brief Implementación de métodos concretos de un algoritmo tokenizador.
 */

#include "cabeceras/algoritmo_tokenizador.hh"
#include "cabeceras/utilidades_tarjetas.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include <vector>

using namespace Implementaciones;
using namespace std;

/**
 * Mapea los argumentos de esta operación (comunes a cualquier función con
 * inverso) a la operación abstracta de tokenización.
 *
 * Valida la entrada con el algoritmo de Luhn. Corta el PAN para cifrar
 * solamente el número de cuenta. Recalcula el dígito verificador.
 *
 * \throw TarjetaMalFormada Si la longitud no es la adecuada [12, 19] o el
 * dígito verificador es erroneo.
 *
 * \return resultado de operación de tokenización.
 */

ArregloDeDigitos AlgoritmoTokenizador::operar(
  const vector<ArregloDeDigitos> &entrada
)
{
  validarEntrada(entrada[0]);
  auto division = entrada[0]
    / Arreglo<unsigned int>{6, entrada[0].obtenerNumeroDeElementos() - 1};
  auto temporal = static_cast<ArregloDeDigitos>(division[0])
    + tokenizar(static_cast<ArregloDeDigitos>(division[1]));
  return temporal + ArregloDeDigitos{algoritmoDeLuhn(temporal) + 1};
}

/**
 * Mapea los argumentos de esta operación (comunes a cualquier función con
 * inverso) a la operación abstracta de detokenización.
 *
 * Valida la entrada con el algoritmo de Luhn. Corta el token para descifrar
 * solamente lo que corresponda al número de cuenta. Recalcula el
 * dígito verificador.
 *
 * \throw TarjetaMalFormada Si la longitud no es la adecuada [12, 19] o el
 * dígito verificador es erroneo.
 *
 * \return Resultado de operación de detokenización.
 */

ArregloDeDigitos AlgoritmoTokenizador::deoperar(
  const vector<ArregloDeDigitos> &entrada
)
{
  validarEntrada(entrada[0], 1);
  auto division = entrada[0]
    / Arreglo<unsigned int>{6, entrada[0].obtenerNumeroDeElementos() - 1};
  auto temporal = static_cast<ArregloDeDigitos>(division[0])
    + detokenizar(static_cast<ArregloDeDigitos>(division[1]));
  return temporal + ArregloDeDigitos{algoritmoDeLuhn(temporal)};
}

/**
 * Valida la entrada del algoritmo tokenizador (PANs o tokens). Primero
 * verifica que la longitud esté entro los 12 y 19 caracteres y después
 * valida el dígito verificador. Para esto último utiliza el desfase dado:
 * un PAN válido no tiene desfase, mientras que los tokens tienen una unidad
 * de desfase.
 *
 * \throw TarjetaMalFormada Si la longitud no es la adecuada [12, 19] o el
 * dígito verificador es erroneo.
 */

void AlgoritmoTokenizador::validarEntrada(
  const ArregloDeDigitos& arreglo,          /**< Elemento a validar. */
  int desfaseDeDigitoVerificador            /**< Desfase de verificador. */
)
{
  int numeroDeElementos = arreglo.obtenerNumeroDeElementos();
  if (numeroDeElementos < 12 || numeroDeElementos > 19)
    throw TarjetaMalFormada{"La longitud debe de ser entre 12 y 19 dígitos"};

  int verifiacion = algoritmoDeLuhn(arreglo, true);
  if (arreglo[-1] != verifiacion + desfaseDeDigitoVerificador)
    throw TarjetaMalFormada{"Dígito de verificación inválido"};
}
