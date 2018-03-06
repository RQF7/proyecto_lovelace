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

/* ========================================================================= */
int probar_mod(int mod, int cota)
{
  Utilidades util;
  for(int i=-cota; i<cota; i++)
    if(util.mod(i,mod) < 0 || util.mod(i,mod) >= mod)
      return 0;
  return 1;
}

/* ========================================================================= */
int probar_stringMpz(mpz_class num)
{
  Utilidades util;
  string cad = util.numToString(num);
  mpz_class numx = util.stringToNum(cad);
  if(num == numx) return 1;
  else            return 0;
}

/* ========================================================================= */
int main(int argc, char* argv[])
{
  for(int i=1; i<100000; i+=23)
  {
    if(probar_mod(i,1000) == 0)
    {
      cout << "ERROR, La función Utilidades::mod() es incorrecta." << endl;
      exit(-1);
    }
    mpz_class x = i;
    if(probar_stringMpz(x) == 0){
      cout << "ERROR, Las funciones Utilidades::numToString() y ";
      cout << "Utilidades::stringToNum son incorrectas." << endl;
      exit(-1);
    }
  }

  cout << "============================================================" << endl
       << "###           PRUEBAS FINALIZADAS CORRECTAMENTE          ###" << endl
       << "============================================================" << endl;

  return 0;
}

/* ========================================================================= */
