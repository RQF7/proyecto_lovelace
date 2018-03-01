/**
 * \file
 * \brief Prueba de red Feistel desbalanceada.
 * Proyecto Lovelace.
 */

#ifndef __RED_FEISTEL_DESBALANCEADA_PRUEBA__
#define __RED_FEISTEL_DESBALANCEADA_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Prueba de la clase de red Feistel desbalanceada.
   *
   * Pruebas de funcionalidades de las redes Feistel desbalanceadas.
   */

  class RedFeistelDesbalanceadaPrueba : public Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      RedFeistelDesbalanceadaPrueba();

      /** \brief Prueba el funcionamiento básico de la clase. */
      static bool probarCifradoDescifrado();
  };
}

#endif
