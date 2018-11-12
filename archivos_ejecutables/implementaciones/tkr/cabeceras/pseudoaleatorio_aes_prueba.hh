/**
 * \file
 * \brief Declaración de pruebas con función pseudoalatoria con AES.
 *
 * Proyecto Lovelace.
 */

#ifndef __PSEUDOALEATORIO_AES_PRUEBA__
#define __PSEUDOALEATORIO_AES_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas con la función pseudoalatoria con AES.
   */

  class PseudoaleatorioAESPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      PseudoaleatorioAESPrueba();

      /** \brief Prueba la operaci{on de la función. */
      static bool probarOperacion();
  };
}

#endif
