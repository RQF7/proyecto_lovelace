/**
 * \file
 * \brief Prueba de función de ronda de FFX.
 * Proyecto Lovelace.
 */

#ifndef __RONDA_FFX_PRUEBA__
#define __RONDA_FFX_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Prueba de.
   */

  class RondaFFXPrueba : public Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      RondaFFXPrueba();

      /** \brief Prueba la operación de la función. */
      static bool probarOperacion();
  };
}

#endif
