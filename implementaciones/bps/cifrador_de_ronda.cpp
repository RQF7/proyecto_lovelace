/**
 * \file
 * \brief Implementación de la clase del cifrador de ronda.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/cifrador_de_ronda.hh"

#include <iostream>
#include <iomanip>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

/* ========================================================================= */

CifradorDeRonda::CifradorDeRonda()
{
}

/* ========================================================================= */

unsigned int CifradorDeRonda::obtenerTamBloque()
{
  return 128;
}

/* ========================================================================= */

/**
 * Método para cifrar una cadena con la llave dada, este utiliza AES de
 * forma interna, y el modo de operación ECB sin padding para cifrar
 * forzosamente bloques de 128 bits.
 */

string CifradorDeRonda::cifrar(string mensaje, byte llave[])
{
  string salida;

  AES::Encryption cifradorSimple(llave, AES::DEFAULT_KEYLENGTH);
  ECB_Mode_ExternalCipher::Encryption cifrador(cifradorSimple);
  if(mensaje.size() == 16)
  {
    StreamTransformationFilter filtro(cifrador, new StringSink(salida),
      StreamTransformationFilter::NO_PADDING);
    filtro.Put(reinterpret_cast<const unsigned char*>
      (mensaje.c_str()), mensaje.size());
    filtro.MessageEnd();
  }
  else
  {
    StreamTransformationFilter filtro(cifrador, new StringSink(salida));
    filtro.Put(reinterpret_cast<const unsigned char*>
      (mensaje.c_str()), mensaje.size());
    filtro.MessageEnd();
  }

  return salida;
}

/* ========================================================================= */

/**
 * Método para descifrar una cadena con la llave dada, este utiliza AES
 * de forma interna, y el modo de operación ECB sin padding para usar
 * forzosamente bloques de 128 bits.
 */

string CifradorDeRonda::descifrar(string mensaje, byte llave[])
{
  string salida;

  AES::Decryption descifradorSimple(llave, AES::DEFAULT_KEYLENGTH);
  ECB_Mode_ExternalCipher::Decryption descifrador(descifradorSimple);
  if(mensaje.size() == 16)
  {
    StreamTransformationFilter filtro(descifrador, new StringSink(salida),
      StreamTransformationFilter::NO_PADDING);
    filtro.Put(reinterpret_cast<const unsigned char*>
      (mensaje.c_str()), mensaje.size());
    filtro.MessageEnd();
  }
  else
  {
    StreamTransformationFilter filtro(descifrador, new StringSink(salida));
    filtro.Put(reinterpret_cast<const unsigned char*>
      (mensaje.c_str()), mensaje.size());
    filtro.MessageEnd();
  }

  return salida;
}
