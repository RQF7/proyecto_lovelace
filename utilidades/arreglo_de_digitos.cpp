/**
 * \file
 * \brief Implementación de un arreglo de dígitos.
 */

#include "cabeceras/arreglo.hh"
#include "cabeceras/arreglo_de_digitos.hh"
#include "cabeceras/utilidades_matematicas.hh"
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

/**
 * Interpreta los caracteres de la cadena dada como un número en la base
 * dada. La cadena «564» pasa como constante 564ull y como arreglo {5, 6, 4}.
 *
 * \todo Lanzar excepción si el número interno se desborda.
 */

ArregloDeDigitos::ArregloDeDigitos(
  std::string cadena,                 /**< Representación en cadena. */
  int base                            /**< Base de número. */
)
: Arreglo<int> (cadena.size()),
  mCadena {cadena},
  mBase {base}
{
  for (int i = mNumeroDeElementos - 1, j = 0; i >= 0; i--, j++)
  {
    int digito = cadena[i] - 48;
    mNumero += digito * potencia<entero>(mBase, j);
    mArregloInterno[i] = digito;
  }
}

/**
 * Interpreta el número dado como una cadena en la base dada. El número
 * 564ull pasa a la cadena interna «564» y al arreglo como {5, 6, 4}.
 */

ArregloDeDigitos::ArregloDeDigitos(
  entero numero,                      /**< Representación numérica. */
  int base                            /**< Base de número. */
)
: Arreglo<int> (contarDigitos<entero>(numero, base)),
  mNumero {numero},
  mBase {base}
{
  for (int i = mNumeroDeElementos - 1; i >= 0; i--)
  {
    entero equivalentePotencia = potencia<entero>(mBase, i);
    int digito = floor(numero / equivalentePotencia);
    mArregloInterno[i] = digito;
    mCadena += digito + 48;
    numero -= digito * equivalentePotencia;
  }
}

/**
 * Imprime el arreglo de dígitos en el flujo dado por la referencia. Solamente
 * se pasa la cadena interna al flujo, sin agregar salto de línea.
 */

ostream& operator<<(
  ostream& flujo,                   /**< Referencia a flujo de escritura. */
  const ArregloDeDigitos& arreglo   /**< Referencia a arreglo a imprimir. */
)
{
  flujo << arreglo.mCadena;
  return flujo;
}
