/**
 * \file
 * \brief Definición de funciones de prueba de FFX.
 * Proyecto Lovelace.
 */

#include "cabeceras/ffx_prueba.hh"
#include "cabeceras/arreglo.hh"
#include "cabeceras/ffx.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

FFXPrueba::FFXPrueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "funciones de suma y resta",
    FFXPrueba::probarFuncionesDeSuma
  });
}

/**
 * Realiza pruebas con las funciones de suma y resta definidas en
 * el archivo de cabecera de FFX.
 *
 * \return Estado de la prueba.
 */

bool FFXPrueba::probarFuncionesDeSuma()
{
  Arreglo<int> argumentoUno {5, 6, 7};
  Arreglo<int> argumentoDos {3, 9, 2};

  /* Suma y resta por bloque.
   * 765 + 293 = 1058 (i.e. 58) */
  Arreglo<int> resultadoSumaPorBloque = sumaPorBloque<int, 10>(
    argumentoUno, argumentoDos);
  Arreglo<int> resultadoRestaPorBloque = restaPorBloque<int, 10>(
    resultadoSumaPorBloque, argumentoUno);
  cout << "Suma y resta por bloque:" << endl
       << "Argumento uno, " << argumentoUno << endl
       << "Argumento dos, " << argumentoDos << endl
       << "Resultado de suma: " << resultadoSumaPorBloque << endl
       << "Inverso mediante resta, " << resultadoRestaPorBloque << endl;
  if (resultadoSumaPorBloque != Arreglo<int>{8, 5, 0} ||
    resultadoRestaPorBloque != argumentoDos)
    return false;

  /* Suma y resta por caracter
   * 765 + 293 = 958 */
  Arreglo<int> resultadoSumaPorCaracter = sumaPorCaracter<int, 10>(
    argumentoUno, argumentoDos);
  Arreglo<int> resultadoRestaPorCaracter = restaPorCaracter<int, 10>(
    resultadoSumaPorCaracter, argumentoUno);
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
