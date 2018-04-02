/**
 * \file
 * \brief Implementación de pruebas del DRBG basado en funciones hash.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/aleatoriedad_trivial.hh"
#include "cabeceras/hash_drbg.hh"
#include "cabeceras/hash_drbg_prueba.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

HashDRBGPrueba::HashDRBGPrueba()
: Utilidades::Prueba{"pruebas de DRBG basado en función hash"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operación de función de derivación",
    HashDRBGPrueba::probarFuncionDeDerivacion
  });
}

/**
 * Prueba la operación de instanciación y cambio de semilla de DRBG basado
 * en una función hash.
 *
 * \return Estado de la prueba.
 */

bool HashDRBGPrueba::probarFuncionDeDerivacion()
{
  AleatoriedadTrivial *aleatoriedad = new AleatoriedadTrivial;

  /* Prueba con SHA256 */
  HashDRBG generador {aleatoriedad, Arreglo<unsigned char>{1, 2, 3},
    DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256};
  cout << "Longitud de semilla: " << dec << generador.mLongitudSemilla << endl;
  cout << "Valor de semilla (" << dec
       << generador.mSemilla.obtenerNumeroDeElementos() << "): " << endl;
  for (unsigned int i = 0;
    i < generador.mSemilla.obtenerNumeroDeElementos(); i++)
    cout << "0x" << hex << (0xFF & generador.mSemilla[i]) << " ";
  cout << endl;
  cout << "Valor de constante (" << dec
       << generador.mConstanteSemilla.obtenerNumeroDeElementos()
       << "): " << endl;
  for (unsigned int i = 0;
    i < generador.mConstanteSemilla.obtenerNumeroDeElementos(); i++)
    cout << "0x" << hex << (0xFF & generador.mConstanteSemilla[i]) << " ";
  cout << endl;

  /* Prueba con SHA512 */
  HashDRBG generadorDos {aleatoriedad, Arreglo<unsigned char>{1, 2, 3},
    DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA512};
  cout << "Longitud de semilla: " << dec << generadorDos.mLongitudSemilla
       << endl;
  cout << "Valor de semilla (" << dec
       << dec << generadorDos.mSemilla.obtenerNumeroDeElementos()
       << "): " << endl;
  for (unsigned int i = 0;
    i < generadorDos.mSemilla.obtenerNumeroDeElementos(); i++)
    cout << "0x" << hex << (0xFF & generadorDos.mSemilla[i]) << " ";
  cout << endl;
  cout << "Valor de constante (" << dec
       << generadorDos.mConstanteSemilla.obtenerNumeroDeElementos()
       << "): " << endl;
  for (unsigned int i = 0;
    i < generadorDos.mConstanteSemilla.obtenerNumeroDeElementos(); i++)
    cout << "0x" << hex << (0xFF & generadorDos.mConstanteSemilla[i]) << " ";
  cout << endl;

  return true;
}
