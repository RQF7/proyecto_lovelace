/**
 * \file
 * \brief Definición de intermediario de arreglo de dígitos.
 */

#include "cabeceras/intermediario_de_arreglo_de_digitos.hh"
#include "cabeceras/arreglo_de_digitos.hh"
#include "cabeceras/intermediario_de_arreglo.hh"
#include "cabeceras/utilidades_matematicas.hh"
#include <iostream>

using namespace Utilidades;
using namespace std;

/**
 * Pasa a la superclase la misma referencia e índice dados, sin embargo,
 * también guarda una referencia local propia. Esto porque en la
 * clase padre es una referencia a Arreglo, mientras que el funcionamiento
 * de esta clase necesita un ArregloDeDigitos.
 */

IntermediarioDeArregloDeDigitos::IntermediarioDeArregloDeDigitos(
  ArregloDeDigitos& arreglo,        /**< Referencia a arreglo. */
  int indice                        /**< Índice de elemento interno. */
)
: IntermediarioDeArreglo<int>{arreglo, indice},
  mArregloDeDigitos {arreglo}
{
}

/**
 * Operador de asignación sobre un ArregloDeDigitos. A parte de hacer la
 * asignación (lo cuál se podría hacer con la clase padre) también se
 * actualiza el estado interno: se manipula el número interno y la cadena
 * (¡como si fueran números de Gödel!).
 *
 * Para hacer la propia asignación sí se utiliza la función de la superclase.
 * La única utilidad de esto es demostrar la relación entre los dos
 * intermediarios; sería un poco más eficiente hacer la asignación
 * directamente.
 *
 * \return Referencia a entero asignado.
 */

int& IntermediarioDeArregloDeDigitos::operator=(
  int elemento                     /* Elemento a escribir. */
)
{
  entero equivalentePotencia = potencia<entero>(mArregloDeDigitos.mBase,
    mArregloDeDigitos.mNumeroDeElementos - mIndice - 1);
  mArregloDeDigitos.mNumero -= (mArregloDeDigitos.mArregloInterno[mIndice])
    * equivalentePotencia;
  mArregloDeDigitos.mCadena[mIndice] = elemento + 48;
  mArregloDeDigitos.mNumero += elemento * equivalentePotencia;
  return IntermediarioDeArreglo<int>::operator=(elemento);
}
