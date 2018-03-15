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

/**
 * Envolvente alrededor de la función de módulo normal para lidiar con
 * números negativos: si el primer operando es negativo, se regresa el
 * módulo del complemento.
 *
 * \return numeroUno % numeroDos
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
 */

template <typename tipo>
tipo potencia(int base, int exponente)
{
  tipo resultado {1};
  for (int i = 0; i < exponente; i++)
    resultado *= base;
  return resultado;
}

#endif
