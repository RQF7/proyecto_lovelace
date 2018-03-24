/**
 * \file
 * \brief
 */

#include "cabeceras/arreglo.hh"
#include "cabeceras/codificador.hh"
#include <string>
#include <vector>

using namespace Utilidades;
using namespace std;

/**
 *
 */

const string Codificador::mAlfabeto =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz"
  "0123456789+/";

/**
 *
 */

Codificador::Codificador(
  Base base
)
: mBase {base},
  mTopeOrigen {(base == Base::Base64) ? 3 : (base == Base::Base32) ? 5 : 1},
  mTopeDestino {(base == Base::Base64) ? 4 : (base == Base::Base32) ? 8 : 2},
  mBufferOrigen {new unsigned char [mTopeOrigen]},
  mBufferDestino {new unsigned char [mTopeDestino]}
{
}

/**
 *
 */

Codificador::~Codificador()
{
  delete[] mBufferOrigen;
  delete[] mBufferDestino;
}

/**
 *
 */

string Codificador::operar(
  vector<Arreglo<unsigned char>>& entrada
)
{
  string resultado;
  int contador = 0;
  /* Proceso normal. */
  for (int i = 0; i < entrada[0].obtenerNumeroDeElementos(); i++)
  {
    mBufferOrigen[contador++] = entrada[0][i];
    if (contador == mTopeOrigen)
    {
      codificarBuffers(resultado, mTopeDestino);
      contador = 0;
    }
  }
  /* Elementos restantes. */
  if (contador != 0)
  {
    for (int i = contador; i < mTopeOrigen; i++)
      mBufferOrigen[i] = '\0';
    codificarBuffers(resultado, contador + 1);
  }
  return resultado;
}

/**
 *
 */

Arreglo<unsigned char> Codificador::deoperar(
  vector<string>& entrada
)
{
  Arreglo<unsigned char> resultado(entrada[0].size());
  int contador = 0;
  /* Proceso normal. */
  for (unsigned int i = 0; i < entrada[0].size(); i++)
  {
    mBufferDestino[contador++] = entrada[0][i];
    if (contador == mTopeDestino)
    {
      decodificarBuffers(resultado, i - mTopeDestino, mTopeOrigen);
      contador = 0;
    }
  }
  /* Elementos restantes. */
  if (contador != 0)
  {
    for (int i = contador; i < mTopeDestino; i++)
      mBufferDestino[i] = '\0';
    decodificarBuffers(resultado, entrada[0].size() - mTopeDestino, contador + 1);
  }
  return resultado;
}

/**
 *
 */

void Codificador::codificarBuffers(
  string &cadena,
  int limite
)
{
  if (mBase == Base::Base64)
    codificarBase64();
  else if (mBase == Base::Base32)
    codificarBase32();
  else
    codificarBase16();
  for (int i = 0; i < limite; i++)
    cadena += mAlfabeto[mBufferDestino[i]];
}

/**
 *
 */

void Codificador::decodificarBuffers(
  Arreglo<unsigned char> &arreglo,
  int contador,
  int limite
)
{
  if (mBase == Base::Base64)
    decodificarBase64();
  else if (mBase == Base::Base32)
    decodificarBase32();
  else
    decodificarBase16();
  for (int i = 0; i < limite; i++)
    arreglo[contador + i] = mBufferOrigen[i];
}

/**
 *
 */

void Codificador::codificarBase64()
{
  mBufferDestino[0] =  (mBufferOrigen[0] & 0b11111100) >> 2;
  mBufferDestino[1] = ((mBufferOrigen[0] & 0b00000011) << 4) +
                      ((mBufferOrigen[1] & 0b11110000) >> 4);
  mBufferDestino[2] = ((mBufferOrigen[1] & 0b00001111) << 2) +
                      ((mBufferOrigen[2] & 0b11000000) >> 6);
  mBufferDestino[3] =  (mBufferOrigen[2] & 0b00111111);
}

/**
 *
 */

void Codificador::decodificarBase64()
{
  mBufferOrigen[0] = ((mBufferDestino[0] & 0b00111111) << 2) +
                     ((mBufferDestino[1] & 0b00110000) >> 4);
  mBufferOrigen[1] = ((mBufferDestino[1] & 0b00001111) << 4) +
                     ((mBufferDestino[2] & 0b00111100) >> 2);
  mBufferOrigen[2] = ((mBufferDestino[2] & 0b00000011) << 6) +
                     ((mBufferDestino[3] & 0b00111111) >> 0);
}

/**
 *
 */

void Codificador::codificarBase32()
{
  mBufferDestino[0] =  (mBufferOrigen[0] & 0b11111000) >> 3;
  mBufferDestino[1] = ((mBufferOrigen[0] & 0b00000111) << 2) +
                      ((mBufferOrigen[1] & 0b11000000) >> 6);
  mBufferDestino[2] =  (mBufferOrigen[1] & 0b00111110) >> 1;
  mBufferDestino[3] = ((mBufferOrigen[1] & 0b00000001) << 4) +
                      ((mBufferOrigen[2] & 0b11110000) >> 4);
  mBufferDestino[4] = ((mBufferOrigen[2] & 0b00001111) << 1) +
                      ((mBufferOrigen[3] & 0b10000000) >> 7);
  mBufferDestino[5] =  (mBufferOrigen[3] & 0b01111100) >> 2;
  mBufferDestino[6] = ((mBufferOrigen[3] & 0b00000011) << 3) +
                      ((mBufferOrigen[4] & 0b11100000) >> 5);
  mBufferDestino[7] =  (mBufferOrigen[4] & 0b00011111);
}

/**
 *
 */

void Codificador::decodificarBase32()
{
  mBufferOrigen[0] = ((mBufferDestino[0] & 0b00011111) << 3) +
                     ((mBufferDestino[1] & 0b00011100) >> 2);
  mBufferOrigen[1] = ((mBufferDestino[1] & 0b00000011) << 6) +
                     ((mBufferDestino[2] & 0b00011111) << 1) +
                     ((mBufferDestino[3] & 0b00010000) >> 4);
  mBufferOrigen[2] = ((mBufferDestino[3] & 0b00001111) << 4) +
                     ((mBufferDestino[4] & 0b00011110) >> 1);
  mBufferOrigen[3] = ((mBufferDestino[4] & 0b00000001) << 7) +
                     ((mBufferDestino[5] & 0b00011111) << 2) +
                     ((mBufferDestino[6] & 0b00011000) >> 3);
  mBufferOrigen[4] = ((mBufferDestino[6] & 0b00000111) << 5) +
                     ((mBufferDestino[7] & 0b00011111) >> 0);
}

/**
 *
 */

void Codificador::codificarBase16()
{
  mBufferDestino[0] = (mBufferOrigen[0] & 0b11110000) >> 4;
  mBufferDestino[1] = (mBufferOrigen[0] & 0b00001111);
}

/**
 *
 */

void Codificador::decodificarBase16()
{
  mBufferOrigen[0] = (mBufferDestino[0] << 4) +
                      mBufferDestino[1];
}
