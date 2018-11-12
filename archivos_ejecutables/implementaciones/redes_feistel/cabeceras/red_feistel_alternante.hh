/**
 * \file
 * \brief Declaración de una red Feistel alternante.
 *
 * Proyecto Lovelace.
 */

#ifndef __RED_FEISTEL_ALTERNANTE__
#define __RED_FEISTEL_ALTERNANTE__

#include "red_feistel.hh"
#include <string>

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
      RedFeistelAlternante(unsigned int numeroDeRondas,
        unsigned int tamanioDeBloque, int desbalanceo = 0,
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

      /** \brief Operación de escritura sobre la función de ronda par. */
      inline void colocarFuncionDeRondaImpar(FuncionDeRonda *funcionDeRondaImpar)
        { delete mFuncionDeRondaImpar; mFuncionDeRondaImpar = funcionDeRondaImpar; }

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
   * \param numeroDeRondas      Número de rondas.
   * \param tamanioDeBloque     Tamaño de bloque (entrada, salida).
   * \param desbalanceo         Grado de desbalanceo de la red; por defecto 0.
   * \param funcionDeRondaPar   Función de ronda par; por defecto implementación
   *                            trivial.
   * \param funcionDeRondaImpar Función de ronda impar; por defecto misma que
   *                            para las pares.
   * \param operadorSuma        Función para combinar bloques; por defecto
   *                            implementación trivial.
   *
   * \throw BalanceInvalido Si el grado de desbalanceo dado se sale del tamaño
   * de bloque.
   */

  template <typename tipo>
  RedFeistelAlternante<tipo>::RedFeistelAlternante(
    unsigned int numeroDeRondas,
    unsigned int tamanioDeBloque,
    int desbalanceo,
    FuncionDeRonda* funcionDeRondaPar,
    FuncionDeRonda* funcionDeRondaImpar,
    FuncionDeCombinacion* operadorSuma
  )
  : RedFeistel<tipo> {numeroDeRondas, tamanioDeBloque,
      funcionDeRondaPar, operadorSuma},
    mDesbalanceo {desbalanceo},
    mFuncionDeRondaImpar {funcionDeRondaImpar}
  {
    if (static_cast<unsigned int>(valorAbsoluto(desbalanceo)) >
      tamanioDeBloque / 2)
      throw BalanceInvalido{
        "El desbalanceo se sale del tamaño de bloque."};
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
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistelAlternante<tipo>::operar(
    const std::vector<Arreglo<tipo>>& textoEnClaro     /**< Bloque a cifrar. */
  )
  {
    Arreglo<Arreglo<tipo>> partes = textoEnClaro[0] / Arreglo<unsigned int>{
      (textoEnClaro[0].obtenerNumeroDeElementos() / 2) + mDesbalanceo};
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      if (mRondaActual % 2 == 0)
        partes[0] = std::move(mOperadorSuma->operar(
          {partes[0], mFuncionDeRonda->operar({partes[1]})}));
      else
        partes[1] = std::move(mOperadorSuma->operar(
          {partes[1], mFuncionDeRondaImpar->operar({partes[0]})}));
    }
    return static_cast<Arreglo<int>>(partes[0])
      || static_cast<Arreglo<int>>(partes[1]);
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
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistelAlternante<tipo>::deoperar(
    const std::vector<Arreglo<tipo>>& textoCifrado   /**< Bloque a descifrar. */
  )
  {
    Arreglo<Arreglo<tipo>> partes = textoCifrado[0] / Arreglo<unsigned int>{
      (textoCifrado[0].obtenerNumeroDeElementos() / 2) + mDesbalanceo};
    for (mRondaActual = mNumeroDeRondas - 1; mRondaActual >= 0; mRondaActual--)
    {
      if (mRondaActual % 2 == 0)
        partes[0] = std::move(mOperadorSuma->deoperar({
          partes[0], mFuncionDeRonda->operar({partes[1]})}));
      else
        partes[1] = std::move(mOperadorSuma->deoperar({
          partes[1], mFuncionDeRondaImpar->operar({partes[0]})}));
      if (mRondaActual == 0)
        break;
    }
    return static_cast<Arreglo<int>>(partes[0])
      || static_cast<Arreglo<int>>(partes[1]);
  }

}

#endif
