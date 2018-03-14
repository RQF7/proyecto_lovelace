/**
 * \file
 * \brief Prueba de la combinación por bloque.
 * Proyecto Lovelace.
 */

#ifndef __COMBINACION_POR_BLOQUE_PRUEBA__
#define __COMBINACION_POR_BLOQUE_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas do combinación por bloque.
   */

  class CombinacionPorBloquePrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      CombinacionPorBloquePrueba();

      /** \brief Prueba la suma y resta por bloque. */
      static bool probarSumaYResta();
  };
}

#endif
