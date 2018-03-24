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
#include "../acceso_a_datos/cabeceras/acceso_mysql.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
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
: Utilidades::Prueba{"pruebas de TKR"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operación con miembros triviales",
    TKRPrueba::probarOperacionTrivial
  });
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operación con función RN",
    TKRPrueba::probarOperacionNoTanTrivial
  });
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operación con base de datos",
    TKRPrueba::probarOperacionNormal
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
  ArregloDeDigitos panUno {123456789123456ull};
  ArregloDeDigitos tokenUno = tkr.tokenizar(panUno);
  ArregloDeDigitos panDos = tkr.detokenizar(tokenUno);
  cout << "Prueba uno: " << endl
       << "PAN uno: " << panUno << endl
       << "Token uno: " << tokenUno << endl
       << "PAN dos: " << panDos << endl;
  if (tokenUno.obtenerNumeroDeElementos() != 8)
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

  ArregloDeDigitos panUno {123456789123456ull};
  ArregloDeDigitos tokenUno = tkr.tokenizar(panUno);
  ArregloDeDigitos tokenDos = tkr.tokenizar(panUno);

  cout << "PAN original: " << panUno << endl
       << "Token uno: " << tokenUno << endl
       << "Token dos: " << tokenDos << endl;

  return true;
}

/**
 * Prueba la operación normal de TKR: un primer proceso de tokenización debe
 * generar un nuevo token, mientras que la segunda ves se debe acceder al
 * anterior la detokenización es solamente una búsqueda en la base de datos.
 *
 * \return Estado de la prueba.
 */

bool TKRPrueba::probarOperacionNormal()
{
  /* Generar llave aleatoria. */
  unsigned char *llave = new unsigned char[AES::DEFAULT_KEYLENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, AES::DEFAULT_KEYLENGTH);

  /* Instanciación de algoritmo. */
  PseudoaleatorioAES* aes = new PseudoaleatorioAES {llave};
  CDV* accesoADatos = new AccesoMySQL {};
  FuncionRN* funcion = new FuncionRN {aes, accesoADatos};
  TKR tkr {funcion, accesoADatos};

  /* Prueba de tokenización y detokenización. */
  ArregloDeDigitos panUno {1234567891234560ull};
  ArregloDeDigitos panTres {5556667778765433ull};
  ArregloDeDigitos tokenUno {tkr.tokenizar(panUno)};
  ArregloDeDigitos tokenDos {tkr.tokenizar(panUno)};
  ArregloDeDigitos tokenTres {tkr.tokenizar(panTres)};
  ArregloDeDigitos panDos {tkr.detokenizar(tokenUno)};
  cout << "PAN: " << panUno << endl
       << "Token uno: " << tokenUno << endl
       << "Token dos: " << tokenDos << endl
       << "Token tres: " << tokenTres << endl
       << "PAN descifrado: " << panDos << endl;

  if (tokenUno != tokenDos || panUno != panDos)
    return false;
  return true;
}
