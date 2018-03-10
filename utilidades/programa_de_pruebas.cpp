/**
 * \file
 * \brief Archivo principal de pruebas de utilidades.
 * Proyecto Lovelace.
 */


#include "cabeceras/arreglo_prueba.hh"
#include "cabeceras/utilidades_matematicas_prueba.hh"
#include <iostream>
#include <vector>

using namespace UtilidadesPruebas;
using namespace Utilidades;
using namespace std;

/**
 * \brief Programa de prueba de utilidades.
 *
 * \return Estado de las pruebas.
 */

int main()
{
  vector<Prueba> clasesDePrueba
  {
    ArregloPrueba {},
    UtilidadesMatematicasPrueba {}
  };
  for (auto claseDePrueba : clasesDePrueba)
    if (!claseDePrueba.probar())
      exit(-1);
  exit(0);
}
