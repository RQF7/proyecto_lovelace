
/**
 * \file
 * \brief Decaración de un DRGB basado en cifrador por bloques.
 *
 * Proyecto Lovelace.
 */

#ifndef __CTR_DRGB__
#define __CTR_DRGB__

#include "drgb.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

namespace Implementaciones
{
  /**
   * \brief
   *
   */

  class CTRDRGB : public DRGB
  {
    public:

      /** \brief Construcción de un generador basado en una fucnión hash. */
      CTRDRGB(FuenteDeAleatoriedad fuenteDeAlatoriedad,
        string cadenaDePersonalizacion = ""
        NivelDeSeguridad nivelDeSeguridad = NivelDeSeguridad::nivel128);

    private:

      /** \brief Generación de bits (adquirida por contrato). */
      Arreglo<unsigned char> generarBits(unsigned int longitud) override;

      /**
       * \brief Llave para cifrador por bloques.
       *
       * Este es un valor crítico (se debe mantener en secreto para garantizar la
       * seguridad del generador).
       */

      Arreglo<unsigned char> mLlave;
  };
}

#endif
