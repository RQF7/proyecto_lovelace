/**
 * \file
 * \brief Declaración de pruebas de las utilidades de tarjetas.
 */

#ifndef __UTILIDADES_TARJETAS_PRUEBA__
#define __UTILIDADES_TARJETAS_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas de utilidades de tarjetas.
   */

  class UtilidadesTarjetasPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro en vector de pruebas. */
      UtilidadesTarjetasPrueba();

      /** \brief Prueba del algoritmo de Luhn. */
      static bool probarAlgoritmoDeLuhn();
  };
}

#endif
