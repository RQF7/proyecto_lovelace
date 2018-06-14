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
 * Inicializa una nueva instancia de un generador. Pasa al contructor de DRBG
 * genérico los valores por defecto definidos en el estándar: la longitud de la
 * semilla depende del tipo de función hash a utilizar (de SHA256 para abajo,
 * 440 bits, y para arriba, 880 bits) y el tiempo de vida útil de la semilla
 * 2^48 (entre otros).
 *
 * Define la clase concreta para la función hash interna (una instancia de
 * HashTransformation, de cryptopp).
 *
 * \note Esto último debería poderse hacer con operadores ternarios dentro de la
 * lista de inicialización: cada vez que lo intento, la compilación muere.
 *
 * En la superclase se obtiene la entropía del generador; una vez obtenida, en
 * esta se siguen los pasos para inicializar la semilla y el valor constante
 * (sección 10.1.1.2 del estándar).
 *
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
    281474976710656ull,      /* Vida útil de semilla: 2 ^ 48. */
  },
  mTipoDeFuncionHash {tipoDeFuncionHash}
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
 *
 * \note Como este apuntador es exclusivo a la vida del objeto, sí se debe
 * liberar aquí.
 */

HashDRBG::~HashDRBG()
{
  delete mFuncionHash;
}

/**
 * Llama a la operación equivalente en la superclase y,
 * basándose en la nueva entropía, vuelve a derivar el valor inicial de
 * la semilla y de la costante (la información crítica). Esto corresponde a la
 * sección 10.1.1.3 de estándar.
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
 * Define el proceso de generación de bytes pseudoaleatorios. Corresponde a la
 * sección 10.1.1.4 del estándar. El trabajo para generar los nuevos bytes se
 * encuentra en funcionDeGeneracion (es la misma división del documento, pero
 * con nombres distintios), también se genera un nuevo estado para la semilla.
 *
 * \return Arreglo con bytes aleatorios.
 */

Arreglo<unsigned char> HashDRBG::generarBytes(
  entero longitud           /**< Número de bytes deseados. */
)
{
  auto resultado = funcionDeGeneracion(static_cast<unsigned int>(longitud));
  auto temporal = hash(Arreglo<unsigned char>{3} || mSemilla);
  mSemilla = mSemilla + temporal
    + mConstanteSemilla + Arreglo<unsigned char>(mContadorDePeticiones);
  return resultado;
}

/**
 * Función de derivación de semilla basada en la función hash interna (sección
 * 10.3 del estándar). Ocupa la cadena de entrada (la entropía, en la mayoría de
 * los casos) para generar un primer estado para la semilla.
 *
 * \return Derivación de la cadena de entrada.
 */

Arreglo<unsigned char> HashDRBG::funcionDeDerivacion(
  const Arreglo<unsigned char>& cadenaDeEntrada,  /**< Cadena a derivar. */
  unsigned int longitudDeSalida                   /**< Longitud de salida. */
)
{
  Arreglo<unsigned char> resultado;
  unsigned int longitud = mFuncionHash->DigestSize();
  unsigned int numeroDeBloques = ceil(
    static_cast<double>(longitudDeSalida) / longitud);
  for (unsigned int i = 0; i < numeroDeBloques; i++)
  {
    Arreglo<unsigned char> entrada =
      Arreglo<unsigned char>{static_cast<unsigned char>(i)}
      || Arreglo<unsigned char>{static_cast<unsigned char>(longitudDeSalida)}
      || cadenaDeEntrada;
    auto salidaHash = hash(entrada);
    resultado = resultado || salidaHash;
  }
  return (resultado / Arreglo<unsigned int>{longitudDeSalida})[0];
}

/**
 * Función ocupada por generarBytes para generar el número de bytes aleatorios
 * usando la función hash interna y el valor de la semilla.
 */

Arreglo<unsigned char> HashDRBG::funcionDeGeneracion(
  unsigned int longitudDeSalida     /**< Longitud de la salida. */
)
{
  Arreglo<unsigned char> resultado;
  unsigned int longitud = mFuncionHash->DigestSize();
  unsigned int numeroDeBloques = ceil(
    static_cast<double>(longitudDeSalida) / longitud);
  Arreglo<unsigned char> datos {mSemilla};
  for (unsigned int i = 0; i < numeroDeBloques; i++)
  {
    resultado = resultado || hash(datos);
    datos = datos || Arreglo<unsigned char>{1};
  }
  return (resultado / Arreglo<unsigned int>{longitudDeSalida})[0];
}

/**
 * Interfaz con objeto de función hash de cryptopp. Regresa un hash del arreglo
 * dado. Ocupa mFuncionHash, definida en el constructor.
 *
 * \return Hash de cadena de entrada.
 */

Arreglo<unsigned char> HashDRBG::hash(
  const Arreglo<unsigned char>& entrada   /**< Bytes de entrada. */
)
{
  unsigned char* salidaDura = new unsigned char[mFuncionHash->DigestSize()];
  mFuncionHash->Update(entrada.obtenerApuntador(),
    entrada.obtenerNumeroDeElementos());
  mFuncionHash->Final(salidaDura);
  return Arreglo<unsigned char>(mFuncionHash->DigestSize(), move(salidaDura));
}
