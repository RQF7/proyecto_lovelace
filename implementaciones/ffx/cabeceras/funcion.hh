/**
 * \file
 * \brief Interfaz de función.
 * Proyecto Lovelace.
 */

#ifndef __FUNCION__
#define __FUNCION__

#include "arreglo.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Interfaz de función.
   *
   * Define una clase totalmente virtual (una interfaz) para definir cualquier
   * proceso (función); los tipos de los argumentos de entrada y de salida son
   * genéricos (definidos en el template). La entrada es un contenedor: de esta
   * manera es la implementación (las clases concretas) las que definen cuántos
   * argumentos reciben. Por ejemplo, ambas funciones en una red Feistel son
   * clases concretas derivadas de esta interfaz: la función de ronda solamente
   * opera con un argumento, mientras que la función de combinación recibe dos
   * argumentos.
   *
   * \todo Usar Arreglo en lugar de vector para la entrada.
   */

  template <typename tipoDeVuelta, typename tipoDeIda>
  class Funcion
  {
    public:

      /**
       * \brief Destructor virtual.
       *
       * Permite a los implementadores definir su propio destructor.
       */

      virtual ~Funcion()
      {
      }

      /**
       * \brief Representación abstracta de proceso.
       *
       * Firma de función virtual que las subclases no pueden ignorar: si la
       * definen se convierten en clases concretas (su definición forma parte
       * de su implementación), y si no la definen, son clases abstractas
       * (no pueden existir objetos de esa clase; para esto tiene que haber una
       * concreta hasta abajo).
       */

      virtual tipoDeVuelta operar(
        const std::vector<tipoDeIda> &entrada) = 0;
  };
}

#endif
