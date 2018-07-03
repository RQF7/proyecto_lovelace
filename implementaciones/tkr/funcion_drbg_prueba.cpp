/**
 * \file
 * \brief Implementación de pruebas de la función de drbg.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/funcion_drbg.hh"
#include "cabeceras/funcion_drbg_prueba.hh"
#include "../drbg/cabeceras/drbg.hh"
#include "../drbg/cabeceras/hash_drbg.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

FuncionDRBGPrueba::FuncionDRBGPrueba()
: Utilidades::Prueba{"pruebas de función de DRBG"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Generación de tokens aleatorios",
    FuncionDRBGPrueba::probarOperacion
  });
}

/**
 * Verifica que la generación de tokens aleatorios sea correcta.
 *
 * \return Estado de la prueba.
 */

bool FuncionDRBGPrueba::probarOperacion()
{
  DRBG *drbg = new HashDRBG{Arreglo<unsigned char>{1, 2, 3},
    DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256};
  FuncionDRBG funcion {drbg};
  ArregloDeDigitos pruebaUno = funcion.operar({10u});
  cout << "Prueba uno: " << pruebaUno << endl;
  if (pruebaUno.obtenerNumeroDeElementos() != 10)
    return false;
  ArregloDeDigitos pruebaDos = funcion.operar({5u});
  cout << "Prueba dos: " << pruebaDos << endl;
  if (pruebaDos.obtenerNumeroDeElementos() != 5)
    return false;
  //delete drbg;
  return true;
}
