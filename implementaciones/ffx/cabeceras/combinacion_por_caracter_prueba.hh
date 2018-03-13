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
   * \brief Pruebas de las operaciones por caracter.
   */

  class CombinacionPorCaracterPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      CombinacionPorCaracterPrueba();

      /** \brief Prueba la suma y resta por caracter. */
      static bool probarSumaYResta();
  };
}

#endif
