/**
 * \file
 * \brief Prueba de implementaciones de entropía en hardware desde cryptopp.
 *
 * La que debe de funcionar es «RDSEED».
 */

#include <cryptopp/rdrand.h>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace CryptoPP;

int main()
{
  RDRAND generador {};
  byte* bloque = new byte[16];
  generador.GenerateBlock(bloque, 16);
  for (int i = 0; i < 16; i++)
    cout << "0x" << hex << (0xFF & bloque[i]) << " ";
  delete bloque;
  return 0;
}
