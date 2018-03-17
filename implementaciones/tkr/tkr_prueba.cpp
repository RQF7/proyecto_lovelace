/**
 * \file
 * \brief Implementación de pruebas de TKR2.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/funcion_rn.hh"
#include "cabeceras/pseudoaleatorio_aes.hh"
#include "cabeceras/tkr.hh"
#include "cabeceras/tkr_prueba.hh"
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

TKRPrueba::TKRPrueba()
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operación con miembros triviales",
    TKRPrueba::probarOperacionTrivial
  });
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operación con función RN",
    TKRPrueba::probarOperacionNoTanTrivial
  });
}

/**
 * Prueba la operación de TKR con una fucción pseudoaleatoria trivial
 * y con un acceso a datos simulado.
 *
 * \return Estado de la prueba.
 */

bool TKRPrueba::probarOperacionTrivial()
{
  TKR tkr {};
  Arreglo<int> panUno {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6};
  Arreglo<int> tokenUno = tkr.tokenizar(panUno, Arreglo<int>{});
  Arreglo<int> panDos = tkr.detokenizar(tokenUno, Arreglo<int>{});
  cout << "Prueba uno: " << endl
       << "PAN uno: " << panUno << endl
       << "Token uno: " << tokenUno << endl
       << "PAN dos: " << panDos << endl;
  if (tokenUno.obtenerNumeroDeElementos() != 16)
    return false;

  return true;
}

/**
 * Prueba la operación de TKR con la función RN (y esta a su vez con una
 * función basada en AES); el acceso a base de datos sigue siendo una
 * simulación.
 *
 * \return Estado de la prueba.
 */

bool TKRPrueba::probarOperacionNoTanTrivial()
{
  unsigned char *llave = new unsigned char[AES::DEFAULT_KEYLENGTH];
  PseudoaleatorioAES* aes = new PseudoaleatorioAES {llave};
  FuncionRN *funcion = new FuncionRN{aes};
  TKR tkr {funcion};

  Arreglo<int> panUno {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6};
  Arreglo<int> tokenUno = tkr.tokenizar(panUno, Arreglo<int>{});
  Arreglo<int> tokenDos = tkr.tokenizar(panUno, Arreglo<int>{});

  cout << "PAN original: " << panUno << endl
       << "Token uno: " << tokenUno << endl
       << "Token dos: " << tokenDos << endl;

  return true;
}