/**
 * \file
 * \brief Prueba de FFX.
 * Proyecto Lovelace.
 */

#ifndef __FFX_PRUEBA__
#define __FFX_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Prueba de la clase de FFX.
   *
   * Pruebas de funcionalidades de la clase de FFX.
   */

  class FFXPrueba : public Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      FFXPrueba();

      /** \brief Prueba el funcionamiento de las funciones de suma y resta. */
      static bool probarFuncionesDeSuma();

      /** \brief Prueba la función de ronda. */
      static bool probarFuncionDeRonda();
  };
}

#endif
