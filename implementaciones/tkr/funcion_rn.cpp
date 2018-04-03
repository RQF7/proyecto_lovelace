/**
 * \file
 * \brief Definición de función RN de TKR2.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/funcion_rn.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../utilidades/cabeceras/utilidades_matematicas.hh"
#include <cmath>
#include <vector>
#include <iostream>

using namespace Implementaciones;
using namespace std;

/**
 * Iniclializa el apuntador a la función interna.
 *
 * \sa http://www.cplusplus.com/reference/cmath/log2/
 *     http://www.cplusplus.com/reference/cmath/ceil/
 */

FuncionRN::FuncionRN(
  FuncionInterna* funcionInterna,      /**< Apuntador a primitiva interna. */
  CDV* baseDeDatos,                    /**< Acceso a datos. */
  unsigned int longitudDeCadena,       /**< Longitud de cadena resultado. */
  unsigned int cardinalidadDeAlfabeto  /**< Cardinalidad del alfabeto usado. */
)
: mFuncionInterna {funcionInterna},
  mBaseDeDatos {baseDeDatos},
  mLongitudDeCadena {longitudDeCadena},
  mCardinalidadDeAlfabeto {cardinalidadDeAlfabeto},
  mLongitudDeBits {static_cast<unsigned int>(ceil(log2(mCardinalidadDeAlfabeto)))},
  mContador {baseDeDatos->obtenerContador("contador de tkr")}
{
}

/**
 * Libera la memoria mantenida por el apuntador a función interna. Actualiza
 * el valor del contador en la base de datos. No se libera el acceso a
 * la base dado que este apuntador siempre es compartido con TKR (es ahí en
 * donde se libera).
 */

FuncionRN::~FuncionRN()
{
  mBaseDeDatos->colocarContador("contador de tkr", mContador);
  delete mFuncionInterna;
}

/**
 * Utiliza la función interna para generar una cadena de bits pseudoaleatoria;
 * después interpreta esa cadena con los datos miembro (la cardinalidad y
 * la longitud de la cadena) para regresar la cadena con el formato adecuado.
 *
 * \return Arreglo pseudoaleatorio con \ref mLongitudDeBits de longitud.
 */

ArregloDeDigitos FuncionRN::operar(const vector<unsigned int>& entrada)
{
  Arreglo<unsigned char> binarioAleatorio = mFuncionInterna->operar({mContador,
    static_cast<entero>(3 * mLongitudDeCadena * mLongitudDeBits)});
  Arreglo<unsigned char> binarioDistribuido = redistribuir(binarioAleatorio);
  ArregloDeDigitos resultado (mLongitudDeCadena);
  for (unsigned int i = 0, j = 0; i < mLongitudDeCadena; j++)
  {
    unsigned int numero = static_cast<unsigned int>(binarioDistribuido[j]);
    if (numero < mCardinalidadDeAlfabeto)
      resultado[i++] = numero;
  }
  mContador++;
  return resultado;
}

/**
 * Redistribución de bytes: en cada byte del arreglo resultado se colocan
 * solamente mLongitudDeBits. Por ejemplo, suponiendo una cardinalidad de
 * 10, la longitud del arreglo retornado es del doble: en cada byte del
 * resultado se colocan 4 bits del origen.
 *
 * \todo De moemnto solo funciona suponiendo que \ref mCardinalidadDeAlfabeto
 * es igual a 10 (4 bits por número). No es muy complicado portarlo a una
 * cardinalidad que sea múltiplo de 8. El problema está cuando la longitud
 * de los bits necesarios para cada dígito no es múltiplo de 8, pues entonces
 * hay que llevar un estado para poder juntar los últimos bits de un byte con
 * los primeros del próximo (no es trivial).
 *
 * \return Redistribución de bytes.
 */

Arreglo<unsigned char> FuncionRN::redistribuir(
  const Arreglo<unsigned char> &original    /**< Acomodo de bytes original. **/
)
{
  unsigned char mascara = 15;
  Arreglo<unsigned char> resultado(static_cast<unsigned int>(floor(
    (8.0 / mLongitudDeBits) * original.obtenerNumeroDeElementos())));
  for (unsigned int i = 0, j = 0;
    i < resultado.obtenerNumeroDeElementos();
    j += (i % 2) ? 1 : 0, i++)
  {
    resultado[i] = (original[j] >> (4 * (i % 2))) & mascara;
  }
  return resultado;
}
