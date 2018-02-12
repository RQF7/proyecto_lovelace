/*
 * Archivo principal de pruebas de librerías.
 * Proyecto Lovelace.
 */

#include "cryptopp/cabeceras/prueba_AES.hh"
#include "cryptopp/cabeceras/prueba_salsa20.hh"
#include "openssl/cabeceras/prueba_IDEA.hh"
#include <iostream>
#include <vector>

using namespace std;

/**
 * \brief Programa de prueba de librerías criptográficas.
 *
 * Itera sobre todas las clases de prueba de librerías criptográficas.
 * Este programa define la estructura que tienen todos los programas de
 * pruebas: un vector con clases de prueba; cada clase agrupa funciones
 * de prueba sobre alguna funcionalidad en específico.
 *
 * Realmente para las libreríascriptográficas no tiene mucho sentido, dado que
 * no es código propio (las funciones siempre regresan «verdadero»). Sin
 * embargo, hacer esto nos permite tener ya un modelo de clases de pruebas
 * listo.
 */

int main()
{
  vector<Prueba> clasesDePrueba
  {
    PruebasCryptopp::PruebaAES {},
    PruebasCryptopp::PruebaSalsa20 {},
    PruebasOpenssl::PruebaIDEA {}
  };
  for (auto claseDePrueba : clasesDePrueba)
    if (!claseDePrueba.probar())
      exit(-1);
  exit(0);
}
