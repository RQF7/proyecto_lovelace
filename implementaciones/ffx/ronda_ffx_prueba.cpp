/**
 * \file
 * \brief Pruebas de función de ronda de FFX.
 * Proyecto Lovelace.
 */

#include "cabeceras/arreglo.hh"
#include "cabeceras/ronda_ffx.hh"
#include "cabeceras/ronda_ffx_prueba.hh"
#include <cryptopp/aes.h>
#include <cryptopp/cbcmac.h>
#include <cryptopp/drbg.h>
#include <cryptopp/sha.h>
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace CryptoPP;
using namespace std;

RondaFFXPrueba::RondaFFXPrueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "operaciones de cifrado y descifrado",
    RondaFFXPrueba::probarOperacion
  });
}

/**
 * Prueba las longitudes de los textos cifrados.
 *
 * \return Estado de la prueba.
 */

bool RondaFFXPrueba::probarOperacion()
{
  /* Crear llave y tweak. */
  unsigned char llave[AES::DEFAULT_KEYLENGTH], tweak[AES::DEFAULT_KEYLENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, AES::DEFAULT_KEYLENGTH);
  generadorAleatorio.GenerateBlock(tweak, AES::DEFAULT_KEYLENGTH);

  /* Prueba de 4 caracteres. */
  Arreglo<int> textoEnClaroUno {1, 2, 3, 4};
  RondaFFX<int> rondaFFXUno {llave, tweak, AES::DEFAULT_KEYLENGTH,
    1, 1, 10, 8, 0, 12};
  auto textoCifradoUno = rondaFFXUno.operar({textoEnClaroUno});
  cout << "Prueba de 4 carcateres:" << endl
       << "Texto en claro: " << textoEnClaroUno << endl
       << "Texto cifrado: " << textoCifradoUno << endl;
  if (textoCifradoUno.obtenerNumeroDeElementos() != 4)
    return false;

  /* Prueba de 8 caracteres. */
  Arreglo<int> textoEnClaroDos {1, 2, 3, 4, 6, 7, 8};
  RondaFFX<int> rondaFFXDos {llave, tweak, AES::DEFAULT_KEYLENGTH,
    1, 1, 10, 16, 0, 12};
  auto textoCifradoDos = rondaFFXDos.operar({textoEnClaroDos});
  cout << "Prueba de 8 carcateres:" << endl
       << "Texto en claro: " << textoEnClaroDos << endl
       << "Texto cifrado: " << textoCifradoDos << endl;
  if (textoCifradoDos.obtenerNumeroDeElementos() != 8)
    return false;

  return true;
}
