/**
 * \file
 * \brief Definición de un DRBG basado en una función hash.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/hash_drbg.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <cryptopp/sha.h>
#include <cmath>
#include <iostream>

using namespace Implementaciones;
using namespace CryptoPP;
using namespace std;

/**
 * \param fuenteDeAlatoriedad     Apuntador a función generadora de entroía.
 *                                (la clase no es respondable de esta memoria).
 * \param cadenaDePersonalizacion Cadena opcional de personalización.
 * \param nivelDeSeguridad        Máximo nivel de seguridad soportado.
 * \param tipoDeFuncionHashfuncionHash Tipo de función hash a usar.
 *
 * \throw PersonalizacionDemasiadoGrande Si la cadena de personzalización
 *                                       excede lo dado en
 *                                       \p longitudPersonalizacion.
 */

HashDRBG::HashDRBG(
  FuenteDeAleatoriedad *fuenteDeAlatoriedad,
  Arreglo<unsigned char> cadenaDePersonalizacion,
  NivelDeSeguridad nivelDeSeguridad,
  TipoDeFuncionHash tipoDeFuncionHash
)
: DRBG{fuenteDeAlatoriedad, cadenaDePersonalizacion, nivelDeSeguridad,
    (static_cast<int>(tipoDeFuncionHash) <= 256) ? 440u / 8u : 880u / 8u,
    34359738368ull / 8ull,   /* Longitud de personalización: 2 ^ 35 bits. */
    524288ull / 8ull,        /* Longitud máxima: 2 ^ 19 bits. */
    281474976710656,         /* Vida útil de semilla: 2 ^ 48. */
  },
  mTipoDeFuncionHash {mTipoDeFuncionHash}
{
  if (mTipoDeFuncionHash == TipoDeFuncionHash::SHA1)
    mFuncionHash = new SHA1;
  else if (mTipoDeFuncionHash == TipoDeFuncionHash::SHA224)
    mFuncionHash = new SHA224;
  else if (mTipoDeFuncionHash == TipoDeFuncionHash::SHA256)
    mFuncionHash = new SHA256;
  else if (mTipoDeFuncionHash == TipoDeFuncionHash::SHA384)
    mFuncionHash = new SHA384;
  else
    mFuncionHash = new SHA512;
  mSemilla = funcionDeDerivacion(mSemilla || mCadenaDePersonalizacion,
    mLongitudSemilla);
  mConstanteSemilla = funcionDeDerivacion(Arreglo<unsigned char>{0} || mSemilla,
    mLongitudSemilla);
}

/**
 * Liberación de memoria reservada.
 */

HashDRBG::~HashDRBG()
{
  delete mFuncionHash;
}

/**
 * Llama a la operación equivalente en la superclase y vuelve,
 * basandose en la nueva entropía, vuelve a derivar el valor inicial de
 * la semilla y de la costante (la información crítica).
 */

void HashDRBG::cambiarSemilla()
{
  auto valorAnterior(move(mSemilla));
  DRBG::cambiarSemilla();
  mSemilla = funcionDeDerivacion(Arreglo<unsigned char>{1} || valorAnterior
    || mSemilla, mLongitudSemilla);
  mConstanteSemilla = funcionDeDerivacion(Arreglo<unsigned char>{0}
    || mSemilla, mLongitudSemilla);
}

/**
 * Elimina (pone en ceros) la información crítica que se mantiene en la
 * esta clase: el valor de la constante. Manda a llamar a la operación
 * equivalente de la superclase.
 */

void HashDRBG::desinstanciar()
{
  DRBG::desinstanciar();
  mConstanteSemilla.colocarConstante(0);
}

/**
 * Función de derivación de semilla basada en la función hash interna.
 */

Arreglo<unsigned char> HashDRBG::funcionDeDerivacion(
  const Arreglo<unsigned char>& cadenaDeEntrada,
  unsigned int longitudDeSalida
)
{
  Arreglo<unsigned char> resultado;
  unsigned int longitud = mFuncionHash->DigestSize();
  unsigned int numeroDeBloques = ceil(
    static_cast<double>(longitudDeSalida) / longitud);
  for (unsigned int i = 0; i < numeroDeBloques; i++)
  {
    unsigned char *salidaDura = new unsigned char[longitud];
    Arreglo<unsigned char> entrada =
      Arreglo<unsigned char>{static_cast<unsigned char>(i)}
      || Arreglo<unsigned char>{static_cast<unsigned char>(longitudDeSalida)}
      || cadenaDeEntrada;
    mFuncionHash->Update(entrada.obtenerApuntador(),
      entrada.obtenerNumeroDeElementos());
    mFuncionHash->Final(salidaDura);
    resultado = move(resultado
      || Arreglo<unsigned char>(longitud, move(salidaDura)));
  }
  return (resultado / Arreglo<unsigned int>{longitudDeSalida})[0];
}

/**
 *
 */

Arreglo<unsigned char> HashDRBG::generarBits(unsigned int longitud)
{
  return Arreglo<unsigned char>();
}
