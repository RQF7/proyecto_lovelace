/**
 * \file
 * \brief Archivo principal de pruebas de ffx y componentes.
 * Proyecto Lovelace.
 */

#include "cabeceras/arreglo_prueba.hh"
#include "cabeceras/red_feistel_prueba.hh"
#include "cabeceras/red_feistel_alternante_prueba.hh"
#include "cabeceras/red_feistel_desbalanceada_prueba.hh"
#include <iostream>
#include <vector>

using namespace ImplementacionesPruebas;
using namespace std;

/**
 * \brief Programa de prueba de FFX y derivados.
 *
 * \return Estado de las pruebas.
 */

int main()
{
  vector<Prueba> clasesDePrueba
  {
    ArregloPrueba {},
    RedFeistelPrueba {},
    RedFeistelAlternantePrueba {},
    RedFeistelDesbalanceadaPrueba {}
  };
  for (auto claseDePrueba : clasesDePrueba)
    if (!claseDePrueba.probar())
      exit(-1);
  exit(0);
}
