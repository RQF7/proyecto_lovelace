/**
 * \file
 * \brief Decaración de un DRBG basado en HMAC.
 *
 * Proyecto Lovelace.
 */

#ifndef __HMAC_DRGB__
#define __HMAC_DRGB__

#include "drbg.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

namespace Implementaciones
{
  /**
   * \brief
   *
   */

  class HMACDRGB : public DRBG
  {
    public:

      /** \brief Construcción de un generador basado en una fucnión hash. */
      HMACDRGB(FuenteDeAleatoriedad fuenteDeAlatoriedad,
        string cadenaDePersonalizacion = ""
        NivelDeSeguridad nivelDeSeguridad = NivelDeSeguridad::nivel128);

    private:

      /** \brief Generación de bits (adquirida por contrato). */
      Arreglo<unsigned char> generarBits(unsigned int longitud) override;

      /**
       * \brief Llave para HMAC.
       *
       * Este es un valor crítico (se debe mantener en secreto para garantizar la
       * seguridad del generador).
       */

      Arreglo<unsigned char> mLlave;
  };
}

#endif
