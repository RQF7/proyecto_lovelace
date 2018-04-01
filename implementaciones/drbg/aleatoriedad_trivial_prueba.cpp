/**
 * \file
 * \brief Implementación de pruebas del lector de aleatoriedad de archivo.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/aleatoriedad_trivial.hh"
#include "cabeceras/aleatoriedad_trivial_prueba.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

AleatoriedadTrivialPrueba::AleatoriedadTrivialPrueba()
: Utilidades::Prueba{"pruebas de aleatoriedad trivial"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operación con miembros triviales",
    AleatoriedadTrivialPrueba::probarOperacion
  });
}

/**
 *
 *
 * \return Estado de la prueba.
 */

bool AleatoriedadTrivialPrueba::probarOperacion()
{
  AleatoriedadTrivial aleatoriedad {};
  Arreglo<unsigned char> resultadoUno = aleatoriedad.operar({8});
  cout << "Alatorio uno (8): ";
  for (unsigned int i = 0; i < resultadoUno.obtenerNumeroDeElementos(); i++)
    cout << "0x" << hex << (0xFF & resultadoUno[i]) << " ";
  cout << endl;

  Arreglo<unsigned char> resultadoDos = aleatoriedad.operar({16});
  cout << "Alatorio dos (16): ";
  for (unsigned int i = 0; i < resultadoDos.obtenerNumeroDeElementos(); i++)
    cout << "0x" << hex << (0xFF & resultadoDos[i]) << " ";
  cout << endl;

  Arreglo<unsigned char> resultadoTres = aleatoriedad.operar({128});
  cout << "Alatorio tres (128): ";
  for (unsigned int i = 0; i < resultadoTres.obtenerNumeroDeElementos(); i++)
    cout << "0x" << hex << (0xFF & resultadoTres[i]) << " ";
  cout << endl;

  return true;
}
