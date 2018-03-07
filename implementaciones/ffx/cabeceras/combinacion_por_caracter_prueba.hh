/**
 * \file
 * \brief Prueba de la combinación por caracter.
 * Proyecto Lovelace.
 */

#ifndef __COMBINACION_POR_CARCATER_PRUEBA__
#define __COMBINACION_POR_CARCATER_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief
   */

  class CombinacionPorCaracterPrueba : public Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      CombinacionPorCaracterPrueba();

      /** \brief Prueba la suma y resta por caracter. */
      static bool probarSumaYResta();
  };
}

#endif
