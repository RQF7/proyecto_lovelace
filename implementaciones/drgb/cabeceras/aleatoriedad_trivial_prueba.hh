/**
 * \file
 * \brief Declaración de pruebas del lector de aleatoriedad de archivo.
 *
 * Proyecto Lovelace.
 */

#ifndef __ALEATORIEDAD_TRIVIAL_PRUEBA__
#define __ALEATORIEDAD_TRIVIAL_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas del lector de aleatoriedad de archivo.
   */

  class AleatoriedadTrivialPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      AleatoriedadTrivialPrueba();

      /** \brief Prueba la operación de la fuente. */
      static bool probarOperacion();
  };
}

#endif
