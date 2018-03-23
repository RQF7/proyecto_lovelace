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
  mListaDePruebas.push_back(FuncionDePrueba{
    "prueba la operación de escritura",
    ArregloDeDigitosPrueba::probarColocar
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
  ArregloDeDigitos prueba(4);
  prueba[0] = 1;
  prueba[1] = 2;
  prueba[2] = 3;
  prueba[3] = 4;
  cout << "Primera prueba: " << prueba << " "
       << prueba.obtenerNumero() << endl;
  if (prueba.obtenerNumero() != 1234ull ||
    prueba.obtenerCadena() != "1234")
    return false;

  return true;
}
