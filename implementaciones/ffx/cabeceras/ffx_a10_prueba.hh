/**
 * \file
 * \brief Prueba de FFX.
 * Proyecto Lovelace.
 */

#ifndef __FFX_A10_PRUEBA__
#define __FFX_A10_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Prueba de la clase de FFX.
   *
   * Pruebas de funcionalidades de la clase de FFX.
   */

  class FFXA10Prueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      FFXA10Prueba();

      /** \brief  */
      static bool probarCifradoDescifrado();
  };
}

#endif
