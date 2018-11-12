/**
 * \file
 * \brief Interfaz de función con operación inversa.
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_CON_INVERSO__
#define __FUNCION_CON_INVERSO__

#include "funcion.hh"
#include "../cabeceras/arreglo.hh"
#include <vector>

namespace Utilidades
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
       * \brief Destructor virtual.
       *
       * Permite a los implementadores definir su propio destructor.
       */

      virtual ~FuncionConInverso()
      {
      }

      /**
       * \brief Función inversa para una operación.
       *
       * Al ser subclase de una interfaz con un método puramente virtual y no
       * proveer de una implementación, esta clase también es puramente virtual
       * (otra interfaz). De esta forma, los implementadores de esta clase no
       * solo adquieren la obligación de dar una implementación para *deoperar*,
       * sino que también para *operar*.
       */

      virtual tipoDeIda deoperar(
        const std::vector<tipoDeVuelta> &entrada) = 0;
  };
}

#endif
