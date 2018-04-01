/**
 * \file
 * \brief Decaración de un DRGB basado en una función hash.
 *
 * Proyecto Lovelace.
 */

#ifndef __HASH_DRGB__
#define __HASH_DRGB__

#include "drgb.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

namespace Implementaciones
{
  /**
   * \brief
   *
   */

  class HashDRGB : public DRGB
  {
    public:

      /** \brief Tipos de funciones hash disponibles. */
      enum class FuncionHash {
        SHA1   = 160,
        SHA224 = 224,
        SHA256 = 256,
        SHA384 = 384,
        SHA512 = 512
      };

      /** \brief Construcción de un generador basado en una fucnión hash. */
      HashDRGB(FuenteDeAleatoriedad fuenteDeAlatoriedad,
        string cadenaDePersonalizacion = ""
        NivelDeSeguridad nivelDeSeguridad = NivelDeSeguridad::nivel128,
        FuncionHash funcionHash = FuncionHash::SHA256);

    private:

      /** \brief Generación de bits (adquirida por contrato). */
      Arreglo<unsigned char> generarBits(unsigned int longitud) override;

      /**
       * \brief Constante que depende de semilla (C).
       *
       * Al igual que la semilla (un miembro de la superclase) este valor también es
       * crítico: la seguridad de la implementación depende de que se mantenga en
       * secreto.
       */

      Arreglo<unsigned char> mConstanteSemilla;

      /** \brief Tipo de función hash usada. */
      FuncionHash mFuncionHash;
  };
}

#endif
