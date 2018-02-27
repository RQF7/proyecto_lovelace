/**
 * \file
 * \brief Prueba de AES, declaración, crypto++
 * Proyecto Lovelace.
 */

#ifndef __PRUEBA_AES_CRYPTOPP__
#define __PRUEBA_AES_CRYPTOPP__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace PruebasCryptopp
{
  /**
   * \brief Prueba de la impementación de AES de cryptopp.
   *
   * Agrupa las funciones de prueba que interactúan con la implementación
   * de AES de cryptopp.
   */

  class PruebaAES : public Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      PruebaAES();

      /** \brief Prueba el funcionamiento de constantes de AES. */
      static bool probarConstantes();

      /** \brief Prueba el proceso de cifrado y descifrado de AES. */
      static bool probarCifradoDescifrado();
  };
}

#endif
