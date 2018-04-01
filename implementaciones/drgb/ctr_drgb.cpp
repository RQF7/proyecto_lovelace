/**
 * \file
 * \brief Definición de un DRGB basado en cifrador por bloques.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/ctr_drgb.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

/**
 * \param fuenteDeAlatoriedad     Apuntador a función generadora de entroía.
 *                                (la clase no es respondable de esta memoria).
 * \param cadenaDePersonalizacion Cadena opcional de personalización.
 * \param nivelDeSeguridad        Máximo nivel de seguridad soportado.
 */

CTRDRGB::CTRDRGB(
  FuenteDeAleatoriedad fuenteDeAlatoriedad,
  Arreglo<unsigned char> cadenaDePersonalizacion
  NivelDeSeguridad nivelDeSeguridad
)
: DRGB(fuenteDeAlatoriedad, cadenaDePersonalizacion, nivelDeSeguridad)
{
}
