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
 *
 *
 * \return Estado de la prueba.
 */

bool HashDRBGPrueba::probarFuncionDeDerivacion()
{
  AleatoriedadTrivial *aleatoriedad = new AleatoriedadTrivial;
  HashDRBG generador {aleatoriedad, Arreglo<unsigned char>{1, 2, 3},
    DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256};
  cout << "Valor de semilla: " << endl;
  // for (unsigned int i = 0; i < mSemilla.obtenerNumeroDeElementos(); i++)
  //   cout << "0x" << hex << (0xFF & mSemilla[i]) << " ";
  // cout << endl;

  return true;
}
