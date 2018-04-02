/**
 * \file
 * \brief Implementación de pruebas de función pseudoalatoria con AES.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/pseudoaleatorio_aes.hh"
#include "cabeceras/pseudoaleatorio_aes_prueba.hh"
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

PseudoaleatorioAESPrueba::PseudoaleatorioAESPrueba()
: Utilidades::Prueba{"pruebas de AES pseudoaleatorio"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "generación de bloque pseudoaleatorio",
    PseudoaleatorioAESPrueba::probarOperacion
  });
}

/**
 * Verifica que la longitud del arreglo cifrado corresponda con la longitud
 * solicitada.
 *
 * \return Estado de la prueba.
 */

bool PseudoaleatorioAESPrueba::probarOperacion()
{
  unsigned char *llave = new unsigned char[AES::DEFAULT_KEYLENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, AES::DEFAULT_KEYLENGTH);

  PseudoaleatorioAES aes {llave};
  Arreglo<unsigned char> pruebaUno = aes.operar({13, 3 * 4 * 16});
  cout << "Prueba uno: " << pruebaUno.obtenerNumeroDeElementos() << endl;
  for (unsigned int i = 0; i < pruebaUno.obtenerNumeroDeElementos(); i++)
    cout << "0x" << hex << (0xFF & static_cast<byte>(pruebaUno[i])) << " ";
  cout << dec << endl;
  if (pruebaUno.obtenerNumeroDeElementos() != 32)
    return false;

  PseudoaleatorioAES aesDos {llave};
  Arreglo<unsigned char> pruebaDos = aesDos.operar({105, 1056});
  cout << "Prueba uno: " << pruebaDos.obtenerNumeroDeElementos() << endl;
  for (unsigned int i = 0; i < pruebaDos.obtenerNumeroDeElementos(); i++)
    cout << "0x" << hex << (0xFF & static_cast<byte>(pruebaDos[i])) << " ";
  cout << dec << endl;
  if (pruebaDos.obtenerNumeroDeElementos() != 144)
    return false;

  return true;
}
