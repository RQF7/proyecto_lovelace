/**
 * \file
 * \brief Interfaz de función con operación inversa simétrica.
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_CON_INVERSO_SIMETRICO__
#define __FUNCION_CON_INVERSO_SIMETRICO__

#include "funcion_con_inverso.hh"
#include "../cabeceras/arreglo.hh"
#include <vector>

namespace Utilidades
{

  /**
   * \brief Interfaz de función inversa simétrica.
   *
   * Subclase de la interfaz función con operación inversa. Representa a las
   * operaciones cuyo inverso es la misma operación que la función de ida
   * (por ejemplo, un XOR). Los argumentos del template pasan igual a la
   * superclase.
   */

  template <typename tipoDeVuelta, typename tipoDeIda>
  class FuncionConInversoSimetrico : public
    FuncionConInverso<tipoDeVuelta, tipoDeIda>
  {
    public:

      /**
       * \brief Destructor virtual.
       *
       * Permite a los implementadores definir su propio destructor.
       */

      virtual ~FuncionConInversoSimetrico()
      {
      }

      /**
       * Implementación de la función *deoperar* definida en *FuncionConInverso*
       * (ahí es virtual). Un implementador de esta interfaz solo queda con la
       * obligación de sobreescribir a *operar* (en la raiz de la jerarquía).
       * Al intentar representar una operación simétrica, lo que esta opración
       * hace es llamar a *operar* pasándole los mismo argumentos. De esta
       * manera, un posible código tercero que utiliza a *FunciónConInverso*
       * puede basarse en la interfaz de *operar* y *deoperar* sin importarle
       * o no si dicha operación es simétrica.
       *
       * \note La palabra clave override no es obligatoria, sin embargo ayuda
       * a dejar de manera explícita en el código cuando dicha operación se
       * lleva a cabo.
       */

      tipoDeVuelta deoperar(const std::vector<tipoDeIda> &entrada)
      override
      {
        return this->operar(entrada);
      }
  };
}

#endif
