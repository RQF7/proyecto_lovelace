/**
 * \file
 * \brief Declaración de pruebas con función de drbg.
 *
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_DRBG_PRUEBA__
#define __FUNCION_DRBG_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * Prueba de la función DRBG.
   */

  class FuncionDRBGPrueba : public Utilidades::Prueba
  {
  public:
    /** \brief Registro de pruebas en vector de funciones. */
    FuncionDRBGPrueba();

    /** \brief Prueba de la operación de la función. */
    static bool probarOperacion();
  };
}

#endif
