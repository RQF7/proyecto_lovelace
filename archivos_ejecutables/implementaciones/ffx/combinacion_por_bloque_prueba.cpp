/**
 * \file
 * \brief Implementación de pruebas de combinación por bloque.
 * Proyecto Lovelace.
 */

#include "cabeceras/combinacion_por_bloque.hh"
#include "cabeceras/combinacion_por_bloque_prueba.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

CombinacionPorBloquePrueba::CombinacionPorBloquePrueba()
: Utilidades::Prueba{"pruebas de combinación por bloque"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operaciones de suma y resta por bloque",
    CombinacionPorBloquePrueba::probarSumaYResta
  });
}

/**
 * Suma y resta por bloque.
  * 765 + 293 = 1058 (i.e. 58)
 */

bool CombinacionPorBloquePrueba::probarSumaYResta()
{
  Arreglo<int> argumentoUno {5, 6, 7};
  Arreglo<int> argumentoDos {3, 9, 2};

  CombinacionPorBloque<int> combinacionPorBloque{};
  Arreglo<int> resultadoSumaPorBloque = combinacionPorBloque.operar({
    argumentoUno, argumentoDos});
  Arreglo<int> resultadoRestaPorBloque = combinacionPorBloque.deoperar({
    resultadoSumaPorBloque, argumentoUno});
  cout << "Suma y resta por bloque:" << endl
       << "Argumento uno, " << argumentoUno << endl
       << "Argumento dos, " << argumentoDos << endl
       << "Resultado de suma: " << resultadoSumaPorBloque << endl
       << "Inverso mediante resta, " << resultadoRestaPorBloque << endl;
  if (resultadoSumaPorBloque != Arreglo<int>{8, 5, 0} ||
    resultadoRestaPorBloque != argumentoDos)
    return false;

  return true;
}
