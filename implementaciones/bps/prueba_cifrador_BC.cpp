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

int probarComposicion(vector<char> alfabeto)
{
  CifradorBC BC(alfabeto,8,8);
  string cadena{""};
  mpz_class num = 0;

  for (int i = 0; i < 100000; i += 23)
  {
    for (int j = 5; j < 15; j++)
    {
      for (int k = 0; k < j; k++)
        cadena += alfabeto[(i * 7) % alfabeto.size()];
      BC.colocarTamBloque(j);
      num = BC.componer(cadena);
      if (cadena != BC.descomponer(num, cadena.size()))
        return 0;
      cadena = "";
    }
  }
  return 1;
}

/* ========================================================================= */

int main(int argc, char* argv[])
{
  vector<char> alfabetoNumerico;
  vector<char> alfabetoAlfabetico1;
  vector<char> alfabetoAlfabetico2;
  vector<char> alfabetoAlfabetico3;
  vector<char> alfabetoAlfanumerico1;
  vector<char> alfabetoAlfanumerico2;
  vector<char> alfabetoAlfanumerico3;
  vector<vector<char> > alfabetos;

  for (int i = 0; i < 10; i++)
  {
    alfabetoNumerico.push_back('0' + i);
    alfabetoAlfanumerico1.push_back('0' + i);
    alfabetoAlfanumerico2.push_back('0' + i);
    alfabetoAlfanumerico3.push_back('0' + i);
  }

  for (int i = 0; i < 26; i++)
  {
    alfabetoAlfabetico1.push_back('a' + i);
    alfabetoAlfabetico3.push_back('a' + i);
    alfabetoAlfanumerico1.push_back('a' + i);
    alfabetoAlfanumerico3.push_back('a' + i);
  }

  for (int i = 0; i < 26; i++)
  {
    alfabetoAlfabetico2.push_back('A' + i);
    alfabetoAlfabetico3.push_back('A' + i);
    alfabetoAlfanumerico2.push_back('A' + i);
    alfabetoAlfanumerico3.push_back('A' + i);
  }

  alfabetos.push_back(alfabetoNumerico);
  alfabetos.push_back(alfabetoAlfabetico1);
  alfabetos.push_back(alfabetoAlfabetico2);
  alfabetos.push_back(alfabetoAlfabetico3);
  alfabetos.push_back(alfabetoAlfanumerico1);
  alfabetos.push_back(alfabetoAlfanumerico2);
  alfabetos.push_back(alfabetoAlfanumerico3);

  for (unsigned int i = 0; i<alfabetos.size(); i++)
  {
    if (probarComposicion(alfabetos[i]) == 0)
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
