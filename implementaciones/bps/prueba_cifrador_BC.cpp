/**
 * Proyecto Lovelace.
 * Pruebas de la clase de Cifrador BC.
 * NOTA: El cifrado y descifrado de BC se prueba con BPS.
 */

#include "cabeceras/cifrador_BC.hh"

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
using namespace CryptoPP;

/* ========================================================================= */
int probar_composicion(vector<char> alfabeto)
{
  CifradorBC BC(alfabeto,8,8);
  string cadena{""};
  mpz_class num = 0;
  
  for(int i=0; i<100000; i+=23)
  {
    for(int j=5; j<15; j++)
    {
      for(int k=0; k<j; k++)
        cadena += alfabeto[(i*7) % alfabeto.size()];
      BC.setTamBloque(j);
      num = BC.componer(cadena);
      if(cadena != BC.descomponer(num,cadena.size()))
        return 0;
      cadena = "";
    }
  }
  return 1;
}

/* ========================================================================= */
int main(int argc, char* argv[])
{
  vector<char> alfabeto_numerico;
  vector<char> alfabeto_alfabetico1;
  vector<char> alfabeto_alfabetico2;
  vector<char> alfabeto_alfabetico3;
  vector<char> alfabeto_alfanumerico1;
  vector<char> alfabeto_alfanumerico2;
  vector<char> alfabeto_alfanumerico3;
  vector<vector<char> > alfabetos;

  for(int i=0; i<10; i++)
  {
    alfabeto_numerico.push_back('0' + i);
    alfabeto_alfanumerico1.push_back('0' + i);
    alfabeto_alfanumerico2.push_back('0' + i);
    alfabeto_alfanumerico3.push_back('0' + i);
  }

  for(int i=0; i<26; i++)
  {
    alfabeto_alfabetico1.push_back('a' + i);
    alfabeto_alfabetico3.push_back('a' + i);
    alfabeto_alfanumerico1.push_back('a' + i);
    alfabeto_alfanumerico3.push_back('a' + i);
  }

  for(int i=0; i<26; i++)
  {
    alfabeto_alfabetico2.push_back('A' + i);
    alfabeto_alfabetico3.push_back('A' + i);
    alfabeto_alfanumerico2.push_back('A' + i);
    alfabeto_alfanumerico3.push_back('A' + i);
  }

  alfabetos.push_back(alfabeto_numerico);
  alfabetos.push_back(alfabeto_alfabetico1);
  alfabetos.push_back(alfabeto_alfabetico2);
  alfabetos.push_back(alfabeto_alfabetico3);
  alfabetos.push_back(alfabeto_alfanumerico1);
  alfabetos.push_back(alfabeto_alfanumerico2);
  alfabetos.push_back(alfabeto_alfanumerico3);

  for(unsigned int i=0; i<alfabetos.size(); i++)
  {
    if(probar_composicion(alfabetos[i]) == 0)
    {
      cout << "ERROR, Las funciones CifradorBC::componer() y ";
      cout << "CifradorBC::descomponer() son incorrectas." << endl;
      exit(-1);
    }
  }

  cout << "============================================================" << endl
       << "###           PRUEBAS FINALIZADAS CORRECTAMENTE          ###" << endl
       << "============================================================" << endl;

  return 0;
}

/* ========================================================================= */
