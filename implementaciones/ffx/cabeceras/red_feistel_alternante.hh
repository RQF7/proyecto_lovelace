/**
 * \file
 * \brief Declaración de una red Feistel alternante.
 *
 * Proyecto Lovelace.
 */

#ifndef __RED_FEISTEL_ALTERNANTE__
#define __RED_FEISTEL_ALTERNANTE__

#include "red_feistel.hh"

namespace Implementaciones
{
  /**
   * \brief Implementación de una red Feistel alternante.
   *
   * Agrega a los datos de una red Feistel una función de ronda más, para ser
   * usada en las rondas impares (en las pares se utiliza la función de la
   * superclase). También agrega un grado de desbalanceo que permite controlar
   * en qué parte del bloque se hacen las particiones. Sobreescribe las
   * operaciones de cifrado y descifrado.
   *
   * \note Después de hacer las implementaciones de las otras dos (las
   * balanceadas y las desbalanceadas), la de las redes alternantes resulta
   * mucho más intuitiva: las operaciones de cifrado y descifrado son iguales
   * (casi) y son menos intrucciones por ronda.
   *
   * \tparam tipo Tipo con el que opera la red.
   */

  template <typename tipo>
  class RedFeistelAlternante : public RedFeistel<tipo>
  {
    public:

      /** \brief Definición de función de ronda en super clase. */
      using FuncionDeRonda =
        typename RedFeistel<tipo>::FuncionDeRonda;

      /** \brief Definición de función de combinación en super clase. */
      using FuncionDeCombinacion =
        typename RedFeistel<tipo>::FuncionDeCombinacion;

      /** \brief Construcción de red Feistel alternante. */
      RedFeistelAlternante(int numeroDeRondas,
        int tamanioDeBloque, int desbalanceo = 0,
        FuncionDeRonda* funcionDeRondaPar =
          new FuncionDeRondaTrivial<Arreglo<tipo>, Arreglo<tipo>>,
        FuncionDeRonda* funcionDeRondaImpar =
          new FuncionDeRondaTrivial<Arreglo<tipo>, Arreglo<tipo>>,
        FuncionDeCombinacion* operadorSuma =
          new FuncionDeCombinacionTrivial<Arreglo<tipo>, Arreglo<tipo>>);

      /** \brief Destructor. */
      ~RedFeistelAlternante();

      /** \brief Operación de cifrado de la red. */
      Arreglo<tipo> operar(
        const std::vector<Arreglo<tipo>>& textoEnClaro) override;

      /** \brief Operación de descifrado de la red. */
      Arreglo<tipo> deoperar(
        const std::vector<Arreglo<tipo>>& textoCifrado) override;

    private:

      /** \brief Grado de desbalanceo de la red. */
      int mDesbalanceo;

      /** \brief Función de ronda impar (para pares se utiliza la de la
       *  superclase). */
      FuncionDeRonda* mFuncionDeRondaImpar;

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
   * Si no se pasa ninguna función para las rondas impares (o si se pasa un
   * nullptr) esta se supone igual que el de la ronda par. El desbalanceo se
   * pasa sin ninguna modificación a la función de *partir*, de la clase
   * Arreglo.
   *
   * \todo Lanzar excepción cuando el desbalanceo no concuerde con el tamaño
   * de bloque.
   */

  template <typename tipo>
  RedFeistelAlternante<tipo>::RedFeistelAlternante(
    /** Número de rondas. */
    int numeroDeRondas,
    /** Tamaño de bloque (entrada, salida). */
    int tamanioDeBloque,
    /** Grado de desbalanceo de la red; por defecto 0. */
    int desbalanceo,
    /** Función de ronda par; por defecto implementación trivial. */
    FuncionDeRonda* funcionDeRondaPar,
    /** Función de ronda impar; por defecto misma que para las pares. */
    FuncionDeRonda* funcionDeRondaImpar,
    /** Función para combinar bloques; por defecto implementación trivial. */
    FuncionDeCombinacion* operadorSuma
  )
  : RedFeistel<tipo> {numeroDeRondas, tamanioDeBloque,
      funcionDeRondaPar, operadorSuma},
    mDesbalanceo {desbalanceo},
    mFuncionDeRondaImpar {funcionDeRondaImpar}
  {
  }

  /**
   * Libera la memoria del apuntador a la función de ronda impar.
   */

  template <typename tipo>
  RedFeistelAlternante<tipo>::~RedFeistelAlternante()
  {
    delete mFuncionDeRondaImpar;
  }

  /**
   * Realiza todas las rondas del proceso de cifrado. La operación de una
   * ronda se resume como:
   * Si es par, PI_{i} = F(PD_{i - 1}) \xor PI_{i - 1}
   *            PD_{i} = PD_{i - 1}
   * Si es impar, PD_{i} = F(PI_{i - 1}) \xor PD_{i - 1}
   *              PI_{i} = PI_{i - 1}
   * La función de ronda usada depende de si esta es par, o impar.
   *
   * \return Bloque cifrado.
   *
   * \todo La operación de partición tendría que ser una sola función.
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistelAlternante<tipo>::operar(
    const std::vector<Arreglo<tipo>>& textoEnClaro     /**< Bloque a cifrar. */
  )
  {
    Arreglo<tipo> parteIzquierda = textoEnClaro[0].partir(2, 0, mDesbalanceo);
    Arreglo<tipo> parteDerecha = textoEnClaro[0].partir(2, 1, mDesbalanceo);
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      if (mRondaActual % 2 == 0)
      {
        parteIzquierda = std::move(mOperadorSuma->operar(
          {parteIzquierda, mFuncionDeRonda->operar({parteDerecha})}));
      }
      else
      {
        parteDerecha = std::move(mOperadorSuma->operar(
          {parteDerecha, mFuncionDeRondaImpar->operar({parteIzquierda})}));
      }
    }
    return parteIzquierda + parteDerecha;
  }

  /**
   * Realiza todas las rondas del proceso de descifrado. La operación de las
   * rondas es la misma que en el proceso de cifrado; no se hacen una sola
   * función porque es necesario mantener la estructura dada por la superclase
   * y porque es necesario llevar el contador de rondas en orden descendente.
   *
   * \return Bloque descifrado.
   *
   * \sa http://www.cplusplus.com/reference/utility/move/
   *
   * \todo Las particiones se tendrían que hacer en una sola función.
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistelAlternante<tipo>::deoperar(
    const std::vector<Arreglo<tipo>>& textoCifrado   /**< Bloque a descifrar. */
  )
  {
    Arreglo<tipo> parteIzquierda = textoCifrado[0].partir(2, 0, mDesbalanceo);
    Arreglo<tipo> parteDerecha = textoCifrado[0].partir(2, 1, mDesbalanceo);
    for (mRondaActual = mNumeroDeRondas - 1; mRondaActual >= 0; mRondaActual--)
    {
      if (mRondaActual % 2 == 0)
      {
        parteIzquierda = std::move(mOperadorSuma->deoperar({
          parteIzquierda, mFuncionDeRonda->operar({parteDerecha})}));
      }
      else
      {
        parteDerecha = std::move(mOperadorSuma->deoperar({
          parteDerecha, mFuncionDeRondaImpar->operar({parteIzquierda})}));
      }
    }
    return parteIzquierda + parteDerecha;
  }

}

#endif
