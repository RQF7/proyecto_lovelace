/**
 * \file
 * \brief Implementación de pruebas de utilidades de tarjetas.
 */

#include "cabeceras/utilidades_criptograficas.hh"
#include "cabeceras/utilidades_criptograficas_prueba.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

UtilidadesCriptograficasPrueba::UtilidadesCriptograficasPrueba()
: Utilidades::Prueba{"pruebas de utilidades criptográficas"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "generación de llaves pseudoaleatorias.",
    UtilidadesCriptograficasPrueba::probarGeneracionDeLlaves
  });
}

/**
 * Prueba la generación de llaves pseudoaleatorias.
 *
 * \return Estado de la prueba.
 */

bool UtilidadesCriptograficasPrueba::probarGeneracionDeLlaves()
{
  unsigned char* llaveUno = generarLlave(16);
  unsigned char* llaveDos = generarLlave(8);
  unsigned char* llaveTres = generarLlave(32);

  cout << "Prueba uno (16): " << endl;
  for (int i = 0; i < 16; i++)
    cout << "0x" << hex << (0xFF & llaveUno[i]) << " ";
  cout << dec << endl;

  cout << "Prueba dos (8): " << endl;
  for (int i = 0; i < 8; i++)
    cout << "0x" << hex << (0xFF & llaveDos[i]) << " ";
  cout << dec << endl;

  cout << "Prueba tres (32): " << endl;
  for (int i = 0; i < 32; i++)
    cout << "0x" << hex << (0xFF & llaveTres[i]) << " ";
  cout << dec << endl;

  delete[] llaveUno;
  delete[] llaveDos;
  delete[] llaveTres;
  return true;
}
