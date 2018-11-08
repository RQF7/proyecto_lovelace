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
   * \brief Generador pseudoaleatorio basado en función hash.
   *
   * Implementación del generados psudoaleatorio basado en funciones hash
   * presentado en NIST 800-90A, sección 10.1. Cada instancia de esta clase
   * puede ocupar una función hash distinta de entre 5 posibilidades:
   *
   * * SHA1
   * * SHA224
   * * SHA256
   * * SHA384
   * * SHA512
   *
   * Para cada operación de las definidas por un DRGB (instanciación, cambio de
   * semilla, desinstanciación) primero se llama a la operación equivalente en
   * la superclase (un DRBG genérico) y después se define un comportamiento
   * propio. La excepción a esto es la función de generación de bits: esta es
   * pública en la superclase; desde ahí se llama a generarBytes, definida
   * solamente por los implementadores.
   *
   * \sa DRBG
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
      HashDRBG(Arreglo<unsigned char> cadenaDePersonalizacion,
        NivelDeSeguridad nivelDeSeguridad = NivelDeSeguridad::nivel128,
        TipoDeFuncionHash tipoDeFuncionHash = TipoDeFuncionHash::SHA256,
        FuenteDeAleatoriedad *fuenteDeAlatoriedad = nullptr);

      /** \brief Destructor de generador. */
      ~HashDRBG();

      /** \brief Función de cambio de semilla. */
      void cambiarSemilla() override;

      /** \brief Función para eliminar información crítica. */
      void desinstanciar() override;

    private:

      /** \brief Generación de bits (adquirida por contrato). */
      Arreglo<unsigned char> generarBytes(entero longitud) override;

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
