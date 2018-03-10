/**
 * \file
 * \brief Definición de una función de combinación trivial.
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_DE_COMBINACION_TRIVIAL__
#define __FUNCION_DE_COMBINACION_TRIVIAL__

#include "../../../utilidades/interfaces_comunes/funcion_con_inverso_simetrico.hh"

namespace Implementaciones
{
  /**
   * \brief Definición de una función de combinación trivial.
   *
   * Implementa a la interfaz de una función con inverso simétrico y no define
   * ninguna operación virtual; por lo tanto, se trata de una clase concreta.
   */

  template <typename tipoDeVuelta, typename tipoDeIda>
  class FuncionDeCombinacionTrivial : public
    Utilidades::FuncionConInversoSimetrico<tipoDeVuelta, tipoDeIda>
  {
   /**
    * \brief Operación de combinación trivial.
    *
    * Regresa el primer elemento del vector del argumento de entrada; en
    + casos normales, este vector tiene dos elementos (los dos operandos).
    *
    * El primer bloque es el del lado izquierdo, mientras que el segundo
    * bloque es la salida de la función de ronda. Al regresar solo el primer
    * bloque, se busca que, en una red con funciones de ronda y de
    * combinaciones triviales, la salida sea el mismo bloque (si el número de
    * rondas es par), o el bloque de entrada invertido (si el número de rondas
    * es impar).
    *
    * \return Copia del primer bloque.
    */

    tipoDeVuelta operar(const std::vector<tipoDeIda> &entrada) override
    {
      return tipoDeVuelta(entrada[0]);
    }
  };
}

#endif
