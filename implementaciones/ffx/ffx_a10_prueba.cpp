/**
 * \file
 * \brief Definición de funciones de prueba de FFX.
 * Proyecto Lovelace.
 */

#include "cabeceras/arreglo.hh"
#include "cabeceras/ffx_a10.hh"
#include "cabeceras/ffx_a10_prueba.hh"
#include <cryptopp/aes.h>
#include <cryptopp/cbcmac.h>
#include <cryptopp/drbg.h>
#include <cryptopp/sha.h>
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace CryptoPP;
using namespace std;

FFXA10Prueba::FFXA10Prueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "operación de ffxa10",
    FFXA10Prueba::probarCifradoDescifrado
  });
}

/**
 * Realiza pruebas con la función de ronda por defecto.
 *
 * \return Estado de la prueba.
 */

bool FFXA10Prueba::probarCifradoDescifrado()
{
  unsigned char llave[AES::DEFAULT_KEYLENGTH], tweak[AES::DEFAULT_KEYLENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, AES::DEFAULT_KEYLENGTH);
  generadorAleatorio.GenerateBlock(tweak, AES::DEFAULT_KEYLENGTH);

  FFXA10<int> ffx {llave, tweak, AES::DEFAULT_KEYLENGTH, 8, 10};
  Arreglo<int> textoOriginal {1, 2, 3, 4, 5, 6, 7, 8};
  Arreglo<int> textoCifrado = ffx.operar({textoOriginal});
  Arreglo<int> textoDescifrado = ffx.deoperar({textoCifrado});
  cout << "Prueba con 8 caracteres: " << endl
       << "Texto original: " << textoOriginal << endl
       << "Texto cifrado: " << textoCifrado << endl
       << "Texto descifrado: " << textoDescifrado << endl;
  if (textoDescifrado != textoOriginal)
    return false;

  FFXA10<int> ffxDos {llave, tweak, AES::DEFAULT_KEYLENGTH, 4, 10};
  Arreglo<int> textoOriginalDos {1, 2, 3, 4};
  Arreglo<int> textoCifradoDos = ffxDos.operar({textoOriginalDos});
  Arreglo<int> textoDescifradoDos = ffxDos.deoperar({textoCifradoDos});
  cout << "Prueba con 4 caracteres: " << endl
       << "Texto original: " << textoOriginalDos << endl
       << "Texto cifrado: " << textoCifradoDos << endl
       << "Texto descifrado: " << textoDescifradoDos << endl;
  if (textoDescifradoDos != textoOriginalDos)
    return false;

//  FFXA10<int> ffxTres {llave, tweak, AES::DEFAULT_KEYLENGTH, 5, 10};
//  Arreglo<int> textoOriginalTres {1, 2, 3, 4, 5};
//  Arreglo<int> textoCifradoTres = ffxTres.operar({textoOriginalTres});
//  Arreglo<int> textoDescifradoTres = ffxTres.deoperar({textoCifradoTres});
//  cout << "Prueba con 5 caracteres: " << endl
//       << "Texto original: " << textoOriginalTres << endl
//       << "Texto cifrado: " << textoCifradoTres << endl
//       << "Texto descifrado: " << textoDescifradoTres << endl;
//  if (textoDescifradoTres != textoOriginalTres)
//    return false;

//  FFXA10<int> ffxCuatro {llave, tweak, AES::DEFAULT_KEYLENGTH, 14, 10};
//  Arreglo<int> textoOriginalCuatro {1, 2, 3, 4, 5, 6, 7, 8,
//    9, 10, 11, 12, 13, 14};
//  Arreglo<int> textoCifradoCuatro = ffxCuatro.operar({textoOriginalCuatro});
//  Arreglo<int> textoDescifradoCuatro = ffxCuatro.deoperar({textoCifradoCuatro});
//  cout << "Prueba con 16 caracteres: " << endl
//       << "Texto original: " << textoOriginalCuatro << endl
//       << "Texto cifrado: " << textoCifradoCuatro << endl
//       << "Texto descifrado: " << textoDescifradoCuatro << endl;
//  if (textoDescifradoCuatro != textoOriginalCuatro)
//    return false;

  return true;
}
