/*
 * Archivo principal de pruebas de librerías.
 * Proyecto Lovelace.
 */

#include "cryptopp/cabeceras/prueba_AES.hh"
#include <iostream>

using namespace std;

int main ()
{
  PruebaAES pruebaAES {};
  if (pruebaAES.probar())
    exit(0);
  else
    exit(-1);
}
