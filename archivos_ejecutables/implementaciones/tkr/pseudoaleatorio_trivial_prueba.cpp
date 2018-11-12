/**
 * \file
 * \brief Implementación de pruebas de función pseudoaleatoria trivial.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/pseudoaleatorio_trivial.hh"
#include "cabeceras/pseudoaleatorio_trivial_prueba.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

PseudoaleatorioTrivialPrueba::PseudoaleatorioTrivialPrueba()
: Utilidades::Prueba{"pruebas de pseudoaleatorio trivial"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "generación de tokens trivial",
    PseudoaleatorioTrivialPrueba::probarOperacion
  });
}

bool PseudoaleatorioTrivialPrueba::probarOperacion()
{
  PseudoaleatorioTrivial funcion;
  ArregloDeDigitos pruebaUno = funcion.operar({16});
  ArregloDeDigitos pruebaDos = funcion.operar({16});
  ArregloDeDigitos pruebaTres = funcion.operar({16});
  cout << "Prueba uno: " << pruebaUno << endl
       << "Prueba dos: " << pruebaDos << endl
       << "Prueba tres: " << pruebaTres << endl;
  if (pruebaUno.obtenerNumeroDeElementos() != 16 ||
    pruebaDos.obtenerNumeroDeElementos() != 16 ||
    pruebaTres.obtenerNumeroDeElementos() != 16 ||
    pruebaUno == pruebaDos || pruebaUno == pruebaTres ||
    pruebaDos == pruebaTres)
    return false;

  return true;
}
