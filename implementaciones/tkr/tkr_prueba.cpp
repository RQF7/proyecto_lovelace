/**
 * \file
 * \brief Implementación de pruebas de TKR2.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/tkr.hh"
#include "cabeceras/tkr_prueba.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

TKRPrueba::TKRPrueba()
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operación con miembros triviales",
    TKRPrueba::probarOperacionTrivial
  });
}

bool TKRPrueba::probarOperacionTrivial()
{
  TKR tkr {};
  Arreglo<int> panUno {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6};
  Arreglo<int> tokenUno = tkr.tokenizar(panUno, Arreglo<int>{});
  Arreglo<int> panDos = tkr.detokenizar(tokenUno, Arreglo<int>{});
  cout << "Prueba uno: " << endl
       << "PAN uno: " << panUno << endl
       << "Token uno: " << tokenUno << endl
       << "PAN dos: " << panDos << endl;
  if (tokenUno.obtenerNumeroDeElementos() != 16)
    return false;

  return true;
}
