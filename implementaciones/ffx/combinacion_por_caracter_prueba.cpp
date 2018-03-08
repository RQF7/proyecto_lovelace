/**
 * \file
 * \brief Implementación de pruebas de combinación por caracter.
 * Proyecto Lovelace.
 */

#include "cabeceras/arreglo.hh"
#include "cabeceras/combinacion_por_caracter.hh"
#include "cabeceras/combinacion_por_caracter_prueba.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

CombinacionPorCaracterPrueba::CombinacionPorCaracterPrueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "operaciones de suma y resta por caracter",
    CombinacionPorCaracterPrueba::probarSumaYResta
  });
}

/**
 * Suma y resta por caracter
 * 765 + 293 = 958
 */

bool CombinacionPorCaracterPrueba::probarSumaYResta()
{
  Arreglo<int> argumentoUno {5, 6, 7};
  Arreglo<int> argumentoDos {3, 9, 2};

  CombinacionPorCaracter<int> combinacionPorCaracter{};
  Arreglo<int> resultadoSumaPorCaracter = combinacionPorCaracter.operar({
    argumentoUno, argumentoDos});
  Arreglo<int> resultadoRestaPorCaracter = combinacionPorCaracter.deoperar({
    resultadoSumaPorCaracter, argumentoUno});
  cout << "Suma y resta por caracter:" << endl
       << "Argumento uno, " << argumentoUno << endl
       << "Argumento dos, " << argumentoDos << endl
       << "Resultado de suma: " << resultadoSumaPorCaracter << endl
       << "Inverso mediante resta, " << resultadoRestaPorCaracter << endl;
  if (resultadoSumaPorCaracter != Arreglo<int>{8, 5, 9} ||
    resultadoRestaPorCaracter != argumentoDos)
    return false;

  return true;
}
