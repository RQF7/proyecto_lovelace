/**
 * \file
 * \brief Prueba de la función pseudoaleatoria trivial.
 * Proyecto Lovelace.
 */

#ifndef __PSEUDOALEATORIA_TRIVIAL_PRUEBA__
#define __PSEUDOALEATORIA_TRIVIAL_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas de función pseudoaleatoria trivial.
   */

  class PseudoaleatoriaTrivialPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      PseudoaleatoriaTrivialPrueba();

      /** \brief Prueba la generación de tokens trivial. */
      static bool probarOperacion();
  };
}

#endif
