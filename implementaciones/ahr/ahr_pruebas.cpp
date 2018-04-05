#include "cabeceras/ahr.hh"
#include "../utilidades/cabeceras/algoritmo_tokenizador.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include <iostream>

using namespace std;
using namespace Implementaciones;

int main()
{
  unsigned char llave1[32] = { 0xc4,0x7b,0x02,0x94,0xdb,0xbb,0xee,0x0f,
                      0xec,0x47,0x57,0xf2,0x2f,0xfe,0xee,0x35,0x87,0xca,0x47,
                      0x30,0xc3,0xd3,0x3b,0x69,0x1d,0xf3,0x8b,0xab,0x07,0x6b,
                      0xc5,0x58};

  CDV* accesoADatos = new AccesoMySQL {};
  ArregloDeDigitos pan2 (string{"585236564456"});
  ArregloDeDigitos pan1 (string{"1122333116565728"});
  ArregloDeDigitos pan3 (string{"887766322946577840"});
  ArregloDeDigitos resultado;

  AlgoritmoTokenizador* tokenizador {nullptr};
  tokenizador = new AHR{accesoADatos, llave1};

  cout << "1. Tokenizando " << pan1.obtenerCadenaEfectiva() << endl;
  resultado = tokenizador->operar({pan1});
  cout << "\t->Resultado tokenización: "
    << resultado.obtenerCadenaEfectiva() << endl;

  resultado = tokenizador->deoperar({resultado});
    cout << "\t->Resultado detokenización: "
      << resultado.obtenerCadenaEfectiva() << endl;

  cout << "2. Tokenizando " << pan2.obtenerCadenaEfectiva() << endl;
  resultado = tokenizador->operar({pan2});
  cout << "\t->Resultado tokenización: "
    << resultado.obtenerCadenaEfectiva() << endl;

  resultado = tokenizador->deoperar({resultado});
    cout << "\t->Resultado detokenización: "
      << resultado.obtenerCadenaEfectiva() << endl;

  cout << "3. Tokenizando " << pan3.obtenerCadenaEfectiva() << endl;
  resultado = tokenizador->operar({pan3});
  cout << "\t->Resultado tokenización: "
    << resultado.obtenerCadenaEfectiva() << endl;

  resultado = tokenizador->deoperar({resultado});
    cout << "\t->Resultado detokenización: "
      << resultado.obtenerCadenaEfectiva() << endl;

}
