/**
 * \file
 * \brief Implementación de pruebas de utilidades de tarjetas.
 */

#include "cabeceras/utilidades_tarjetas.hh"
#include "cabeceras/utilidades_tarjetas_prueba.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

UtilidadesTarjetasPrueba::UtilidadesTarjetasPrueba()
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Cálculo de dígito verificador: algoritmo de Luhn",
    UtilidadesTarjetasPrueba::probarAlgoritmoDeLuhn
  });
}

/**
 * Prueba el resultado del método contra dígitos que calculé a mano (varias
 * veces); tanto para cadenas pares como impares.
 *
 * \return Estado de la prueba.
 */

bool UtilidadesTarjetasPrueba::probarAlgoritmoDeLuhn()
{
  Arreglo<int> numeroUno {5, 2, 5, 6, 7, 8, 8, 1, 6, 9, 4, 0, 8, 9, 9};
  int pruebaUno = algoritmoDeLuhn(numeroUno);
  Arreglo<int> numeroDos {6, 7, 6};
  int pruebaDos = algoritmoDeLuhn(numeroDos);
  Arreglo<int> numeroTres {4, 8, 9, 1};
  int pruebaTres = algoritmoDeLuhn(numeroTres);
  cout << "Prueba Uno: " << numeroUno << " ==> " << pruebaUno << endl
       << "Prueba Dos: " << numeroDos << " ==> " << pruebaDos << endl
       << "Prueba Tres: " << numeroTres << " ==> " << pruebaTres << endl;
  if (pruebaUno != 4 || pruebaDos != 7 || pruebaTres != 8)
    return false;

  return true;
}
