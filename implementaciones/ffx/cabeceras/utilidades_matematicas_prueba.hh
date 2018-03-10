/**
 * \file
 * \brief Prueba de las utilidades matemáticas.
 * Proyecto Lovelace.
 */

#ifndef __UTILIDADES_MATEMATICAS_PRUEBA__
#define __UTILIDADES_MATEMATICAS_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas de las operaciones por caracter.
   */

  class UtilidadesMatematicasPrueba : public Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      UtilidadesMatematicasPrueba();

      /** \brief Prueba la operación de potencia. */
      static bool probarPotencia();

      /** \brief Prueba la operación de módulo */
      static bool probarModulo();
  };
}

#endif
