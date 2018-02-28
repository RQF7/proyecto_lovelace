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

      /** \brief Construcción de red Feistel desbalanceada. */
      RedFeistelDesbalanceada(int numeroDeRondas,
        int tamanioDeBloque, int desbalanceo = 0,
        funcionDeOperacion<tipo> funcionDeRondaPar = operacionTrivial<tipo>,
        funcionDeCombinacion<tipo> operadorSuma = combinacionTrivial<tipo>,
        funcionDeCombinacion<tipo> operadorSumaInverso = nullptr);

      /** \brief Operación de cifrado de la red. */
      Arreglo<tipo> cifrar(const Arreglo<tipo>& textoEnClaro) override;

      /** \brief Operación de descifrado de la red. */
      Arreglo<tipo> descifrar(const Arreglo<tipo>& textoCifrado) override;

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

      /** \brief Referencia a operación de combinación inversa. */
      using RedFeistel<tipo>::mOperadorSumaInverso;

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
    funcionDeOperacion<tipo> funcionDeRonda,
    /** Función para combinar bloques; por defecto implementación trivial. */
    funcionDeCombinacion<tipo> operadorSuma,
    /** Inverso de la suma; por defecto la misma que el operadorSuma. */
    funcionDeCombinacion<tipo> operadorSumaInverso
  )
  : RedFeistel<tipo> {numeroDeRondas, tamanioDeBloque, funcionDeRonda,
      operadorSuma, operadorSumaInverso},
    mDesbalanceo {desbalanceo}
  {
  }

  /**
   * Realiza todas las rondas del proceso de cifrado.
   *
   * \return Bloque cifrado.
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistelDesbalanceada<tipo>::cifrar (
    const Arreglo<tipo>& textoEnClaro       /**< Bloque a cifrar. */
  )
  {
    Arreglo<tipo> temporal = std::move(textoEnClaro);
    Arreglo<tipo> parteDerecha, parteIzquierda, auxiliar;
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      /* Partición */
      parteIzquierda = std::move(temporal.partir(2, 0, mDesbalanceo));
      parteDerecha = std::move(temporal.partir(2, 1, mDesbalanceo));

      /* Operación normal */
      auxiliar = std::move(parteDerecha);
      parteDerecha =
        std::move(mOperadorSuma(parteIzquierda, mFuncionDeRonda(auxiliar)));
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
  Arreglo<tipo> RedFeistelDesbalanceada<tipo>::descifrar (
    const Arreglo<tipo>& textoCifrado       /**< Bloque a descifrar. */
  )
  {
    int desvalanceoInverso = (mTamanioDeBloque % 2 == 0)
      ? mDesbalanceo * -1
      : (mDesbalanceo * -1) + 1;
    Arreglo<tipo> temporal = std::move(textoCifrado);
    Arreglo<tipo> parteDerecha, parteIzquierda, auxiliar;
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      /* Partición */
      parteIzquierda = std::move(temporal.partir(2, 0, desvalanceoInverso));
      parteDerecha = std::move(temporal.partir(2, 1, desvalanceoInverso));

      /* Operación normal */
      auxiliar = std::move(parteIzquierda);
      parteIzquierda = std::move(mOperadorSumaInverso(
        parteDerecha, mFuncionDeRonda(auxiliar)));
      parteDerecha = std::move(auxiliar);

      temporal = std::move(parteIzquierda + parteDerecha);
    }
    return temporal;
  }

}

#endif
