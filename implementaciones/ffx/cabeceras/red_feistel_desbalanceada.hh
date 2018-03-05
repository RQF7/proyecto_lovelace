/**
 * \file
 * \brief Declaración de una red Feistel desbalanceada.
 *
 * Proyecto Lovelace.
 */

#ifndef __RED_FEISTEL_DESBALANCEADA__
#define __RED_FEISTEL_DESBALANCEADA__

#include "red_feistel.hh"

namespace Implementaciones
{
  /**
   * \brief Implementación de una red Feistel desbalanceada.
   *
   * En cuestión de datos miembro, solamente se agrega el grado de
   * desbalanceo. Se sobrescriben las operaciones de cifrado y descifrado
   * de una red balanceada.
   *
   * \todo ¿Cuál es la forma más rápida de hacer la repartición, en las
   * operaciones de cifrado y descifrado?
   *
   * \tparam tipo Tipo con el que opera la red.
   */

  template <typename tipo>
  class RedFeistelDesbalanceada : public RedFeistel<tipo>
  {
    public:

      /** \brief Definición de función de ronda en super clase. */
      using FuncionDeRonda =
        typename RedFeistel<tipo>::FuncionDeRonda;

        /** \brief Definición de función de combinación en super clase. */
      using FuncionDeCombinacion =
        typename RedFeistel<tipo>::FuncionDeCombinacion;

      /** \brief Construcción de red Feistel desbalanceada. */
      RedFeistelDesbalanceada(int numeroDeRondas,
        int tamanioDeBloque, int desbalanceo = 0,
        FuncionDeRonda& funcionDeRonda =
          RedFeistel<tipo>::funcionDeRondaPorDefecto,
        FuncionDeCombinacion& operadorSuma =
          RedFeistel<tipo>::funcionDeCombinacionPorDefecto);

      /** \brief Operación de cifrado de la red. */
      Arreglo<tipo> operar(
        const std::vector<Arreglo<tipo>>& textoEnClaro) override;

      /** \brief Operación de descifrado de la red. */
      Arreglo<tipo> deoperar(
        const std::vector<Arreglo<tipo>>& textoEnClaro) override;

    private:

      /** \brief Grado de desbalanceo de la red. */
      int mDesbalanceo;

      /** \brief Referencia a número de rondas de la red. */
      using RedFeistel<tipo>::mNumeroDeRondas;

      /** \brief Referencia a tamaño de los bloques. */
      using RedFeistel<tipo>::mTamanioDeBloque;

      /** \brief Referencia a función de ronda; usado para pares */
      using RedFeistel<tipo>::mFuncionDeRonda;

      /** \brief Referencia a operación de combinación. */
      using RedFeistel<tipo>::mOperadorSuma;

      /** \brief Referencia a ronda actual. */
      using RedFeistel<tipo>::mRondaActual;
  };

  /**
   * Casi todos los parámetros se pasan a la superclase; el único propio a
   * esta clase es el desbalanceo.
   *
   * \todo Lanzar excepción cuando el desbalanceo no concuerde con el tamaño
   * de bloque.
   */

  template <typename tipo>
  RedFeistelDesbalanceada<tipo>::RedFeistelDesbalanceada(
    /** Número de rondas. */
    int numeroDeRondas,
    /** Tamaño de bloque (entrada, salida). */
    int tamanioDeBloque,
    /** Grado de desbalanceo de la red; por defecto 0. */
    int desbalanceo,
    /** Función de ronda par; por defecto implementación trivial. */
    FuncionDeRonda& funcionDeRonda,
    /** Función para combinar bloques; por defecto implementación trivial. */
    FuncionDeCombinacion& operadorSuma
  )
  : RedFeistel<tipo> {numeroDeRondas, tamanioDeBloque,
      funcionDeRonda, operadorSuma},
    mDesbalanceo {desbalanceo}
  {
  }

  /**
   * Realiza todas las rondas del proceso de cifrado.
   *
   * \return Bloque cifrado.
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistelDesbalanceada<tipo>::operar (
    const std::vector<Arreglo<tipo>>& textoEnClaro      /**< Bloque a cifrar. */
  )
  {
    Arreglo<tipo> temporal = std::move(textoEnClaro[0]);
    Arreglo<tipo> parteDerecha, parteIzquierda, auxiliar;
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      /* Partición */
      parteIzquierda = std::move(temporal.partir(2, 0, mDesbalanceo));
      parteDerecha = std::move(temporal.partir(2, 1, mDesbalanceo));

      /* Operación normal */
      auxiliar = std::move(parteDerecha);
      parteDerecha = std::move(mOperadorSuma.operar(
        {parteIzquierda, mFuncionDeRonda.operar({auxiliar})}));
      parteIzquierda = std::move(auxiliar);

      temporal = std::move(parteIzquierda + parteDerecha);
    }
    return temporal;
  }

  /**
   * Realiza todas las rondas del proceso de descifrado.
   *
   * \return Bloque descifrado.
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistelDesbalanceada<tipo>::deoperar (
    const std::vector<Arreglo<tipo>>& textoCifrado   /**< Bloque a descifrar. */
  )
  {
    int desbalanceoInverso = (mTamanioDeBloque % 2 == 0)
      ? mDesbalanceo * -1
      : (mDesbalanceo * -1) + 1;
    Arreglo<tipo> temporal = std::move(textoCifrado[0]);
    Arreglo<tipo> parteDerecha, parteIzquierda, auxiliar;
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      /* Partición */
      parteIzquierda = std::move(temporal.partir(2, 0, desbalanceoInverso));
      parteDerecha = std::move(temporal.partir(2, 1, desbalanceoInverso));

      /* Operación normal */
      auxiliar = std::move(parteIzquierda);
      parteIzquierda = std::move(mOperadorSuma.deoperar(
        {parteDerecha, mFuncionDeRonda.operar({auxiliar})}));
      parteDerecha = std::move(auxiliar);

      temporal = std::move(parteIzquierda + parteDerecha);
    }
    return temporal;
  }

}

#endif
