/**
 * \file
 * \brief Interfaz de función con operación inversa.
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_CON_INVERSO__
#define __FUNCION_CON_INVERSO__

#include "arreglo.hh"
#include "funcion.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Interfaz de función inversa.
   *
   * Subclase de la interfaz función que agrega a la lista de funciones
   * totalmente virtuales una operación inversa. Los argumentos del template
   * son los mismos para ambas interfaces.
   */

  template <typename tipoDeVuelta, typename tipoDeIda>
  class FuncionConInverso : public Funcion<tipoDeVuelta, tipoDeIda>
  {
    public:

      /**
       * \brief Función inversa para una operación.
       *
       * Al ser subclase de una interfaz con un método puramente virtual y no
       * proveer de una implementación, esta clase también es puramente virtual
       * (otra interfaz). De esta forma, los implementadores de esta clase no
       * solo adquieren la obligación de dar una implementación para *deoperar*,
       * sino que también para *operar*.
       */

      virtual tipoDeVuelta deoperar(
        const std::vector<tipoDeIda> &entrada) = 0;
  };
}

#endif
