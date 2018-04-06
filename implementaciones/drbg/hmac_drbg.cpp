/**
 * \file
 * \brief Decaración de un DRBG basado en HMAC.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/hmac_drgb.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

using namespace Implementaciones;
using namespace std;

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
: DRBG(fuenteDeAlatoriedad, cadenaDePersonalizacion, nivelDeSeguridad)
{
}