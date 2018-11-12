/**
 * \file
 * \brief Archivo principal de pruebas de librerías.
 * Proyecto Lovelace.
 */

#include "cryptopp/cabeceras/prueba_AES.hh"
#include "cryptopp/cabeceras/prueba_salsa20.hh"
#include "cryptopp/cabeceras/prueba_SHA256.hh"
#include "cryptopp/cabeceras/prueba_CBC_MAC.hh"
#include "../utilidades/cabeceras/prueba.hh"
#include "../utilidades/cabeceras/conjunto_de_pruebas.hh"
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
  Utilidades::ConjuntoDePruebas prueba
  {
    "PRUEBAS CRYPTOPP",
    {
      PruebasCryptopp::PruebaAES {},
      PruebasCryptopp::PruebaSalsa20 {},
      PruebasCryptopp::PruebaSHA256 {},
      PruebasCryptopp::PruebaCBCMAC {}
    }
  };
}
