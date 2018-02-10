/*
 * Archivo principal de pruebas de librerías.
 * Proyecto Lovelace.
 */

#include "cryptopp/cabeceras/prueba_AES.hh"
#include "cryptopp/cabeceras/prueba_salsa20.hh"
#include <iostream>

using namespace std;

int main ()
{
  PruebaAES pruebaAES {};
  PruebaSalsa20 pruebaSalsa20 {};
  if (pruebaAES.probar() &&
      pruebaSalsa20.probar())
    exit(0);
  else
    exit(-1);
}
