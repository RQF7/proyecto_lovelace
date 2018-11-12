/**
 * \file
 * \brief Definición de prueba de puente con cryptopp.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/drbg_cryptopp.hh"
#include "cabeceras/drbg_cryptopp_prueba.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

DRBGCryptoppPrueba::DRBGCryptoppPrueba()
: Utilidades::Prueba{"pruebas de envolvente de DRBG de CryptoPP"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "probar operación normal de generador",
    DRBGCryptoppPrueba::probarOperacion
  });
}

/**
 * \return Estado de la prueba.
 */

bool DRBGCryptoppPrueba::probarOperacion()
{
  DRBGCryptopp generador {};
  Arreglo<unsigned char> pruebaUno = generador.operar({10});
  cout << "Prueba con 10 elementos: " << endl
    << pruebaUno << endl;
  auto pruebaDos = generador.operar({10});
  cout << "Segunda prueba con 10 elementos: " << endl
    << pruebaDos << endl;
  if (pruebaUno == pruebaDos)
    return false;
  return true;
}
