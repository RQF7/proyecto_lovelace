/**
 * \file
 * \brief Declaración de pruebas de TKR2.
 *
 * Proyecto Lovelace.
 */

#ifndef __TKR_PRUEBA__
#define __TKR_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas de TKR.
   */

  class TKRPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      TKRPrueba();

      /** \brief Prueba la operación con miembros triviales. */
      static bool probarOperacionTrivial();

      /** \brief Prueba la operación con la función RN. */
      static bool probarOperacionNoTanTrivial();
  };
}

#endif
