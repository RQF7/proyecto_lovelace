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
int probar_codificacion(vector<char> alfabeto)
{
  Codificador codificador(alfabeto);
  unsigned char caracter;
  for(unsigned int i=0; i<alfabeto.size(); i++)
  {
    caracter = codificador.codificar(alfabeto[i]);
    if(caracter >= alfabeto.size())
      return 0;
    caracter = codificador.decodificar(caracter);
    if(caracter != alfabeto[i])
      return 0;
  }
  return 1;
}

/* ========================================================================= */
int probar_sumaRestaMod(vector<char> alfabeto)
{
  Codificador codificador(alfabeto);
  string A{""}, B{""}, C{""};
  
  for(int i=0; i<1000; i+=23)
  {
    for(int j=5; j<15; j++)
    {
      for(int k=0; k<j; k++)
      {
        A += alfabeto[(i*7) % alfabeto.size()];
        B += alfabeto[(i*11) % alfabeto.size()];
      }
      C = codificador.sumaMod(A,B);
      if(codificador.restaMod(C,B) != A)
        return 0;
      A = "";
    }
  }
  return 1;
}

/* ========================================================================= */
int main(int argc, char* argv[]) {

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
    if(probar_codificacion(alfabetos[i]) == 0)
    {
      cout << "ERROR, Las funciones Codificador::codificar() y ";
      cout << "Utilidades::decodificar son incorrectas." << endl;
      exit(-1);
    }
    if(probar_sumaRestaMod(alfabetos[i]) == 0){
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

/* ========================================================================= */
