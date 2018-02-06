/*
 * Super clase de todas las pruebas, definición.
 * Proyecto Lovelace.
 */

#include "cabeceras/prueba.hh"
#include <iostream>

using namespace std;

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
