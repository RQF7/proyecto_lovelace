/**
 * \file
 * \brief Definición de la clase de Utilidades.
 * Proyecto Lovelace.
 */

#ifndef __UTILIDADES_BPS___
#define __UTILIDADES_BPS___

#include <iostream>
#include <iomanip>
#include <gmpxx.h>
#include <gmp.h>

namespace Implementaciones
{
  class UtilidadesBPS
  {
    public:
      /** \brief Constructor de la clase. */
      UtilidadesBPS();

      /** \brief Función encargada de obtener el módulo de un entero. */
      int mod(int num, int mod);

      /** \brief Función encargada de obtener el módulo de un entero grande. */
      mpz_class mod(mpz_class num, mpz_class mod);

      /** \brief Función para obtener el número grande equivalente de una cadena. */
      mpz_class cadenaANumero(std::string cadena);

      /** \brief Función para obtener la cadena equivalente de un número grande. */
      std::string numeroACadena(mpz_class numero);

  };
}

#endif
