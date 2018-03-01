/**
 * \file
 * \brief Prueba de contenedor de arreglo.
 * Proyecto Lovelace.
 */

#ifndef __ARREGLO_PRUEBA__
#define __ARREGLO_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Prueba del contenedor tipo arreglo.
   *
   * Pruebas de funcionalidades del contenedor tipo arreglo.
   */

  class ArregloPrueba : public Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      ArregloPrueba();

      /** \brief Prueba el funcionamiento básico de la clase. */
      static bool probarFuncionalidadBasica();

      /** \brief Prueba la función de partición. */
      static bool probarParticiones();

      /** \brief Prueba de operación de concatenación. */
      static bool probarConcatenacion();

      /** \brief Prueba la operación de los constructores. */
      static bool probarConstructores();

      /** \brief Prueba los operadores de comparación. */
      static bool probarOperadoresComparacion();

      /** \brief Prueba las conversiones numéricas. */
      static bool probarConversionesNumericas();
  };
}

#endif
