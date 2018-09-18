/**
 * \file
 * \brief Definición de funciones comúnes relacionadas con la criptografía.
 */

#include "cabeceras/utilidades_criptograficas.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include "../drbg/cabeceras/hash_drbg.hh"
#include "../drbg/cabeceras/aleatoriedad_hardware.hh"
#include "../drbg/cabeceras/aleatoriedad_trivial.hh"
#include <utility>
#include <iostream>

using namespace Implementaciones;
using namespace CryptoPP;

/**
 * Genera una llave pseudoaleatoria con un DRBG aprobado por el NIST.
 * Por defecto ocupa un generador de entropía por hardware; si la
 * máquina en la que se corre no contiene instrucciones para esto, entonces
 * se ocupa entropía desde /dev/urand.
 *
 * \return Arreglo con llave psudoaleatoria.
 */

Arreglo<unsigned char> Implementaciones::generarLlave(
  int longitud                      /**< Longitud en bytes. */
)
{
  HashDRBG *generador = nullptr;
  try
  {
    AleatoriedadHardware *aleatoriedad = new AleatoriedadHardware{};
    generador = new HashDRBG{Arreglo<unsigned char>{1, 2, 3},
      DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256,
      aleatoriedad};
  }
  catch (CryptoPP::RDSEED_Err &excepcion)
  {
    AleatoriedadTrivial *aleatoriedadDos = new AleatoriedadTrivial{};
    generador = new HashDRBG{Arreglo<unsigned char>{1, 2, 3},
      DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256,
      aleatoriedadDos};
  }

  auto resultado = generador->operar({static_cast<unsigned int>(longitud)});
  delete generador;
  return resultado;
}
