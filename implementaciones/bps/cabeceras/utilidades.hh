/**
 * \file
 * \brief Definición de la clase de Utilidades.
 * Proyecto Lovelace.
 */

#ifndef __UTILIDADES___
#define __UTILIDADES___

#include <iostream>
#include <iomanip>
#include <gmpxx.h>
#include <gmp.h>

class Utilidades
{
  public:
    /** \brief Constructor de la clase. */
    Utilidades();

    /** \brief Función encargada de obtener el módulo de un entero. */
    int mod(int num, int mod);

    /** \brief Función encargada de obtener el módulo de un entero grande. */
    mpz_class mod(mpz_class num, mpz_class mod);

    /** \brief Función para obtener el número grande equivalente de una cadena. */
    mpz_class cadenaANumero(std::string cadena);

    /** \brief Función para obtener la cadena equivalente de un número grande. */
    std::string numeroACadena(mpz_class numero);

};

#endif
