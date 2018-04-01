/**
 * \file
 * \brief Definición de un DRGB basado en una función hash.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/hash_drgb.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

/**
 * \param fuenteDeAlatoriedad     Apuntador a función generadora de entroía.
 *                                (la clase no es respondable de esta memoria).
 * \param cadenaDePersonalizacion Cadena opcional de personalización.
 * \param nivelDeSeguridad        Máximo nivel de seguridad soportado.
 * \param funcionHash             Tipo de función hash a usar.
 *
 * \throw PersonalizacionDemasiadoGrande Si la cadena de personzalización
 *                                       excede lo dado en
 *                                       \p longitudPersonalizacion.
 */

HashDRGB::HashDRGB(
  FuenteDeAleatoriedad fuenteDeAlatoriedad,
  Arreglo<unsigned char> cadenaDePersonalizacion
  NivelDeSeguridad nivelDeSeguridad,
  FuncionHash funcionHash
)
: DRGB{fuenteDeAlatoriedad, cadenaDePersonalizacion, nivelDeSeguridad,
    (static_cast<int>(funcionHash) <= 256) ? 440 : 880,
    34359738368ull,   /* Longitud de personalización: 2 ^ 35. */
    524288ull,        /* Longitud máxima: 2 ^ 19. */
    281474976710656,  /* Vida útil de semilla: 2 ^ 48. */
  },
  mFuncionHash {funcionHash}
{
  mSemmila = funcionDeDerivacion(mSemilla + mCadenaDePersonalizacion,
    mLongitudSemilla);
  mConstanteSemilla = funcionDeDerivacion(Arreglo<unsigned char>{0} + mSemilla,
    mLongitudSemilla);
}
