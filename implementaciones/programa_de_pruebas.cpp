/**
 * \file
 * \brief Archivo principal de pruebas de ffx y componentes.
 * Proyecto Lovelace.
 */

#include "ffx/cabeceras/combinacion_por_bloque_prueba.hh"
#include "ffx/cabeceras/combinacion_por_caracter_prueba.hh"
#include "ffx/cabeceras/ffx_a10_prueba.hh"
#include "ffx/cabeceras/ronda_ffx_a10_prueba.hh"
#include "redes_feistel/cabeceras/red_feistel_prueba.hh"
#include "redes_feistel/cabeceras/red_feistel_alternante_prueba.hh"
#include "redes_feistel/cabeceras/red_feistel_desbalanceada_prueba.hh"
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
  vector<Utilidades::Prueba> clasesDePrueba
  {
    RedFeistelPrueba {},
    RedFeistelAlternantePrueba {},
    RedFeistelDesbalanceadaPrueba {},
    CombinacionPorCaracterPrueba {},
    CombinacionPorBloquePrueba {},
    RondaFFXA10Prueba {},
    FFXA10Prueba {}
  };
  for (auto claseDePrueba : clasesDePrueba)
    if (!claseDePrueba.probar())
      exit(-1);
  exit(0);
}
