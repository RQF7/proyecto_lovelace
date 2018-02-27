/*
 * Prueba de SHA256, declaración, crypto++
 * Proyecto Lovelace
 */

#include "cabeceras/prueba_SHA256.hh"
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>

using namespace std;
using namespace CryptoPP;
using namespace PruebasCryptopp;

/**
 * Registra las funciones de prueba de AES en la lista de funciones a probar
 * que mantiene la clase de Prueba.
 */
PruebaSHA256::PruebaSHA256()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "Obtener la digestión del mensaje",
    PruebaSHA256::probarDigestion
  });
}

bool PruebaSHA256::probarDigestion()
{
  string entrada {"abc"},
    vectorPrueba {"BA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD"},
    salidaClara;
  
  byte salida[SHA256::DIGESTSIZE];

  SHA256 sha256;
  HexEncoder hex(new StringSink(salidaClara));

  /* Obtener valor SHA256 de la cadena entrada**/
  sha256.Update(
    reinterpret_cast<const unsigned char*>(entrada.c_str()),
    entrada.length()
  );
  sha256.Final(salida);

  /* Mostrar entrada */
  cout << "Entrada: " << entrada << endl;

  /* Mostrar salida en base hexadecimal */
  hex.Put(salida, sizeof(salida));
  hex.MessageEnd();
  cout << "Salida: " << salidaClara << endl;

  return !vectorPrueba.compare(salidaClara);
}