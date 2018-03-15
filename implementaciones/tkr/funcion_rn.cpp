/**
 * \file
 * \brief Definición de función RN de TKR2.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/funcion_rn.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include "../../utilidades/cabeceras/utilidades_matematicas.hh"
#include <cmath>
#include <vector>
#include <iostream>

using namespace Implementaciones;
using namespace std;

entero FuncionRN::mContador = 0;

/**
 * Iniclializa el apuntador a la función interna.
 *
 * \sa http://www.cplusplus.com/reference/cmath/log2/
 *     http://www.cplusplus.com/reference/cmath/ceil/
 */

FuncionRN::FuncionRN(
  FuncionInterna* funcionInterna,   /**< Apuntador a primitiva interna. */
  int longitudDeCadena,             /**< Longitud de cadena resultado. */
  int cardinalidadDeAlfabeto        /**< Cardinalidad del alfabeto usado. */
)
: mFuncionInterna {funcionInterna},
  mLongitudDeCadena {longitudDeCadena},
  mCardinalidadDeAlfabeto {cardinalidadDeAlfabeto},
  mLongitudDeBits {static_cast<int>(ceil(log2(mCardinalidadDeAlfabeto)))}
{
}

/**
 * Libera la memoria mantenida por el apuntador a función interna.
 */

FuncionRN::~FuncionRN()
{
  delete mFuncionInterna;
}

/**
 * Utiliza la función interna para generar una cadena de bits pseudoaleatoria;
 * después interpreta esa cadena con los datos miembro (la cardinalidad y
 * la longitud de la cadena) para regresar la cadena con el formato adecuado.
 *
 * \return Arreglo pseudoaleatorio con \ref mLongitudDeBits de longitud.
 */

Arreglo<int> FuncionRN::operar(const vector<int>& entrada)
{
  Arreglo<unsigned char> binarioAleatorio = mFuncionInterna->operar({mContador,
    static_cast<entero>(3 * mLongitudDeCadena * mLongitudDeBits)});
  Arreglo<unsigned char> binarioDistribuido = redistribuir(binarioAleatorio);
  Arreglo<int> resultado (mLongitudDeCadena);
  for (int i = 0, j = 0; i < mLongitudDeCadena; j++)
  {
    int numero = static_cast<int>(binarioDistribuido[j]);
    if (numero < mCardinalidadDeAlfabeto)
      resultado.colocar(i++, numero);
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
  Arreglo<unsigned char> resultado(static_cast<int>(floor(
    (8.0 / mLongitudDeBits) * original.obtenerNumeroDeElementos())));
  for (int i = 0, j = 0;
    i < resultado.obtenerNumeroDeElementos();
    j += (i % 2) ? 1 : 0, i++)
  {
    resultado.colocar(i, (original[j] >> (4 * (i % 2))) & mascara);
  }
  return resultado;
}
