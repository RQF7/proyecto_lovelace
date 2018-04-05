/**
 * \file
 * \brief Archivo principal de pruebas de ffx y componentes.
 * Proyecto Lovelace.
 */

#include "acceso_a_datos/cabeceras/acceso_mysql_prueba.hh"
#include "drbg/cabeceras/aleatoriedad_trivial_prueba.hh"
#include "drbg/cabeceras/ctr_drbg_prueba.hh"
#include "drbg/cabeceras/hash_drbg_prueba.hh"
#include "ffx/cabeceras/combinacion_por_bloque_prueba.hh"
#include "ffx/cabeceras/combinacion_por_caracter_prueba.hh"
#include "ffx/cabeceras/ffx_a10_prueba.hh"
#include "ffx/cabeceras/ronda_ffx_a10_prueba.hh"
#include "redes_feistel/cabeceras/red_feistel_prueba.hh"
#include "redes_feistel/cabeceras/red_feistel_alternante_prueba.hh"
#include "redes_feistel/cabeceras/red_feistel_desbalanceada_prueba.hh"
#include "tkr/cabeceras/funcion_rn_prueba.hh"
#include "tkr/cabeceras/pseudoaleatorio_aes_prueba.hh"
#include "tkr/cabeceras/pseudoaleatorio_trivial_prueba.hh"
#include "tkr/cabeceras/tkr_prueba.hh"
#include "ahr/cabeceras/ahr_prueba.hh"
#include "aes_ensamblador/cabeceras/aes_prueba.hh"
#include "utilidades/cabeceras/utilidades_criptograficas_prueba.hh"
#include "utilidades/cabeceras/utilidades_tarjetas_prueba.hh"
#include "../utilidades/cabeceras/conjunto_de_pruebas.hh"
#include <iostream>
#include "../utilidades/cabeceras/prueba.hh"
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
  Utilidades::ConjuntoDePruebas pruebas
  {
    "PRUEBAS DE IMPLEMENTACIONES",
    {
      RedFeistelPrueba {},
      RedFeistelAlternantePrueba {},
      RedFeistelDesbalanceadaPrueba {},
      CombinacionPorCaracterPrueba {},
      CombinacionPorBloquePrueba {},
      RondaFFXA10Prueba {},
      FFXA10Prueba {},
      UtilidadesTarjetasPrueba {},
      PseudoaleatorioTrivialPrueba {},
      PseudoaleatorioAESPrueba {},
      FuncionRNPrueba {},
      TKRPrueba {},
      AccesoMySQLPrueba {},
      UtilidadesCriptograficasPrueba {},
      AleatoriedadTrivialPrueba {},
      HashDRBGPrueba {},
      CTRDRBGPrueba {},
      AHRPrueba(),
      AESPrueba()
    }
  };
}
