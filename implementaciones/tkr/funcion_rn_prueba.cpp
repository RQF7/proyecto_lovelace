/**
 * \file
 * \brief Implementación de pruebas de la función RN
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/funcion_rn.hh"
#include "cabeceras/funcion_rn_prueba.hh"
#include "cabeceras/pseudoaleatorio_aes.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <cryptopp/aes.h>
#include <cryptopp/cbcmac.h>
#include <cryptopp/drbg.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <vector>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace CryptoPP;
using namespace std;

FuncionRNPrueba::FuncionRNPrueba()
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Redistribución de bytes en arreglo",
    FuncionRNPrueba::probarRedistribucion
  });
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Generación de tokens aleatorios",
    FuncionRNPrueba::probarOperacion
  });
}

/**
 * Verifica que las particiones de bytes sean correctas.
 *
 * \return Estado de la prueba.
 */

bool FuncionRNPrueba::probarRedistribucion()
{
  FuncionRN funcion {nullptr};
  Arreglo<unsigned char> arreglo {255, 15, 240, 0};
  auto prueba = funcion.redistribuir(arreglo);
  cout << "Prueba uno: " << endl;
  for (int i = 0; i < arreglo.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arreglo[i]) << " ";
  cout << endl;
  for (int i = 0; i < prueba.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(prueba[i]) << " ";
  cout << endl;
  if (prueba.obtenerNumeroDeElementos() != 8 ||
    prueba != Arreglo<unsigned char>{15, 15, 15, 0, 0, 15, 0, 0})
    return false;

  return true;
}

/**
 * Verifica que la generación de tokens aleatorios sea correcta.
 *
 * \return Estado de la prueba.
 */

bool FuncionRNPrueba::probarOperacion()
{
  unsigned char *llave = new unsigned char[AES::DEFAULT_KEYLENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, AES::DEFAULT_KEYLENGTH);
  PseudoaleatorioAES* aes = new PseudoaleatorioAES {llave};

  FuncionRN funcion {aes};
  Arreglo<int> tokenUno = funcion.operar({});
  Arreglo<int> tokenDos = funcion.operar({});
  Arreglo<int> tokenTres = funcion.operar({});
  cout << "Token uno: " << tokenUno << endl
       << "Token dos: " << tokenDos << endl
       << "Token tres: " << tokenTres << endl;
  if (tokenUno.obtenerNumeroDeElementos() != 16 ||
    tokenUno == tokenDos || tokenDos == tokenTres || tokenUno == tokenTres)
    return false;

  return true;
}
