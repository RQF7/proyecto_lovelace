/**
 * \file
 * \brief Declaración de prueba de puente con cryptopp.
 *
 * Proyecto Lovelace.
 */

#ifndef __DRBG_CRYPTOPP_PRUEBA__
#define __DRBG_CRYPTOPP_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Prueba el puente con el DRBG de cryptopp
   */

  class DRBGCryptoppPrueba
  : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      DRBGCryptoppPrueba();

      /** \brief Prueba de generador. */
      static bool probarOperacion();
  };
}

#endif
