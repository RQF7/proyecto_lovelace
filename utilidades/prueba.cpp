/**
 * \file
 * \brief Super clase de todas las pruebas, definición.
 * Proyecto Lovelace.
 */

#include "cabeceras/prueba.hh"
#include <iostream>

using namespace std;

/**
 * Ejecuta cada una de las funciones definidas en mListaDePruebas. Imprime
 * en la salida estándar el resultado de cada una.
 *
 * \return Verdadero en caso de que todas las pruebas se aprueben, falso si
 * al menos una falla.
 */

bool Prueba::probar()
{
  int contador = 1;
  bool resultadoGlobal = true;
  for (auto prueba : mListaDePruebas)
  {
    cout << "==> Prueba " << contador << ": " << prueba.obtenerDescripcion()
         << endl
         << "================================================================="
         << endl;
    bool resultadoLocal = (prueba.obtenerFuncion())();
    cout
         << "================================================================="
         << endl
         << "==> Resultado: " << (resultadoLocal ? "aceptado" : "rechazado")
         << endl << endl;
    resultadoGlobal &= resultadoLocal;
    contador++;
  }
  return resultadoGlobal;
}
