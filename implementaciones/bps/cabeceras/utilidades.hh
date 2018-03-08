/* ========================================================================= */
/* ============================== Utilidades =============================== */
/* ======================================================================daz */

/**
 * Proyecto Lovelace.
 * 
 * \file
 * \brief Definición de la clase de Utilidades.
 * 
 */

#ifndef UTILIDADES_H_
#define UTILIDADES_H_

#include <iostream>
#include <iomanip>
#include <gmpxx.h>
#include <gmp.h>

/* ========================================================================= */

class Utilidades{

public:
  /** \brief Constructor de la clase. */
  Utilidades();

  /** \brief Función encargada de obtener el modulo de un entero. */
  int mod(int num, int mod);

  /** \brief Función encargada de obtener el modulo de un entero grande. */
  mpz_class mod(mpz_class num, mpz_class mod);

  /** \brief Función para obtener el numero grande equivalente de una cadena. */
  mpz_class stringToNum(std::string cadena);

  /** \brief Función para obtener la cadena equivalente de un numero grande. */
  std::string numToString(mpz_class numero);

};

/* ========================================================================= */

#endif
