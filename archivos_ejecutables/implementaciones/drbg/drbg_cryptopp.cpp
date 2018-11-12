/**
 * \file
 * \brief Definición de puente con generador pseudoaleatorio de cryptopp.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/drbg_cryptopp.hh"

using namespace Implementaciones;
using namespace std;

/**
 * Genera la instancia del objeto de cryptopp.
 */

/* TODO: ¿Darle entorpía desde el hardware? */

DRBGCryptopp::DRBGCryptopp()
: mDrbg {}
{
}

/**
 * Operación del generador. Ocupa el constructor de un arreglo por memoria
 * ya reservada.
 */

Arreglo<unsigned char> DRBGCryptopp::operar(const std::vector<entero>& entrada)
{
  unsigned char *bloque = new unsigned char[entrada[0]];
  mDrbg.GenerateBlock(bloque, entrada[0]);
  return Arreglo<unsigned char>(static_cast<unsigned int>(entrada[0]),
    move(bloque));
}
