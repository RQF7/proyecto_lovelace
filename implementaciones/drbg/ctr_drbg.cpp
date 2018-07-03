/**
 * \file
 * \brief Definición de un DRBG basado en cifrado por bloques.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/ctr_drbg.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>

using namespace Implementaciones;
using namespace CryptoPP;
using namespace std;

/**
 * Proceso de instanciación dado en el estándar, en la sección 10.2.1.3.1:
 * cuando no se ocupa una función de derivación.
 *
 * \param fuenteDeAlatoriedad     Apuntador a función generadora de entropía.
 *                                (la clase no es respondable de esta memoria).
 * \param cadenaDePersonalizacion Cadena opcional de personalización.
 * \param nivelDeSeguridad        Máximo nivel de seguridad soportado.
 * \param tipoDeCifrador          Tipo de cifrado por bloque a usar.
 *
 * \throw PersonalizacionDemasiadoGrande Si la cadena de personzalización
 *                                       excede lo dado en
 *                                       \p longitudPersonalizacion.
 */

CTRDRBG::CTRDRBG(
  Arreglo<unsigned char> cadenaDePersonalizacion,
  NivelDeSeguridad nivelDeSeguridad,
  TipoDeCifrador tipoDeCifrador,
  FuenteDeAleatoriedad *fuenteDeAlatoriedad
)
: DRBG{cadenaDePersonalizacion, nivelDeSeguridad,
    static_cast<unsigned int>(tipoDeCifrador) + 16u, /* Longitud de semilla. */
    static_cast<unsigned int>(tipoDeCifrador) + 16u, /* Personalización. */
    524288ull / 8ull,        /* Longitud máxima: 2 ^ 19 bits. */
    281474976710656ull,      /* Vida útil de semilla: 2 ^ 48. */
    fuenteDeAlatoriedad
  },
  mTipoDeCifrador {tipoDeCifrador},
  mLongitudLlave {static_cast<unsigned int>(mTipoDeCifrador)},
  mLongitudBloque {16u},
  mLlave (mLongitudLlave)
{
  Arreglo<unsigned char> materialDeLlave = mSemilla ^ cadenaDePersonalizacion;
  mSemilla.colocarConstante(0);
  mLlave.colocarConstante(0);
  actualizarEstado(materialDeLlave);
}

/**
 * Llama a la operación equivalente en la superclase y,
 * basándose en la nueva entropía, vuelve a derivar el valor inicial de
 * la semilla y de la costante (la información crítica). Esto corresponde a la
 * sección 10.1.1.3 de estándar.
 */

void CTRDRBG::cambiarSemilla()
{
  DRBG::cambiarSemilla();
  actualizarEstado(mSemilla);
}

/**
 * Elimina (pone en ceros) la información crítica que se mantiene en la
 * esta clase: el valor de la constante. Manda a llamar a la operación
 * equivalente de la superclase.
 */

void CTRDRBG::desinstanciar()
{
  DRBG::desinstanciar();
  mLlave.colocarConstante(0);
}

/**
 * Función generadora de bytes aleatorios (llamada desde clase
 * abstracta).
 *
 * \return Arreglo con el número de bytes solicitados.
 */

Arreglo<unsigned char> CTRDRBG::generarBytes(
  entero longitud         /**< Longitud de salida. */
)
{
  unsigned int longitudLocal = static_cast<unsigned int>(longitud);
  Arreglo<unsigned char> resultado;
  while (resultado.obtenerNumeroDeElementos() < longitudLocal)
  {
    mSemilla = ((mSemilla + 1ull) / Arreglo<unsigned int>{mLongitudBloque})[0];
    resultado = resultado || cifrarBloque(mSemilla);
  }
  return (resultado / Arreglo<unsigned int>{longitudLocal})[0];
}

/**
 * Operación de actualización de estado. En el estándar corresponde a
 * CTR_DRBG_Update (sección 10.2.1.2). Calcula un nuevo valor para
 * la semilla y para la llave del cifrado por bloques.
 */

void CTRDRBG::actualizarEstado(
  const Arreglo<unsigned char>& entrada   /**< Arreglo de entrada (entropía). */
)
{
  Arreglo<unsigned char> temporal;
  while (temporal.obtenerNumeroDeElementos() < mLongitudSemilla)
  {
    mSemilla = ((mSemilla + 1ull) / Arreglo<unsigned int>{mLongitudBloque})[0];
    temporal = temporal || cifrarBloque(mSemilla);
  }
  temporal = (temporal / Arreglo<unsigned int>{mLongitudSemilla})[0];
  temporal = temporal ^ entrada;
  mLlave = (temporal / Arreglo<unsigned int>{mLongitudLlave})[0];
  mSemilla = (temporal / Arreglo<unsigned int>{mLongitudSemilla})[0];
}

/**
 * Interfaz con cifrado por bloques de cryptopp. Cifra el bloque dado.
 *
 * \todo Hacer integración con AESNI.
 *
 * \return Bloque cifrado.
 */

Arreglo<unsigned char> CTRDRBG::cifrarBloque(
  const Arreglo<unsigned char>& bloque    /**< Bloque a cifrar. */
)
{
  unsigned char *resultadoDuro = new unsigned char[mLongitudBloque];
  string cadena;
  AES::Encryption cifradoAES {mLlave.obtenerApuntador(), mLongitudLlave};
  ECB_Mode_ExternalCipher::Encryption cifradoECB {cifradoAES};
  StreamTransformationFilter filtro(cifradoECB, new StringSink(cadena),
    StreamTransformationFilter::NO_PADDING);
  filtro.Put(bloque.obtenerApuntador(), mLongitudBloque);
  filtro.MessageEnd();
  memcpy(resultadoDuro, cadena.c_str(), mLongitudBloque);
  return Arreglo<unsigned char>(mLongitudBloque, move(resultadoDuro));
}
