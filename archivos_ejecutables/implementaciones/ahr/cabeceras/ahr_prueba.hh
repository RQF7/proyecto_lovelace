/**
 * \file
 * \brief Declaración de pruebas de AHR.
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

      /** \brief Prueba la operación del algoritmo AHR. */
      static bool probarOperacion();
  };
}

#endif
