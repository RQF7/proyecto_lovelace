/**
 * Proyecto Lovelace.
 * Pruebas de la clase de Cifrador BPS.
 */

#include "cabeceras/cifrador_BPS.hh"

#include <iostream>
#include <fstream>
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

int probar_cifradoDescifrado(string claro, byte llave[], mpz_class tweak, 
                      vector<char> alfabeto, unsigned int num_de_rondas){

  string cifrado, descifrado;
  CifradorBPS BPS(alfabeto,num_de_rondas);
  
  cifrado    = BPS.cifrar(claro, llave, tweak);
  descifrado = BPS.descifrar(cifrado, llave, tweak);
  
  if(claro == descifrado) 
    return 1;
  return 0;
}

/* ========================================================================= */

int main(int argc, char* argv[]) 
{  
  unsigned int num_de_rondas = 8;
  byte llave[10][AES::DEFAULT_KEYLENGTH];
  mpz_class tweak[10];
  
  memset(llave[0], 0xFF, AES::DEFAULT_KEYLENGTH);
  memset(llave[1], 0x00, AES::DEFAULT_KEYLENGTH);
  memset(llave[2], 0xA2, AES::DEFAULT_KEYLENGTH);
  memset(llave[3], 0x45, AES::DEFAULT_KEYLENGTH);
  memset(llave[4], 0x23, AES::DEFAULT_KEYLENGTH);
  memset(llave[5], 0xED, AES::DEFAULT_KEYLENGTH);
  memset(llave[6], 0xD3, AES::DEFAULT_KEYLENGTH);
  memset(llave[7], 0x7C, AES::DEFAULT_KEYLENGTH);
  memset(llave[8], 0x51, AES::DEFAULT_KEYLENGTH);
  memset(llave[9], 0x07, AES::DEFAULT_KEYLENGTH);
  
  tweak[0] = 0x2323232323232323;
  tweak[1] = 0xADF345389FDD3C92;
  tweak[2] = 0x565656569A9A9A12;
  tweak[3] = 0x869C854F74423A8B;
  tweak[4] = 0xFDEACCDEADCBBEFA;
  tweak[5] = 0x1243153134351536;
  tweak[6] = 0x10F00FF00F000FF0;
  tweak[7] = 0x0000000000028783;
  tweak[8] = 0x124315FFFFFFFF00;
  tweak[9] = 0xFDDEA23982783293;

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


  ifstream archivo_numerico("valores/numericos.txt");
  ifstream archivo_alfabetico1("valores/alfabeticos1.txt");
  ifstream archivo_alfabetico2("valores/alfabeticos2.txt");
  ifstream archivo_alfabetico3("valores/alfabeticos3.txt");
  ifstream archivo_alfanumerico1("valores/alfanumericos1.txt");
  ifstream archivo_alfanumerico2("valores/alfanumericos2.txt");
  ifstream archivo_alfanumerico3("valores/alfanumericos3.txt");
  
  vector<string> valores_numerico;
  vector<string> valores_alfabetico1;
  vector<string> valores_alfabetico2;
  vector<string> valores_alfabetico3;
  vector<string> valores_alfanumerico1;
  vector<string> valores_alfanumerico2;
  vector<string> valores_alfanumerico3;
  vector<vector<string> > valores;

  string valor;
  while (archivo_numerico >> valor) valores_numerico.push_back(valor);
  while (archivo_alfabetico1 >> valor) valores_alfabetico1.push_back(valor);
  while (archivo_alfabetico2 >> valor) valores_alfabetico2.push_back(valor);
  while (archivo_alfabetico3 >> valor) valores_alfabetico3.push_back(valor);
  while (archivo_alfanumerico1 >> valor) valores_alfanumerico1.push_back(valor);
  while (archivo_alfanumerico2 >> valor) valores_alfanumerico2.push_back(valor);
  while (archivo_alfanumerico3 >> valor) valores_alfanumerico3.push_back(valor);

  valores.push_back(valores_numerico);
  valores.push_back(valores_alfabetico1);
  valores.push_back(valores_alfabetico2);
  valores.push_back(valores_alfabetico3);
  valores.push_back(valores_alfanumerico1);
  valores.push_back(valores_alfanumerico2);
  valores.push_back(valores_alfanumerico3);

  int resultado = 0;
  for(int a=0; a<7; a++){
    cout << "====================================================" << endl
         << "             Pruebas con el alfabeto " << a+1 << endl
         << "====================================================" << endl;
    for(int l=0; l<10; l++){
      for(int t=0; t<10; t++){
        for(unsigned int i=0; i<valores[a].size(); i++)
        {
          cout << "# Cifrando con: ..................................."
               << endl << "  Cadena: "  << valores[a][i] << endl
               << "  Llave: " << l << " " << "Tweak: " << t << endl;
  
          resultado = probar_cifradoDescifrado(valores[a][i],llave[l],tweak[t],
                                               alfabetos[a],num_de_rondas);
          
          if(resultado == 0)
          {
            cout << "PRUEBA FALLIDA:" << endl
                 << "No se ha posido cifrar y cifrar correctamente." << endl
                 << "Cadena: "  << valores[a][i] << endl
                 << "Llave: " << l << " " << "Tweak: " << t << endl;
            exit(-1);
          }
          else
            cout << "  Exitoso!" << endl; 
        }
      }
    }
  }

  cout << "============================================================" << endl
       << "###    PRUEBA GENERAL DE BPS FINALIZADA CORRECTAMENTE    ###" << endl
       << "============================================================" << endl;

  return 0;

}