/**
 * \file
 * \brief Prueba de CBC MAC, declaración, crypto++
 * Proyecto Lovelace.
 */

#ifndef __PRUEBA_CBC_MAC_CRYPTOPP__
#define __PRUEBA_CBC_MAC_CRYPTOPP__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace PruebasCryptopp
{
  /**
   * \brief Prueba de la implementación de CBC MAC de cryptopp.
   */

  class PruebaCBCMAC : public Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      PruebaCBCMAC();

      /** \brief Prueba el proceso de cifrado y descifrado de CBC MAC. */
      static bool probarCifrado();
  };
}

#endif