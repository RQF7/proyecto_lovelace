/**
 * \file
 * \brief Declaración y definición de funciones matemáticas comunes.
 *
 * En la mayoría de los casos el tipo de los operadores es un template, por lo
 * que la implementación se encuentra junto a la declaración.
 * Proyecto Lovelace.
 */

#ifndef __UTILIDADES_MATEMATICAS__
#define __UTILIDADES_MATEMATICAS__

#include <iostream>

/** \brief Alias para entero de 8 bytes. */
using entero = unsigned long long int;

/** \brief Alias para entero de 8 bytes con signo. */
using enteroConSigno = long long int;

/** \brief Operación de módulo. */
template <typename tipo>
tipo modulo(tipo numeroUno, tipo numeroDos);

/** \brief Operación de potencia. */
template <typename tipo>
tipo potencia(int base, int exponente);

/** \brief Cuenta el número de dígitos del número dado. */
template <typename tipo>
int contarDigitos(tipo numero, int base);

/** \brief Regresa el valor absoluto del número dado. */
template <typename tipo>
tipo valorAbsoluto(tipo numero);

/**
 * Envolvente alrededor de la función de módulo normal para lidiar con
 * números negativos: si el primer operando es negativo, se regresa el
 * módulo del complemento.
 *
 * \return numeroUno % numeroDos
 *
 * \tparam tipo Tipo de operandos.
 */

template <typename tipo>
tipo modulo(
  tipo numeroUno,                        /**< Primer operando. */
  tipo numeroDos                         /**< Segundo operando. */
)
{
  return (numeroUno >= 0)
    ? numeroUno % numeroDos
    : numeroDos - ((numeroUno * -1) % numeroDos);
}

/**
 * Efectúa una operación de potencia. El template permite especificar
 * el tipo de datos con el que se opera.
 *
 * \return operación de potencia.
 *
 * \tparam tipo Tipo de resultado.
 */

template <typename tipo>
tipo potencia(
  int base,                              /**< Base de la operación. */
  int exponente                          /**< Exponente de la operación. */
)
{
  tipo resultado {1};
  for (int i = 0; i < exponente; i++)
    resultado *= base;
  return resultado;
}

/**
 * Cuenta los dígitos del número dado en la base dada.
 *
 * \return Número de dígitos.
 *
 * \tparam tipo Tipo del número dado.
 */

template <typename tipo>
int contarDigitos(
  tipo numero,                           /**< Número a analizar. */
  int base                               /**< Base de número dado. */
)
{
  int resultado {1};
  while ((numero /= base) != 0)
    resultado++;
  return resultado;
}

/**
 * Calcula el valor absoluto del número dado.
 *
 * \return Valor absoluto de entrada.
 *
 * \tparam tipo Tipo del número dado.
 */

template <typename tipo>
tipo valorAbsoluto(
  tipo numero                            /**< Número de entrada. */
)
{
  if (numero >= 0)
    return numero;
  else
    return numero * -1;
}

#endif
