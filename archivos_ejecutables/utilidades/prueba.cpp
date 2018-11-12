/**
 * \file
 * \brief Super clase de todas las pruebas, definición.
 * Proyecto Lovelace.
 */

#include "cabeceras/color.hh"
#include "cabeceras/prueba.hh"
#include <iostream>

using namespace Utilidades;
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
    cout << Color::Azul
         << "==> Subprueba " << contador << " de " << mListaDePruebas.size()
         << ": " << prueba.obtenerDescripcion() << endl
         << Color::Original
         << "-------------------------------------------------------------------"
         << endl;
    bool resultadoLocal = (prueba.obtenerFuncion())();
    cout
         << "-------------------------------------------------------------------"
         << endl << (resultadoLocal ? Color::Verde : Color::Rojo)
         << "==> Resultado: " << (resultadoLocal ? "aceptado" : "rechazado")
         << Color::Original << endl << endl;
    resultadoGlobal &= resultadoLocal;
    contador++;
  }
  return resultadoGlobal;
}
