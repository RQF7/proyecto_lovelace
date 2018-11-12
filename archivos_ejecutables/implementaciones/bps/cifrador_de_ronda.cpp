/**
 * \file
 * \brief Implementación de la clase del cifrado de ronda.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/cifrador_de_ronda.hh"

#include <iostream>
#include <iomanip>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/des.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;
using namespace Implementaciones;

/* ========================================================================= */

CifradorDeRonda::CifradorDeRonda()
{
  tipo = BANDERA_AES;
}

/* ========================================================================= */

CifradorDeRonda::CifradorDeRonda(unsigned int cifrador)
{
  tipo = cifrador;
}

/* ========================================================================= */

void CifradorDeRonda::colocarCifrador(unsigned int cifrador)
{
  tipo = cifrador;
}

/* ========================================================================= */

unsigned int CifradorDeRonda::obtenerCifrador()
{
  return tipo;
}

/* ========================================================================= */

unsigned int CifradorDeRonda::obtenerTamBloque()
{
  if(tipo == BANDERA_AES)
    return AES::DEFAULT_KEYLENGTH * 8;
  else
    return DES_EDE2::DEFAULT_KEYLENGTH * 8;
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

  if (tipo == BANDERA_AES)
  {
    AES::Encryption cifradorSimple(llave, AES::DEFAULT_KEYLENGTH);
    ECB_Mode_ExternalCipher::Encryption cifrador(cifradorSimple);
    if (mensaje.size() == AES::DEFAULT_KEYLENGTH)
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
  }
  else
  {
    DES_EDE2::Encryption cifradorSimple(llave, DES_EDE2::DEFAULT_KEYLENGTH);
    ECB_Mode_ExternalCipher::Encryption cifrador(cifradorSimple);
    if (mensaje.size() == DES_EDE2::DEFAULT_KEYLENGTH)
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

  if (tipo == BANDERA_AES)
  {
    AES::Decryption descifradorSimple(llave, AES::DEFAULT_KEYLENGTH);
    ECB_Mode_ExternalCipher::Decryption descifrador(descifradorSimple);
    if (mensaje.size() == AES::DEFAULT_KEYLENGTH)
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
  }
  else
  {
    DES_EDE2::Decryption descifradorSimple(llave, DES_EDE2::DEFAULT_KEYLENGTH);
    ECB_Mode_ExternalCipher::Decryption descifrador(descifradorSimple);
    if (mensaje.size() == DES_EDE2::DEFAULT_KEYLENGTH)
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
  }

  return salida;
}
