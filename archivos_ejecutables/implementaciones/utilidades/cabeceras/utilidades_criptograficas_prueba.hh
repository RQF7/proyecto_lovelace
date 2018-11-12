/**
 * \file
 * \brief Declaración de pruebas de las utilidades de tarjetas.
 */

#ifndef __UTILIDADES_CRIPTOGRAFICAS_PRUEBA__
#define __UTILIDADES_CRIPTOGRAFICAS_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas de utilidades de tarjetas.
   */

  class UtilidadesCriptograficasPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro en vector de pruebas. */
      UtilidadesCriptograficasPrueba();

      /** \brief Prueba de la generación pseudoaleatoria de llaves. */
      static bool probarGeneracionDeLlaves();
  };
}

#endif
