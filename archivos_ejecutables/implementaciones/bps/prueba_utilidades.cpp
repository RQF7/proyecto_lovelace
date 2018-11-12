/**
 * Proyecto Lovelace.
 * Pruebas de la clase de Utilidades.
 */

#include "cabeceras/utilidades.hh"

#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

#include <gmpxx.h>
#include <gmp.h>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace Implementaciones;

/* ========================================================================= */

int probarMod(int mod, int cota)
{
  UtilidadesBPS util;
  for(int i = -cota; i < cota; i++)
    if(util.mod(i, mod) < 0 || util.mod(i, mod) >= mod)
      return 0;
  return 1;
}

/* ========================================================================= */

int probarStringMpz(mpz_class num)
{
  UtilidadesBPS util;
  string cad = util.numeroACadena(num);
  mpz_class numx = util.cadenaANumero(cad);
  if(num == numx) return 1;
  else            return 0;
}

/* ========================================================================= */

int main(int argc, char* argv[])
{
  for (int i = 1; i < 100000; i += 23)
  {
    if (probarMod(i, 1000) == 0)
    {
      cout << "ERROR, La función Utilidades::mod() es incorrecta." << endl;
      exit(-1);
    }
    mpz_class x = i;
    if (probarStringMpz(x) == 0)
    {
      cout << "ERROR, Las funciones Utilidades::numeroACadena() y ";
      cout << "Utilidades::cadenaANumero son incorrectas." << endl;
      exit(-1);
    }
  }

  cout << "============================================================" << endl
       << "###           PRUEBAS FINALIZADAS CORRECTAMENTE          ###" << endl
       << "============================================================" << endl;

  return 0;
}

/* ========================================================================= */
