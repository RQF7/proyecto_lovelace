/**
 * \file
 * \brief Declaración de pruebas con función RN.
 *
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_RN_PRUEBA__
#define __FUNCION_RN_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas con la función RN.
   */

  class FuncionRNPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      FuncionRNPrueba();

      /** \brief Prueba de la operación de redistribución. */
      static bool probarRedistribucion();

      /** \brief Prueba la operación de la función. */
      static bool probarOperacion();
  };
}

#endif
