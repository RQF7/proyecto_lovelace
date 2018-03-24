/**
 * \file
 * \brief Archivo principal de pruebas de utilidades.
 * Proyecto Lovelace.
 */


#include "cabeceras/arreglo_prueba.hh"
#include "cabeceras/arreglo_de_digitos_prueba.hh"
#include "cabeceras/conjunto_de_pruebas.hh"
#include "cabeceras/prueba.hh"
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
  ConjuntoDePruebas pruebas
  {
    "PRUEBAS DE UTILIDADES",
    {
      ArregloPrueba {},
      UtilidadesMatematicasPrueba {},
      ArregloDeDigitosPrueba {}
    }
  };
}
