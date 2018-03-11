/**
 * Proyecto Lovelace.
 * Pruebas de la clase de Codificador.
 */

#include "cabeceras/codificador.hh"

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

int probarCodificacion(vector<char> alfabeto)
{
  Codificador codificador(alfabeto);
  unsigned char caracter;
  for (unsigned int i = 0; i < alfabeto.size(); i++)
  {
    caracter = codificador.codificar(alfabeto[i]);
    if (caracter >= alfabeto.size())
      return 0;
    caracter = codificador.decodificar(caracter);
    if (caracter != alfabeto[i])
      return 0;
  }
  return 1;
}

/* ========================================================================= */

int probarSumaRestaMod(vector<char> alfabeto)
{
  Codificador codificador(alfabeto);
  string A{""}, B{""}, C{""};

  for (int i = 0; i < 1000; i += 23)
  {
    for (int j = 5; j < 15; j++)
    {
      for (int k = 0; k < j; k++)
      {
        A += alfabeto[(i * 7) % alfabeto.size()];
        B += alfabeto[(i * 11) % alfabeto.size()];
      }
      C = codificador.sumaMod(A, B);
      if (codificador.restaMod(C, B) != A)
        return 0;
      A = "";
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

  for(unsigned int i = 0; i < alfabetos.size(); i++)
  {
    if(probarCodificacion(alfabetos[i]) == 0)
    {
      cout << "ERROR, Las funciones Codificador::codificar() y ";
      cout << "Utilidades::decodificar son incorrectas." << endl;
      exit(-1);
    }
    if(probarSumaRestaMod(alfabetos[i]) == 0)
    {
      cout << "ERROR, Las funciones Codificador::sumaMod() y ";
      cout << "Utilidades::restaMod son incorrectas." << endl;
      exit(-1);
    }
  }

  cout << "============================================================" << endl
       << "###           PRUEBAS FINALIZADAS CORRECTAMENTE          ###" << endl
       << "============================================================" << endl;

  return 0;
}
