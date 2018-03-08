/**
 * \file
 * \brief Definición de funciones de prueba de FFX.
 * Proyecto Lovelace.
 */

#include "cabeceras/ffx_prueba.hh"
#include "cabeceras/arreglo.hh"
#include "cabeceras/ffx.hh"
#include <cryptopp/aes.h>
#include <cryptopp/cbcmac.h>
#include <cryptopp/drbg.h>
#include <cryptopp/sha.h>
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace CryptoPP;
using namespace std;

FFXPrueba::FFXPrueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "funciones de suma y resta",
    FFXPrueba::probarFuncionesDeSuma
  });
  mListaDePruebas.push_back(FuncionDePrueba{
    "funciones de ronda",
    FFXPrueba::probarFuncionDeRonda
  });
}

/**
 * Realiza pruebas con la función de ronda por defecto.
 *
 * \return Estado de la prueba.
 */

bool FFXPrueba::probarFuncionDeRonda()
{
  /* Crear llave y tweak. */
  unsigned char llave[AES::DEFAULT_KEYLENGTH], tweak[AES::DEFAULT_KEYLENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, AES::DEFAULT_KEYLENGTH);
  generadorAleatorio.GenerateBlock(tweak, AES::DEFAULT_KEYLENGTH);

  Arreglo<int> textoEnClaro {1, 2, 3, 4, 5, 6, 7, 8};
  Arreglo<int> textoCifrado (funcionRondaCbcMacAes<int, llave, tweak,
    AES::DEFAULT_KEYLENGTH, 0, 1, 10, 16, 0, 12>(textoEnClaro));

  return true;
}
