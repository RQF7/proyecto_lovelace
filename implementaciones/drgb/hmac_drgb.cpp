/**
 * \file
 * \brief Decaración de un DRGB basado en HMAC.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/hmac_drgb.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

/**
 * \param fuenteDeAlatoriedad     Apuntador a función generadora de entroía.
 *                                (la clase no es respondable de esta memoria).
 * \param cadenaDePersonalizacion Cadena opcional de personalización.
 * \param nivelDeSeguridad        Máximo nivel de seguridad soportado.
 */

HMACDRGB::HMACDRGB(
  FuenteDeAleatoriedad fuenteDeAlatoriedad,
  Arreglo<unsigned char> cadenaDePersonalizacion
  NivelDeSeguridad nivelDeSeguridad
)
: DRGB(fuenteDeAlatoriedad, cadenaDePersonalizacion, nivelDeSeguridad)
{
}
