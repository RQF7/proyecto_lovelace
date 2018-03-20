/**
 * \file
 * \brief Implementación de pruebas de utilidades matemáticas.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/arreglo_de_digitos.hh"
#include "cabeceras/arreglo_de_digitos_prueba.hh"
#include <iostream>

using namespace Utilidades;
using namespace UtilidadesPruebas;
using namespace std;

ArregloDeDigitosPrueba::ArregloDeDigitosPrueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "prueba la operación de los constructores",
    ArregloDeDigitosPrueba::probarConstructores
  });
}

/**
 * Prueba las conversiones numéricas realizadas en los constructores del
 * arreglo de dígitos.
 *
 * \return Estado de la prueba.
 */

bool ArregloDeDigitosPrueba::probarConstructores()
{
  ArregloDeDigitos pruebaUno {"123456"};
  ArregloDeDigitos pruebaDos {76589ull};
  cout << "Prueba uno: " << pruebaUno << " "
       << pruebaUno.obtenerNumero() << endl
       << "Prueba dos: " << pruebaDos << " "
       << pruebaDos.obtenerNumero() << endl;

  if (pruebaUno.obtenerNumero() != 123456ull ||
    pruebaDos.obtenerCadena() != "76589")
    return false;
  return true;
}
