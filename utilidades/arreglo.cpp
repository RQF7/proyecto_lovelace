/**
 * \file
 * \brief Especializaciones de la clase Arreglo.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/arreglo.hh"
#include <iostream>

using namespace std;

/**
 * Algoritmo de suma entre los dos arreglos de bytes dados. OJO: no se trata de
 * una suma bit a bit, sino que es a nivel de bytes; esto es fácilmente
 * generalizable a otros tipos de datos: int, long long int.
 *
 * La longitud del resultado es la misma que los operandos, por lo que no
 * se toma en cuenta el último acarreo. Esto porque en el contexto de uso
 * inicial (las funciones de derivación de los DRGBs) el resultado debe
 * estar modulado a esta longitud.
 */

Arreglo<unsigned char> operator+(
  const Arreglo<unsigned char>& arregloUno, /**< Primer operando. */
  const Arreglo<unsigned char>& arregloDos  /**< Segundo operando. */
)
{
  unsigned int longitudMax = (arregloUno.obtenerNumeroDeElementos() >
    arregloDos.obtenerNumeroDeElementos()) ?
    arregloUno.obtenerNumeroDeElementos() :
    arregloDos.obtenerNumeroDeElementos();
  unsigned int longitudMin = (arregloUno.obtenerNumeroDeElementos() <
    arregloDos.obtenerNumeroDeElementos()) ?
    arregloUno.obtenerNumeroDeElementos() :
    arregloDos.obtenerNumeroDeElementos();
  bool lado {(arregloUno.obtenerNumeroDeElementos() >
    arregloDos.obtenerNumeroDeElementos()) ? true : false};
  Arreglo<unsigned char> resultado (longitudMax);
  unsigned int acarreo = 0;
  if (longitudMax != longitudMin)
    resultado.colocarConstante(0);
  for (unsigned int i = 0; i < longitudMax; i++)
  {
    int suma = (i < longitudMin) ?
      arregloUno[i] + arregloDos[i] + acarreo :
      (lado) ? arregloUno[i] + acarreo : arregloDos[i] + acarreo;
    int residuo = modulo(suma, 256);
    acarreo = floor(suma / 256);
    resultado[i] = residuo;
  }
  return resultado;
}

/**
 * Impresión de un arreglo de bits. No se aplica ningún modificador de
 * flujo (hex, dec), sino que se espera que el usuario lo aplque justo antes
 * de utilizar la función (para permitir flexibilidad).
 */

ostream& operator<<(
  ostream &flujo,                         /**< Flujo de impresión. */
  const Arreglo<unsigned char> &arreglo   /**< Arreglo a imprimir. */
)
{
  for (unsigned int i = 0; i < arreglo.obtenerNumeroDeElementos(); i++)
    flujo << "0x" << hex << (0xFF & arreglo.mArregloInterno[i]) << " ";
  return flujo << dec;
}
