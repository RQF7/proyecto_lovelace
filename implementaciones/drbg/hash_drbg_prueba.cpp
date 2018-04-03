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
  //mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
  //  "probar operación normal de generador",
  //  HashDRBGPrueba::probarFuncionDeGeneracion
  //});
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

  delete aleatoriedad;
  return true;
}

/**
 * Prueba la operación normal del generador.
 *
 * \return Estado de la prueba.
 */

bool HashDRBGPrueba::probarFuncionDeGeneracion()
{
  AleatoriedadTrivial *aleatoriedad = new AleatoriedadTrivial;
  HashDRBG generador {aleatoriedad, Arreglo<unsigned char>{1, 2, 3},
    DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256};

  Arreglo<unsigned char> pruebaUno = generador.operar({10});
  cout << "Prueba uno: " << pruebaUno << endl;
  Arreglo<unsigned char> pruebaDos = generador.operar({100});
  cout << "Prueba dos: " << pruebaDos << endl;
  Arreglo<unsigned char> pruebaTres = generador.operar({32});
  cout << "Prueba tres: " << pruebaTres << endl;

  delete aleatoriedad;
  return true;
}
