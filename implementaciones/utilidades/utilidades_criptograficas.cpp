/**
 * \file
 * \brief Definición de funciones comúnes relacionadas con la criptografía.
 */

#include "cabeceras/utilidades_criptograficas.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <cryptopp/drbg.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <cryptopp/sha.h>
#include <utility>
#include <iostream>

using namespace Implementaciones;
using namespace CryptoPP;

/**
 * Genera una llave pseudoaleatoria con un DRGB aprobado por el NIST.
 *
 * \return Arreglo con llave psudoaleatoria.
 */

Arreglo<unsigned char> Implementaciones::generarLlave(
  int longitud                      /**< Longitud en bytes. */
)
{
  /* Arreglo con resultado. */
  unsigned char* llave = new unsigned char[longitud];
  /* Arreglo con entropía (contenedor de cryptopp). */
  SecByteBlock entropia {48};
  /* Generador de aleatoredad aprobado por el NIST (90B y 90C). */
  NonblockingRng generadorAleatorio;
  /* Interfaz con generador: rellena el arreglo de entropia. */
  RandomNumberSource fuenteDeAleatoriedad {generadorAleatorio,
    static_cast<int>(entropia.size()),
    new ArraySink{entropia, entropia.size()}};
  /* Instanciación de DRGB con función hash. */
  Hash_DRBG<SHA256, 128/8, 440/8> generadorPseudoaleatorio(entropia,
    32, entropia + 32, 16);

  generadorPseudoaleatorio.GenerateBlock(llave, longitud);
  Arreglo<unsigned char>resultado (longitud, std::move(llave));
  delete[] llave;
  return resultado;
}
