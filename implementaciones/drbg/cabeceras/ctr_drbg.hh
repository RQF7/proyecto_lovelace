
/**
 * \file
 * \brief Decaración de un DRBG basado en cifrador por bloques.
 *
 * Proyecto Lovelace.
 */

#ifndef __CTR_DRBG__
#define __CTR_DRBG__

#include "drbg.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

namespace Implementaciones
{
  /**
   * \brief Generador pseudoaleatorio basado en cifrador por bloques.
   *
   * Implementación del generados psudoaleatorio basado en cifrador por bloques
   * presentado en NIST 800-90A, sección 10.2. Cada instancia de esta clase
   * puede ocupar una versión de AES distinta:
   *
   * * AES128
   * * AES192
   * * AES256
   */

  class CTRDRBG : public DRBG
  {
    public:

      /** \brief Tipos de cifrador por bloque disponibles. */
      enum class TipoDeCifrador : unsigned int {
        AES128 = 16u,
        AES192 = 24u,
        AES256 = 32u
      };

      /** \brief Construcción de un generador basado en un cifrador por bloque. */
      CTRDRBG(FuenteDeAleatoriedad *fuenteDeAlatoriedad,
        Arreglo<unsigned char> cadenaDePersonalizacion,
        NivelDeSeguridad nivelDeSeguridad = NivelDeSeguridad::nivel128,
        TipoDeCifrador tipoDeCifrador = TipoDeCifrador::AES128);

      /** \brief Función de cambio de semilla. */
      void cambiarSemilla() override;

      /** \brief Función para eliminar información crítica. */
      void desinstanciar() override;

    private:

      /** \brief Generación de bits (adquirida por contrato). */
      Arreglo<unsigned char> generarBytes(entero longitud) override;

      /** \brief Función de actualización. */
      void actualizarEstado(const Arreglo<unsigned char>& entrada);

      /** \brief Envoltura alrededor del cifrador por bloque. */
      Arreglo<unsigned char> cifrarBloque(const Arreglo<unsigned char>& bloque);

      /** \brief Tipo de cifrador por bloques interno. */
      TipoDeCifrador mTipoDeCifrador;

      /** \brief Longitud de la llave interna. */
      unsigned int mLongitudLlave;

      /** \breif Longitud de bloque. */
      unsigned int mLongitudBloque;

      /** \brief Longitud de contador. */
      unsigned int mLongitudContador;

      /**
       * \brief Llave para cifrador por bloques.
       *
       * Este es un valor crítico (se debe mantener en secreto para garantizar
       * la seguridad del generador).
       */

      Arreglo<unsigned char> mLlave;
  };
}

#endif
