/**
 * \file
 * \brief Definición de funciones de prueba del contenedor tipo arreglo.
 * Proyecto Lovelace.
 */

#include "cabeceras/arreglo_prueba.hh"
#include "cabeceras/arreglo.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace Implementaciones;
using namespace PruebasImplementaciones;
using namespace std;

ArregloPrueba::ArregloPrueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "funcionalidad básica",
    ArregloPrueba::probarFuncionalidadBasica
  });
  mListaDePruebas.push_back(FuncionDePrueba{
    "generación de particiones",
    ArregloPrueba::probarParticiones
  });
  mListaDePruebas.push_back(FuncionDePrueba{
    "concatenación",
    ArregloPrueba::probarConcatenacion
  });
}

/**
 * Funcionalidad inicial (de la primera implementación) del contenedor tipo
 * arreglo.
 *
 * Se prueba la reserva de memoria; las operaciones de lectura y escritura;
 * y la impresión en un flujo. Se prueba con distintos tipos (tanto básicos
 * como compuestos).
 *
 * \return verdaderoen todos los casos.
 */

bool ArregloPrueba::probarFuncionalidadBasica()
{
  Arreglo<int> arreglo {10};
  for (int i = 0; i < 10; i++)
    arreglo.colocar(i, i + 1);
  cout << arreglo << endl;

  Arreglo<char> arreglo2 {3};
  arreglo2.colocar(0, 'A');
  arreglo2.colocar(1, 'B');
  arreglo2.colocar(2, 'C');
  cout << arreglo2 << endl;

  Arreglo<vector<int>> arreglo3 {2};
  arreglo3.colocar(0, {0, 1, 2, 3, 4});
  arreglo3.colocar(1, {5, 6, 7, 8, 9});

  Arreglo<string> arreglo4 {3};
  arreglo4.colocar(0, "Ricardo");
  arreglo4.colocar(1, "Quezada");
  arreglo4.colocar(2, "Figueroa");
  cout << arreglo4 << endl;

  return true;
}

/**
 * Prueba de particiones de un arreglo. Se prueban dos particiones exactas y
 * una con residuo.
 *
 * \return Verdadero en todos los casos.
 */

bool ArregloPrueba::probarParticiones()
{
  Arreglo<int> arreglo {10};
  for (int i = 0; i < 10; i++)
    arreglo.colocar(i, i + 1);

  auto primerMedio = arreglo.partir(2, 0);
  auto segundoMedio = arreglo.partir(2, 1);
  cout << "Medios: " << endl
       << primerMedio << endl
       << segundoMedio << endl;

  auto segundoQuinto = arreglo.partir(5, 1);
  auto quintoQuinto = arreglo.partir(5, 4);
  cout << "Quintos: " << endl
       << segundoQuinto << endl
       << quintoQuinto << endl;

  auto primerCuarto = arreglo.partir(4, 0);
  auto cuartoCuarto = arreglo.partir(4, 3);
  cout << "Cuartos: " << endl
       << primerCuarto << endl
       << cuartoCuarto << endl;

  return true;
}

/**
 * Prueba la operación de concatenación de los arreglos.
 *
 * \return Verdadero en todos los casos.
 */

bool ArregloPrueba::probarConcatenacion()
{
  Arreglo<int> arregloUno {5}, arregloDos{5}, arregloTres{5};
  for (int i = 0; i < 5; i++)
  {
    arregloUno.colocar(i, i + 1);
    arregloDos.colocar(i, (i + 1) + 5);
    arregloTres.colocar(i, (i + 1) + 10);
  }
  cout << arregloUno + arregloDos << endl;
  cout << arregloUno + arregloDos + arregloTres << endl;
  return true;
}
