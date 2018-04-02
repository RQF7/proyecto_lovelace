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
: Prueba{"pruebas para el arreglo de dígitos"}
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "prueba la operación de los constructores",
    ArregloDeDigitosPrueba::probarConstructores
  });
  mListaDePruebas.push_back(FuncionDePrueba{
    "prueba la operación de escritura",
    ArregloDeDigitosPrueba::probarColocar
  });
  mListaDePruebas.push_back(FuncionDePrueba{
    "prueba la obtención de una cadena efectiva",
    ArregloDeDigitosPrueba::probarCadenaEfectiva
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
  ArregloDeDigitos pruebaUno ("123456");
  ArregloDeDigitos pruebaDos (76589ull);
  cout << "Prueba uno: " << pruebaUno << " "
       << pruebaUno.obtenerNumero() << endl
       << "Prueba dos: " << pruebaDos << " "
       << pruebaDos.obtenerNumero() << endl;

  if (pruebaUno.obtenerNumero() != 123456ull ||
    pruebaDos.obtenerCadena() != "76589")
    return false;
  return true;
}


/**
 * Prueba la construcción de un arreglo vacío que se va llenando después
 * de la construcción. Esta función se creo solo por razones de compatibilidad
 * con los Srreglos normales, en realidad, siempre que sea posible, hay que
 * inicializar el arreglo desde el contructor, y no cambiarlo durante su vida
 * útil.
 *
 * \retrun Estado de la prueba.
 */

bool ArregloDeDigitosPrueba::probarColocar()
{
  ArregloDeDigitos prueba(4u);
  prueba[0] = 1;
  prueba[1] = 2;
  prueba[2] = 3;
  prueba[3] = 4;
  cout << "Primera prueba: " << prueba << " "
       << prueba.obtenerNumero() << endl;
  if (prueba.obtenerNumero() != 1234ull ||
    prueba.obtenerCadena() != "1234")
    return false;

  prueba[0] = 5;
  prueba[2] = 9;
  cout << "Segunda prueba: " << prueba << " "
       << prueba.obtenerNumero() << endl;
  if (prueba.obtenerNumero() != 5294ull ||
    prueba.obtenerCadena() != "5294")
    return false;

  return true;
}

/**
 * Prueba la función para quitar ceros a la izquierda de una representación
 * interna.
 *
 * \return Estado de la prueba.
 */

bool ArregloDeDigitosPrueba::probarCadenaEfectiva()
{
  ArregloDeDigitos arregloUno {0, 0, 1, 2, 3};
  string pruebaUno = arregloUno.obtenerCadenaEfectiva();
  cout << "Prueba uno: " << endl
       << arregloUno << endl
       << pruebaUno << endl;
  if (pruebaUno != "123")
    return false;

  ArregloDeDigitos arregloDos {1, 2, 3};
  string pruebaDos = arregloDos.obtenerCadenaEfectiva();
  cout << "Prueba uno: " << endl
       << arregloDos << endl
       << pruebaDos << endl;
  if (pruebaDos != "123")
    return false;

  ArregloDeDigitos arregloTres {0, 1, 2, 3};
  string pruebaTres = arregloTres.obtenerCadenaEfectiva();
  cout << "Prueba uno: " << endl
       << arregloTres << endl
       << pruebaTres << endl;
  if (pruebaTres != "123")
    return false;

  return true;
}
