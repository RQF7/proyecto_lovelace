/**
 * \file
 * \brief Definición de una función de ronda trivial.
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_DE_RONDA_TRIVIAL__
#define __FUNCION_DE_RONDA_TRIVIAL__

#include "funcion.hh"

namespace Implementaciones
{

  /**
   * \brief Definición de una función de ronda trivial.
   *
   * Implementa a la interfaz de una función y no define ninguna operación
   * virtual; por lo tanto, se trata de una clase concreta.
   */

  template <typename tipoDeVuelta, typename tipoDeIda>
  class FuncionDeRondaTrivial : public Funcion<tipoDeVuelta, tipoDeIda>
  {

    /**
     * \brief Función de ronda trivial para una red Feistel.
     *
     * Simplemente regresa una copia del primer elemento del vector de
     * entrada (en casos normales, el único).
     *
     * \note Con fines ilustrativos solamente:
     * aparte de la implementación dada, se consideran otras dos. La primera
     * recibe el arreglo por valor (no por referencia) y su cuerpo es:
     * ```
     * return Arreglo<tipo>(arreglo);
     * ```
     * La segunda también recibe el arreglo por valor, pero su cuerpo es:
     * ```
     * return Arreglo<tipo>(std::move(arreglo));
     * ```
     * El compilador efectúa una operación de copia (`O(n)`) al llamar a una
     * función con argumentos por valor y una operación de movimiento (`O(1)`)
     * al regreso de cada función. Dicho esto, podemos decir que la primera
     * versión ejecuta dos operaciones de copia, una detrás de la otra, y una
     * operación de movimiento (`O(n) + O(n) + O(1)`); la segunda versión es
     * una mejora, dado que quita una de las operaciones de copia redundantes
     * (`O(n) + O(1) + O(1)`). La versión original (la que recibe el argumento
     * por referencia), efectúa casi las mismas operaciones que la segunda
     * versión, solo que con un orden distinto y con una sintaxis más clara
     * (`O(1) + O(n) + O(1)`); en este caso la primera operación no corresponde
     * a una llamada al constructor por movimiento, sino que es el costo de la
     * creación de la referencia. En todo caso, la versión  que hay que evitar
     * a toda costa es la primera, dado que hay una copia redundante.
     *
     * \return Copia de bloque dado.
     *
     * \sa http://www.cplusplus.com/reference/utility/move/
     *
     * \todo ¿Tiene caso hacer implementación trivial con puras operaciones de
     * movimiento? Tal vez como ejercicio de C++, pero no con espera de que
     * se ocupe en algún lado.
     */

    tipoDeVuelta operar(const std::vector<tipoDeIda> &entrada) override
    {
      return tipoDeVuelta(entrada[0]);
    }
  };
}

#endif
