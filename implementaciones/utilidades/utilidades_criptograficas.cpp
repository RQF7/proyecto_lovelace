/**
 * \file
 * \brief Definición de funciones comúnes relacionadas con la criptografía.
 */

#include "cabeceras/utilidades_criptograficas.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include "../drbg/cabeceras/hash_drbg.hh"
#include "../drbg/cabeceras/aleatoriedad_hardware.hh"
#include <utility>
#include <iostream>

using namespace Implementaciones;
using namespace CryptoPP;

/**
 * Genera una llave pseudoaleatoria con un DRBG aprobado por el NIST.
 *
 * \return Arreglo con llave psudoaleatoria.
 */

Arreglo<unsigned char> Implementaciones::generarLlave(
  int longitud                      /**< Longitud en bytes. */
)
{
  AleatoriedadHardware *aleatoriedad = new AleatoriedadHardware;
  HashDRBG generador {Arreglo<unsigned char>{1, 2, 3},
    DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256,
    aleatoriedad};

  auto resultado = generador.operar({static_cast<unsigned int>(longitud)});
  delete aleatoriedad;
  return resultado;
}
