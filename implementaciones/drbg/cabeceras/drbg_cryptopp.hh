/**
 * \file
 * \brief Declaración de puente con generador pseudoaleatorio de cryptopp.
 *
 * Proyecto Lovelace.
 */

#ifndef __DRBG_CRYPTOPP__
#define __DRBG_CRYPTOPP__

#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <cryptopp/drbg.h>
#include <cryptopp/sha.h>
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Puete con clase de DRBG de cryptopp.
   *
   * La idea central es que implemente la misma interfaz que el generador
   * pseudoaleatorio propio. De esta manera, en donde se ocupa uno, se debe
   * también de poder ocupar el otro.
   */

  class DRBGCryptopp
  : public Utilidades::Funcion<Arreglo<unsigned char>, entero>
  {
    public:

      /** \brief Construcción de nueva instancia. */
      DRBGCryptopp();

      /** \brief Operación de generador. */
      Arreglo<unsigned char> operar(const std::vector<entero>& entrada) override;

    private:

      /** \brief Objeto encapsulado. */
      CryptoPP::Hash_DRBG<CryptoPP::SHA256, 128/8, 440/8> mDrbg;
  };
}

#endif
