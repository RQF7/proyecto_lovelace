/**
 * \file
 * \brief Definición de clase de conjunto de pruebas.
 */

#include "cabeceras/conjunto_de_pruebas.hh"
#include "cabeceras/prueba.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace Utilidades;
using namespace std;

/**
 * Ejecuta las pruebas dadas en el vector y termina el programa con el
 * resultado.
 */

[[noreturn]]
ConjuntoDePruebas::ConjuntoDePruebas(string mensaje, vector<Prueba> pruebas)
{
  int contador = 1;
  bool resultadoGlobal = true;
  cout << "*******************************************************************"
       << endl;

  for (unsigned int i = 0; i < (63 - mensaje.size() + 2) / 2; i++)
    cout << "*";
  cout << " " << mensaje << " ";
  for (unsigned int i = 0; i < (63 - mensaje.size() + 2) / 2; i++)
    cout << "*";

  cout << endl
       << "*******************************************************************"
       << endl << endl;

  for (auto claseDePrueba : pruebas)
  {
    cout << "Prueba " << contador << " de " << pruebas.size()
         << ": " << claseDePrueba.obtenerMensaje() << endl
         << "==================================================================="
         << endl << endl;

    bool resultadoLocal = claseDePrueba.probar();
    resultadoGlobal &= resultadoLocal;
    contador++;

    cout
        << "==================================================================="
        << endl << endl;
  }

  if (resultadoGlobal)
    exit(EXIT_SUCCESS);
  exit(EXIT_FAILURE);
}
