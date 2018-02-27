/*
 * Prueba de SHA256, declaración, crypto++
 * Proyecto Lovelace
 */

#ifndef __PRUEBA_SHA256_CRYPTOPP__
#define __PRUEBA_SHA256_CRYPTOPP__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace PruebasCryptopp
{
  /*
   * \brief Prueba de la implementación SHA-256 de Crypto++
   *
   * Pequeña prueba para obtener el valor HASH de la entrada abc en SHA-256.
   * Se prueban también las constantes.
   */

  class PruebaSHA256 : public Prueba
  {
    public:
      /** \brief Prueba de constantes y funcionamiento de SHA256. */
      PruebaSHA256();

      /** \brief Prueba funcionamiento de SHA256. */
      static bool probarDigestion();
  };
}

#endif
