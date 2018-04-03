/**
 * \file
 * \brief Decaración de un DRBG basado en una función hash.
 *
 * Proyecto Lovelace.
 */

#ifndef __HASH_DRBG__
#define __HASH_DRBG__

#include "aleatoriedad_trivial.hh"
#include "drbg.hh"
#include "hash_drbg_prueba.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"
#include <cryptopp/cryptlib.h>

namespace Implementaciones
{
  /**
   * \brief
   *
   */

  class HashDRBG : public DRBG
  {
    public:

      /** \brief Tipos de funciones hash disponibles. */
      enum class TipoDeFuncionHash {
        SHA1   = 160,
        SHA224 = 224,
        SHA256 = 256,
        SHA384 = 384,
        SHA512 = 512
      };

      /** \brief Construcción de un generador basado en una función hash. */
      HashDRBG(FuenteDeAleatoriedad *fuenteDeAlatoriedad,
        Arreglo<unsigned char> cadenaDePersonalizacion,
        NivelDeSeguridad nivelDeSeguridad = NivelDeSeguridad::nivel128,
        TipoDeFuncionHash tipoDeFuncionHash = TipoDeFuncionHash::SHA256);

      /** \brief Destructor de generador. */
      ~HashDRBG();

      /** \brief Función de cambio de semilla. */
      void cambiarSemilla() override;

      /** \brief Función para eliminar información crítica. */
      void desinstanciar() override;

    private:

      /** \brief Generación de bits (adquirida por contrato). */
      Arreglo<unsigned char> generarBytes(unsigned int longitud) override;

      /** \brief Función de derivación. */
      Arreglo<unsigned char> funcionDeDerivacion(
        const Arreglo<unsigned char>& cadenaDeEntrada,
        unsigned int longitudDeSalida);

      /** \brief Función de generación. */
      Arreglo<unsigned char> funcionDeGeneracion(unsigned int longitudDeSalida);

      /** \brief Interfaz con función hash de cryptopp. */
      Arreglo<unsigned char> hash(const Arreglo<unsigned char>& entrada);

      /**
       * \brief Constante que depende de semilla (C).
       *
       * Al igual que la semilla (un miembro de la superclase) este valor
       * también es crítico: la seguridad de la implementación depende de que
       * se mantenga en secreto.
       */

      Arreglo<unsigned char> mConstanteSemilla;

      /** \brief Tipo de función hash usada. */
      TipoDeFuncionHash mTipoDeFuncionHash;

      /** \brief Función hash de cryptopp. */
      CryptoPP::HashTransformation *mFuncionHash;

      /** \brief Clase de prueba como amiga. */
      friend class ImplementacionesPruebas::HashDRBGPrueba;
  };
}

#endif
