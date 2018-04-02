/**
 * \file
 * \brief Declaración de pruebas del DRBG basado en funciones hash.
 *
 * Proyecto Lovelace.
 */

#ifndef __HASH_DRBG_PRUEBA__
#define __HASH_DRBG_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas del DRBG basado en funciones hash.
   */

  class HashDRBGPrueba
  : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      HashDRBGPrueba();

      /** \brief Prueba la operación de la fuente. */
      static bool probarFuncionDeDerivacion();
  };
}

#endif
