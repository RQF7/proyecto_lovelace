/**
 * \file
 * \brief Implementación de pruebas del DRBG basado en cifrador por bloque.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/aleatoriedad_trivial.hh"
#include "cabeceras/ctr_drbg.hh"
#include "cabeceras/ctr_drbg_prueba.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

CTRDRBGPrueba::CTRDRBGPrueba()
: Utilidades::Prueba{"pruebas de DRBG basado en cifrador por bloque"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "probar operación normal de generador",
    CTRDRBGPrueba::probarFuncionDeGeneracion
  });
}

/**
 * Prueba la operación normal del generador.
 *
 * \return Estado de la prueba.
 */

bool CTRDRBGPrueba::probarFuncionDeGeneracion()
{
  CTRDRBG generador {Arreglo<unsigned char>{1, 2, 3},
    DRBG::NivelDeSeguridad::nivel128};

  Arreglo<unsigned char> pruebaUno = generador.operar({10});
  cout << "Prueba uno: " << pruebaUno << endl;
  Arreglo<unsigned char> pruebaDos = generador.operar({100});
  cout << "Prueba dos: " << pruebaDos << endl;
  Arreglo<unsigned char> pruebaTres = generador.operar({32});
  cout << "Prueba tres: " << pruebaTres << endl;
  if (pruebaUno.obtenerNumeroDeElementos() != 10
      || pruebaDos.obtenerNumeroDeElementos() != 100
      || pruebaTres.obtenerNumeroDeElementos() != 32)
    return false;

  generador.cambiarSemilla();
  Arreglo<unsigned char> pruebaCuatro = generador.operar({50});
  cout << "Prueba cuatro: " << pruebaCuatro << endl;
  if (pruebaCuatro.obtenerNumeroDeElementos() != 50)
    return false;

  return true;
}
