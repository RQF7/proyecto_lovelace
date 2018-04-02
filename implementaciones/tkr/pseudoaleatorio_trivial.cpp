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
 *
 * \return Arreglo de dígitos con PAN válido aleatorio.
 */

ArregloDeDigitos PseudoaleatorioTrivial::operar(
  const std::vector<unsigned int>& entrada   /**< Longitud de salida.. */
)
{
  ArregloDeDigitos resultado(entrada[0]);
  random_device dispositivo;
  mt19937_64 generador{dispositivo()};
  uniform_int_distribution<int> distribucion(0, 9);
  for (unsigned int i = 0; i < resultado.obtenerNumeroDeElementos() - 1; i++)
    resultado[i] = modulo(distribucion(generador), 10);
  resultado[resultado.obtenerNumeroDeElementos() - 1] =
    algoritmoDeLuhn(resultado, true);
  return resultado;
}
