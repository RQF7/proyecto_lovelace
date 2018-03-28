/**
 * \file
 * \brief Implementación de pruebas de utilidades de tarjetas.
 */

#include "cabeceras/utilidades_criptograficas.hh"
#include "cabeceras/utilidades_criptograficas_prueba.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
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
  Arreglo<unsigned char> llaveUno = generarLlave(16);
  Arreglo<unsigned char> llaveUnoCopia = generarLlave(16);
  Arreglo<unsigned char> llaveDos = generarLlave(8);
  Arreglo<unsigned char> llaveDosCopia = generarLlave(8);
  Arreglo<unsigned char> llaveTres = generarLlave(32);
  Arreglo<unsigned char> llaveTresCopia = generarLlave(32);

  cout << "Prueba uno (16): " << endl;
  for (int i = 0; i < 16; i++)
    cout << "0x" << hex << (0xFF & llaveUno[i]) << " ";
  cout << dec << endl;
  for (int i = 0; i < 16; i++)
    cout << "0x" << hex << (0xFF & llaveUnoCopia[i]) << " ";
  cout << dec << endl;
  if (llaveUno == llaveUnoCopia)
    return false;

  cout << "Prueba dos (8): " << endl;
  for (int i = 0; i < 8; i++)
    cout << "0x" << hex << (0xFF & llaveDos[i]) << " ";
  cout << dec << endl;
  for (int i = 0; i < 8; i++)
    cout << "0x" << hex << (0xFF & llaveDosCopia[i]) << " ";
  cout << dec << endl;
  if (llaveDos == llaveDosCopia)
    return false;

  cout << "Prueba tres (32): " << endl;
  for (int i = 0; i < 32; i++)
    cout << "0x" << hex << (0xFF & llaveTres[i]) << " ";
  cout << dec << endl;
  for (int i = 0; i < 32; i++)
    cout << "0x" << hex << (0xFF & llaveTresCopia[i]) << " ";
  cout << dec << endl;
  if (llaveTres == llaveTresCopia)
    return false;

  return true;
}
