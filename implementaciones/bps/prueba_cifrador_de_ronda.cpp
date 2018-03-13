/**
 * Proyecto Lovelace.
 * Pruebas de la clase de Cifrador de Ronda.
 */

#include "cabeceras/cifrador_de_ronda.hh"

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

int probarCifradoDescifrado(string mensaje)
{
  CifradorDeRonda cifradorDeRonda;
  byte llave[AES::DEFAULT_KEYLENGTH];
  string cifrado;

  for (unsigned int i = 0; i < 256; i++)
  {
    memset(llave, i, AES::DEFAULT_KEYLENGTH);

    cifradorDeRonda.colocarCifrador(CifradorDeRonda::BANDERA_AES);
    cifrado = cifradorDeRonda.cifrar(mensaje, llave);
    if (mensaje != cifradorDeRonda.descifrar(cifrado, llave))
      return 0;

    cifradorDeRonda.colocarCifrador(CifradorDeRonda::BANDERA_TDES);
    cifrado = cifradorDeRonda.cifrar(mensaje, llave);
    if (mensaje != cifradorDeRonda.descifrar(cifrado, llave))
      return 0;
  }
  return 1;
}

/* ========================================================================= */

int main(int argc, char* argv[])
{
  vector<string> mensajes;
  mensajes.push_back("ABCDEFGHIJKLMNOP");
  mensajes.push_back("abvcdefghijklmop");
  mensajes.push_back("0123456789012345");
  mensajes.push_back("ABCDEFGHabcdefgh");
  mensajes.push_back("ijklmnopIJKLMNOP");
  mensajes.push_back("DanielAyalaZamor");
  mensajes.push_back("gatoGatoGATOgATO");
  mensajes.push_back("IWHATYOUTOKNOWNO");
  mensajes.push_back("071296CDMX232323");
  mensajes.push_back("TOKIOPARISBOSTON");
  mensajes.push_back("SIMONPANTALEONSI");
  mensajes.push_back("comidacorridayea");
  mensajes.push_back("3438947892738492");
  mensajes.push_back("huiHUIHUIhIuhIhI");
  mensajes.push_back("ZZZZAAAXXXAAAZZZ");

  for (unsigned int i = 0; i < mensajes.size(); i++)
  {
    if (probarCifradoDescifrado(mensajes[i]) == 0)
    {
      cout << "ERROR, Los metodos CifradorDeRonda::cifrar() y ";
      cout << "CifradorDeRonda::descifrar() son incorrectas." << endl;
      exit(-1);
    }
  }

  cout << "============================================================" << endl
       << "###           PRUEBAS FINALIZADAS CORRECTAMENTE          ###" << endl
       << "============================================================" << endl;

  return 0;
}
