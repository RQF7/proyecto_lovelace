/**
 * \file
 * \brief Definición de la función pseudoaleatoria temporal.
 */

#include "cabeceras/pseudoaleatorio_trivial.hh"
#include "../utilidades/cabeceras/utilidades_tarjetas.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../utilidades/cabeceras/utilidades_matematicas.hh"
#include <random>
#include <vector>
#include <iostream>

using namespace Implementaciones;
using namespace std;

/**
 * Implementación de función pseudoaleatoria no criptográfica. Solo para
 * pruebas y códigos temporales.
 */

ArregloDeDigitos PseudoaleatorioTrivial::operar(
  const std::vector<int>& entrada   /**< Nada en sí, pero la interfaz obliga. */
)
{
  ArregloDeDigitos resultado(16);
  random_device dispositivo;
  mt19937_64 generador{dispositivo()};
  uniform_int_distribution<int> distribucion(0, 9);
  for (int i = 0; i < 15; i++)
    resultado.colocar(i, modulo(distribucion(generador), 10));
  auto temporal = resultado.partir(2, 0, 7);
  resultado.colocar(15, algoritmoDeLuhn(temporal));
  return resultado;
}
