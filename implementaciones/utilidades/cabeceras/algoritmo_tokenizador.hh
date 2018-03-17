/**
 * \file
 * \brief Declaración de clase abstracta de algoritmo tokenizador.
 */

#ifndef __ALGORITMO_TOKENIZADDOR__
#define __ALGORITMO_TOKENIZADDOR__

#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/interfaces_comunes/funcion_con_inverso.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Estándar de interfaz para un algoritmo tokenizador.
   *
   * Un algoritmo tokenizador es cualquier cosa que implemente los dos métodos
   * puramente abstractos de esta clase. El algoritmo tokenizador es a su vez
   * una función con inverso; la implementación que se hace de operar y deoperar
   * es simplemente una construcción alrededor de cifrar y descifrar.
   */

  class AlgoritmoTokenizador
  : public Utilidades::FuncionConInverso<Arreglo<int>, Arreglo<int>>
  {
    public:

      /** \brief Operación de tokenización. */
      virtual Arreglo<int> tokenizar(
        const Arreglo<int>& pan, const Arreglo<int>& informacionAdicional) = 0;

      /** \brief Operación de detokenización. */
      virtual Arreglo<int> detokenizar(
        const Arreglo<int>& token, const Arreglo<int>& informacionAdicional) = 0;

      /** \brief Puente con operación de tokenización. */
      Arreglo<int> operar(
        const std::vector<Arreglo<int>> &entrada) override;

      /** \brief Puente con operación de detokenización. */
      Arreglo<int> deoperar(
        const std::vector<Arreglo<int>> &entrada) override;
  };
}

#endif