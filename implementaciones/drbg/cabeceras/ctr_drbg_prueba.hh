/**
 * \file
 * \brief Declaración de pruebas del DRBG basado en cifrador por bloque.
 *
 * Proyecto Lovelace.
 */

#ifndef __CTR_DRBG_PRUEBA__
#define __CTR_DRBG_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas del DRBG basado en funciones hash.
   */

  class CTRDRBGPrueba
  : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      CTRDRBGPrueba();

      /** \brief Prueba la operación normal del generador. */
      static bool probarFuncionDeGeneracion();
  };
}

#endif
