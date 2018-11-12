/**
 * \file
 * \brief Prueba de función de ronda de FFX.
 * Proyecto Lovelace.
 */

#ifndef __RONDA_FFX_A10_PRUEBA__
#define __RONDA_FFX_A10_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Prueba de la función de ronda de FFX A10.
   */

  class RondaFFXA10Prueba : public Utilidades::Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      RondaFFXA10Prueba();

      /** \brief Prueba la operación de la función. */
      static bool probarOperacion();
  };
}

#endif
