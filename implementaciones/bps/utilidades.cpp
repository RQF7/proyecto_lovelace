/**
 * \file
 * \brief Implementación de la clase de Utilidades.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/utilidades.hh"

#include <iostream>
#include <iomanip>
#include <gmpxx.h>
#include <gmp.h>

using namespace std;
using namespace Implementaciones;

/* ========================================================================= */

UtilidadesBPS::UtilidadesBPS()
{
}

/* ========================================================================= */

/**
 * Esta función se encarga de sacarle el módulo al un número,
 * haciendo que siempre se retorne un valor positivo.
 */
/* Ejemplo: -7 % 4 = -3; mod(-7,4) = 1 */

int UtilidadesBPS::mod(int num, int mod)
{
  return (num % mod + mod) % mod;
}

/* ========================================================================= */

/**
 * Esta función se encarga de sacarle el módulo al un número,
 * haciendo que siempre se retorne un valor positivo.
 */
/* Ejemplo: -7 % 4 = -3; mod(-7,4) = 1 */

mpz_class UtilidadesBPS::mod(mpz_class num, mpz_class mod)
{
  return (num % mod + mod) % mod;
}

/* ========================================================================= */

/**
 * Esta función crea una cadena a partir de un número de gran tamaño,
 * siendo esta cadena una copia de los bits del número.
 */

mpz_class UtilidadesBPS::cadenaANumero(string cadena)
{
  mpz_class numero = 0;

  for (unsigned int i = 0; i < cadena.size(); i++)
  {
    numero += (unsigned char) cadena[i];
    numero  = numero << 8;
  }
  numero = numero >> 8;

  return numero;
}

/* ========================================================================= */

/**
 * Esta función crea un número de gran tamaño a partir de una cadena,
 * siendo este número una copia de los bits de la cadena.
 */

string UtilidadesBPS::numeroACadena(mpz_class numero)
{
  string cadena{""};
  string caracter{""};
  mpz_class auxiliar = 0;

  for (int i = 0; numero > 0; i++)
  {
    auxiliar  = (numero >> (8 * i)) & (0xFF);
    numero   -= auxiliar << (8 * i);
    caracter  = (unsigned char) mpz_get_ui(auxiliar.get_mpz_t());
    cadena    = caracter + cadena;
  }

  return cadena;
}
