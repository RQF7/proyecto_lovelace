/**
 * \file
 * \brief Pruebas de función de ronda de FFX.
 * Proyecto Lovelace.
 */

#include "cabeceras/ronda_ffx_a10.hh"
#include "cabeceras/ronda_ffx_a10_prueba.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <cryptopp/aes.h>
#include <cryptopp/cbcmac.h>
#include <cryptopp/drbg.h>
#include <cryptopp/sha.h>
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace CryptoPP;
using namespace std;

RondaFFXA10Prueba::RondaFFXA10Prueba()
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operaciones de cifrado y descifrado",
    RondaFFXA10Prueba::probarOperacion
  });
}

/**
 * Prueba las longitudes de los textos cifrados.
 *
 * \return Estado de la prueba.
 */

bool RondaFFXA10Prueba::probarOperacion()
{
  /* Crear llave y tweak. */
  unsigned char llave[AES::DEFAULT_KEYLENGTH], tweak[AES::DEFAULT_KEYLENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, AES::DEFAULT_KEYLENGTH);
  generadorAleatorio.GenerateBlock(tweak, AES::DEFAULT_KEYLENGTH);

  /* Prueba de 4 caracteres. */
  Arreglo<int> textoEnClaroUno {1, 2, 3, 4};
  RondaFFXA10<int> rondaFFXUno {llave, tweak, AES::DEFAULT_KEYLENGTH,
    1, 1, 10, 4, 0, 12};
  auto textoCifradoUno = rondaFFXUno.operar({textoEnClaroUno});
  cout << "Prueba de 4 carcateres:" << endl
       << "Texto en claro: " << textoEnClaroUno << endl
       << "Texto cifrado: " << textoCifradoUno << endl;
  if (textoCifradoUno.obtenerNumeroDeElementos() != 4)
    return false;

  /* Prueba de 8 caracteres. */
  Arreglo<int> textoEnClaroDos {1, 2, 3, 4, 6, 7, 8};
  RondaFFXA10<int> rondaFFXDos {llave, tweak, AES::DEFAULT_KEYLENGTH,
    1, 1, 10, 8, 0, 12};
  auto textoCifradoDos = rondaFFXDos.operar({textoEnClaroDos});
  cout << "Prueba de 8 carcateres:" << endl
       << "Texto en claro: " << textoEnClaroDos << endl
       << "Texto cifrado: " << textoCifradoDos << endl;
  if (textoCifradoDos.obtenerNumeroDeElementos() != 8)
    return false;

  /* Prueba de 2 caracteres. */
  Arreglo<int> textoEnClaroTres {1, 2};
  RondaFFXA10<int> rondaFFXTres {llave, tweak, AES::DEFAULT_KEYLENGTH,
    1, 1, 10, 2, 0, 12};
  auto textoCifradoTres = rondaFFXTres.operar({textoEnClaroTres});
  cout << "Prueba de 2 carcateres:" << endl
       << "Texto en claro: " << textoEnClaroTres << endl
       << "Texto cifrado: " << textoCifradoTres << endl;
  if (textoCifradoTres.obtenerNumeroDeElementos() != 2)
    return false;

  /* Prueba de 12 caracteres. */
  Arreglo<int> textoEnClaroCuatro {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  RondaFFXA10<int> rondaFFXCuatro {llave, tweak, AES::DEFAULT_KEYLENGTH,
    1, 1, 10, 12, 0, 12};
  auto textoCifradoCuatro = rondaFFXCuatro.operar({textoEnClaroCuatro});
  cout << "Prueba de 12 carcateres:" << endl
       << "Texto en claro: " << textoEnClaroCuatro << endl
       << "Texto cifrado: " << textoCifradoCuatro << endl;
  if (textoCifradoCuatro.obtenerNumeroDeElementos() != 12)
    return false;

  /* Prueba de 16 caracteres. */
  Arreglo<int> textoEnClaroCinco {1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16};
  RondaFFXA10<int> rondaFFXCinco {llave, tweak, AES::DEFAULT_KEYLENGTH,
    4, 1, 10, 16, 0, 12};
  auto textoCifradoCinco = rondaFFXCinco.operar({textoEnClaroCinco});
  cout << "Prueba de 12 carcateres:" << endl
       << "Texto en claro: " << textoEnClaroCinco << endl
       << "Texto cifrado: " << textoCifradoCinco << endl;
  if (textoCifradoCinco.obtenerNumeroDeElementos() != 16)
    return false;

  return true;
}
