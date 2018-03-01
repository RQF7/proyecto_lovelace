/**
 * \file
 * \brief Prueba de red Feistel alternante.
 * Proyecto Lovelace.
 */

#ifndef __RED_FEISTEL_ALTERNANTE_PRUEBA__
#define __RED_FEISTEL_ALTERNANTE_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Prueba de la clase de red Feistel alternante.
   *
   * Pruebas de funcionalidades de las redes Feistel alternantes.
   */

  class RedFeistelAlternantePrueba : public Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      RedFeistelAlternantePrueba();

      /** \brief Prueba el funcionamiento básico de la clase. */
      static bool probarCifradoDescifrado();
  };
}

#endif
