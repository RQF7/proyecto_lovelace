/**
 * \file
 * \brief Definición de un DRBG basado en cifrador por bloques.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/ctr_drgb.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

using namespace Implementaciones;
using namespace std;

/**
 * \param fuenteDeAlatoriedad     Apuntador a función generadora de entropía.
 *                                (la clase no es respondable de esta memoria).
 * \param cadenaDePersonalizacion Cadena opcional de personalización.
 * \param nivelDeSeguridad        Máximo nivel de seguridad soportado.
 */

CTRDRGB::CTRDRGB(
  FuenteDeAleatoriedad fuenteDeAlatoriedad,
  Arreglo<unsigned char> cadenaDePersonalizacion
  NivelDeSeguridad nivelDeSeguridad
)
: DRBG(fuenteDeAlatoriedad, cadenaDePersonalizacion, nivelDeSeguridad)
{
}
