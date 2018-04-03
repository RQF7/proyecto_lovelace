/**
 * \file
 * \brief Implementación de codificador.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/arreglo.hh"
#include "cabeceras/codificador.hh"
#include <string>
#include <vector>

using namespace Utilidades;
using namespace std;

/**
 * Se utiliza el alfabeto propuesto en el RFC para la base 64; en el caso de
 * las otras dos bases se utilizan los primeros 32 y 16 caracteres,
 * respectivamente.
 */

const string Codificador::mAlfabeto =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz"
  "0123456789+/";

/**
 * Reserva la memoria necesaria para los buffers internos dependiendo del
 * la base utilizada.
 *
 * El tamaño de los buffers de destino y de origen responde a el primer
 * múltiplo común entre la base origen (256, en todos los casos) y la base
 * destino:
 * * Base 64: mcm(8, 6) = 24 = 8 * 3 = 6 * 4
 * * Base 32: mcm(8, 5) = 40 = 8 * 5 = 5 * 8
 * * Base 16: mcm(8, 4) =  8 = 8 * 1 = 4 * 2
 *
 * Se inicializa un apuntador a la función correspondiente de
 * codifiación/decodificación; esto ahorra pasos en el procesamiento.
 */

Codificador::Codificador(
  Base base                 /**< Base de codificación. */
)
: mBase {base},
  mTopeOrigen {(base == Base::Base64) ? 3 : (base == Base::Base32) ? 5 : 1},
  mTopeDestino {(base == Base::Base64) ? 4 : (base == Base::Base32) ? 8 : 2},
  mBufferOrigen {new unsigned char [mTopeOrigen]},
  mBufferDestino {new unsigned char [mTopeDestino]},
  mFuncionCodificacion {(base == Base::Base64) ? &Codificador::codificarBase64 :
                        (base == Base::Base32) ? &Codificador::codificarBase32 :
                                                 &Codificador::codificarBase16},
  mFuncionDecodificacion {(base == Base::Base64) ? &Codificador::decodificarBase64 :
                          (base == Base::Base32) ? &Codificador::decodificarBase32 :
                                                   &Codificador::decodificarBase16}
{
}

/**
 * Libera la memoria de los dos buffers internos.
 */

Codificador::~Codificador()
{
  delete[] mBufferOrigen;
  delete[] mBufferDestino;
}

/**
 * Operación de codificación. Procesa el arreglo de bytes dados y entrega
 * una cadena con los caracteres de mAlfabeto.
 *
 * \param entrada Vector con solo el primer elemento; bytes a codificar.
 *
 * \return Cadena con bytes codificador.
 */

string Codificador::operar(
  const vector<Arreglo<unsigned char>>& entrada
)
{
  string resultado;
  int contador = 0;
  /* Proceso normal. */
  for (unsigned int i = 0; i < entrada[0].obtenerNumeroDeElementos(); i++)
  {
    mBufferOrigen[contador++] = entrada[0][i];
    if (contador == mTopeOrigen)
    {
      codificarBuffers(resultado, mTopeDestino);
      contador = 0;
    }
  }
  /* Elementos restantes; padding. */
  if (contador != 0)
  {
    for (int i = contador; i < mTopeOrigen; i++)
      mBufferOrigen[i] = '\0';
    int limite = (mBase != Base::Base32) ? contador + 1 :
      (contador == 1) ? contador + 1 : contador + 2;
    codificarBuffers(resultado, limite);
    for (; limite < mTopeDestino; limite++)
      resultado += '=';
  }
  return resultado;
}

/**
 * Operación inversa para decodificar una cadena (codificada previamente);
 * regresa un arreglo de bytes.
 *
 * \return Arreglo de bytes decodificados.
 */

Arreglo<unsigned char> Codificador::deoperar(
  const vector<string>& entrada  /**< Cadena codificada (en primer elemento). */
)
{
  /* Establecer longitud. */
  int contadorPaddings = 0;
  for (unsigned int i = entrada[0].size() - 1; entrada[0][i] == '='; i--)
    contadorPaddings++;
  if (mBase == Base::Base32)
  {
    if (contadorPaddings == 6) contadorPaddings = 4;
    else if (contadorPaddings == 4) contadorPaddings = 3;
    else if (contadorPaddings == 3) contadorPaddings = 2;
    else if (contadorPaddings == 2) contadorPaddings = 1;
  }
  Arreglo<unsigned char> resultado(static_cast<unsigned int>((
    entrada[0].size() / mTopeDestino) * mTopeOrigen - contadorPaddings));
  int contador = 0;
  int contadorDos = 0;
  /* Proceso normal. */
  for (unsigned int i = 0; i < entrada[0].size() - contadorPaddings; i++)
  {
    mBufferDestino[contador++] = static_cast<unsigned char>(
      mAlfabeto.find(entrada[0][i]));
    if (contador == mTopeDestino)
    {
      decodificarBuffers(resultado, contadorDos, mTopeOrigen);
      contadorDos += mTopeOrigen;
      contador = 0;
    }
  }
  /* Elementos restantes. */
  if (contador != 0)
  {
    for (int i = contador; i < mTopeDestino; i++)
      mBufferDestino[i] = 'A';
    decodificarBuffers(resultado, contadorDos, contador - 1);
  }
  return resultado;
}

/**
 * Agrega a la cadena el resultado de una operación de codificación.
 * También sirve como multiplexación hacia las operaciones correspondientes
 * a la base miembro. Una implementación más inteligente haría esta decisión
 * desde el contructor (para no estarla repitiendo); sin embargo para eso
 * tengo que hacer clases extras, o pelearme con apuntadores a funciones
 * miembro no estáticas.
 *
 * El límite dado sirve para casos de extremos, en los que no siempre se
 * codifica toda la cadena.
 */

void Codificador::codificarBuffers(
  string &cadena,           /**< Referencia a cadena resultado. */
  int limite                /**< Número de elementos a agregar. */
)
{
  (this->*mFuncionCodificacion)();
  for (int i = 0; i < limite; i++)
    cadena += mAlfabeto[mBufferDestino[i]];
}

/**
 * Agrega al arreglo el resultado de la operación de decodificación.
 * La optimización planteada en la codificación también aplica para
 * este caso (tal vez se podría hacer que cada operación fuera una
 * instancia de una función con inverso; tiene sentido, pero son demasiadas
 * clases).
 */

void Codificador::decodificarBuffers(
  Arreglo<unsigned char> &arreglo,    /**< Referencia a arreglo resultado. */
  int contador,                       /**< Índice de arreglo. */
  int limite                          /**< Número de elementos a escribir. */
)
{
  (this->*mFuncionDecodificacion)();
  for (int i = 0; i < limite; i++)
    arreglo[contador + i] = mBufferOrigen[i];
}

/**
 * Operaciones a nivel de bits para codificar algo en base 64.
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
 * Operaciones a nivel de bits para codificar algo en base 64.
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
 * Operaciones a nivel de bits para codificar algo en base 32.
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
 * Operaciones a nivel de bits para decodificar algo en base 32.
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
 * Operaciones a nivel de bits para codificar algo en base 16.
 */

void Codificador::codificarBase16()
{
  mBufferDestino[0] = (mBufferOrigen[0] & 0b11110000) >> 4;
  mBufferDestino[1] = (mBufferOrigen[0] & 0b00001111);
}

/**
 * Operaciones a nivel de bits para decodificar algo en base 16.
 */

void Codificador::decodificarBase16()
{
  mBufferOrigen[0] = (mBufferDestino[0] << 4) +
                      mBufferDestino[1];
}
