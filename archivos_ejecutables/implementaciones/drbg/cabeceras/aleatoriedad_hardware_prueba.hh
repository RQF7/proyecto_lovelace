/**
 * \file
 * \brief Declaración de pruebas del lector de aleatoriedad de hardware.
 *
 * Proyecto Lovelace.
 */

#ifndef __ALEATORIEDAD_HARDWARE_PRUEBA__
#define __ALEATORIEDAD_HARDWARE_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas del lector de aleatoriedad desde hardware.
   */

  class AleatoriedadHardwarePrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      AleatoriedadHardwarePrueba();

      /** \brief Prueba la operación de la fuente. */
      static bool probarOperacion();
  };
}

#endif
