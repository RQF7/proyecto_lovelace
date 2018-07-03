/**
 * \file
 * \brief Definición de una fuente de aleatoriedad desde hardware.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/aleatoriedad_hardware.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <iostream>

using namespace Implementaciones;
using namespace std;

/**
 * Inicializa la clase de Cryptopp y hace una prueba de operación. En caso de
 * que el procesador no tenga implementada esa función, lanza excepción.
 *
 * \throw Cryptopp::RDSEED_Err Cuando no está implementado en el procesador.
 */

AleatoriedadHardware::AleatoriedadHardware()
: mGenerador {}
{
}

/**
 * Solo porque sí.
 */

AleatoriedadHardware::~AleatoriedadHardware()
{
}

/**
 * Regresa el número de bytes solicitados como un arreglo de bytes.
 * La llamada a RDSEED la hace con un arreglo duro; regresa el arreglo
 * construido mediante copia de una región de memoria ya reservada.
 *
 * \return Arreglo con bytes generador por el procesador.
 */

Arreglo<unsigned char> AleatoriedadHardware::operar(
  const std::vector<unsigned int>& entrada    /**< Número de bytes a leer. */
)
{
  unsigned char *arregloDuro = new unsigned char[entrada[0]];
  mGenerador.GenerateBlock(arregloDuro, entrada[0]);
  return Arreglo<unsigned char>(entrada[0], move(arregloDuro));
}
