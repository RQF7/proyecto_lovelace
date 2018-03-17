/**
 * \file
 * \brief Prueba de AES, implementación, crypto++
 * Proyecto Lovelace.
 */

#include "cabeceras/prueba_CBC_MAC.hh"
#include <cryptopp/aes.h>
#include <cryptopp/cbcmac.h>
#include <cryptopp/drbg.h>
#include <cryptopp/filters.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <string>

using namespace std;
using namespace CryptoPP;
using namespace PruebasCryptopp;

/**
 * Registra las funciones de prueba de CBC MAC en la lista de funciones a probar
 * que mantiene la clase de Prueba.
 */

PruebaCBCMAC::PruebaCBCMAC()
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Proceso de generación de MAC",
    PruebaCBCMAC::probarCifrado
  });
}

/**
 * Prueba la generación de MACs en dos mensajes muy parecidos, con la misma
 * llave. Si los MACs son iguales, entonces la prueba falla.
 *
 * \return Estado de la prueba.
 */

bool PruebaCBCMAC::probarCifrado()
{
  /* Generar llave */
  byte llave[AES::DEFAULT_KEYLENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, AES::DEFAULT_KEYLENGTH);

  CBC_MAC<AES> cbcmac {llave};
  string textoUno = "abcdefghijklmnopqrstuvwxyz";
  string textoDos = "abcdefghijklmnoqprstuvwxyz";

  cbcmac.Update(reinterpret_cast<const unsigned char*>(textoUno.c_str()),
    textoUno.length() + 1);
  byte mac[cbcmac.DigestSize()];
  cbcmac.TruncatedFinal(mac, cbcmac.DigestSize());

  cbcmac.Update(reinterpret_cast<const unsigned char*>(textoDos.c_str()),
    textoDos.length() + 1);
  byte macDos[cbcmac.DigestSize()];
  cbcmac.TruncatedFinal(macDos, cbcmac.DigestSize());

  cout << "Texto uno: " << textoUno << endl << "MAC: ";
  for (unsigned int i = 0; i < cbcmac.DigestSize(); i++)
    cout << "0x" << hex << (0xFF & mac[i]) << " ";
  cout << endl;

  cout << "Texto dos: " << textoDos << endl << "MAC: ";
  for (unsigned int i = 0; i < cbcmac.DigestSize(); i++)
    cout << "0x" << hex << (0xFF & macDos[i]) << " ";
  cout << endl;

  bool bandera = false;
  for (unsigned int i = 0; i < cbcmac.DigestSize(); i++)
    if (mac[i] != macDos[i])
    {
      bandera = true;
      break;
    }

  if (!bandera)
    return false;

  return true;
}
