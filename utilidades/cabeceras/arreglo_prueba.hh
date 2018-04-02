/**
 * \file
 * \brief Prueba de contenedor de arreglo.
 * Proyecto Lovelace.
 */

#ifndef __ARREGLO_PRUEBA__
#define __ARREGLO_PRUEBA__

#include "prueba.hh"

namespace UtilidadesPruebas
{
  /**
   * \brief Prueba del contenedor tipo arreglo.
   *
   * Pruebas de funcionalidades del contenedor tipo arreglo.
   */

  class ArregloPrueba : public Utilidades::Prueba
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

      /** \brief Prueba el control de acceso. */
      static bool probarControlDeAcceso();

      /** \brief Prueba la división entre arreglo. */
      static bool probarDivisionEntreArreglo();

      /** \brief Prueba la suma entre arreglos de bytes. */
      static bool probarSuma();
  };
}

#endif
