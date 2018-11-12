/**
 * \file
 * \brief Prueba de red Feistel balanceada.
 * Proyecto Lovelace.
 */

#ifndef __RED_FEISTEL_PRUEBA__
#define __RED_FEISTEL_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Prueba de la clase de red Feistel.
   *
   * Pruebas de funcionalidades de las redes Feistel.
   */

  class RedFeistelPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      RedFeistelPrueba();

      /** \brief Prueba el funcionamiento básico de la clase. */
      static bool probarCifradoDescifrado();

      /** \brief Construcción de una metared Feistel. */
      static bool metaRedFeistel();
  };
}

#endif
