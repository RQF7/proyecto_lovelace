/**
 * \file
 * \brief Declaración de pruebas de TKR2.
 *
 * Proyecto Lovelace.
 */

#ifndef __AHR_PRUEBA__
#define __AHR_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas de AHR.
   */

  class AHRPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      AHRPrueba();

      /** \brief Prueba la operación con base de datos. */
      static bool probarOperacion();
  };
}

#endif
