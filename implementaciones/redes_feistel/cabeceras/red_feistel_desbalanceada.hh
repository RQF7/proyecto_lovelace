/**
 * \file
 * \brief Declaración de una red Feistel desbalanceada.
 *
 * Proyecto Lovelace.
 */

#ifndef __RED_FEISTEL_DESBALANCEADA__
#define __RED_FEISTEL_DESBALANCEADA__

#include "red_feistel.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"

namespace Implementaciones
{
  /**
   * \brief Implementación de una red Feistel desbalanceada.
   *
   * En cuestión de datos miembro, solamente se agrega el grado de
   * desbalanceo. Se sobrescriben las operaciones de cifrado y descifrado
   * de una red balanceada.
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
      RedFeistelDesbalanceada(unsigned int numeroDeRondas,
        unsigned int tamanioDeBloque, int desbalanceo = 0,
        FuncionDeRonda* funcionDeRonda =
          new FuncionDeRondaTrivial<Arreglo<tipo>, Arreglo<tipo>>,
        FuncionDeCombinacion* operadorSuma =
          new FuncionDeCombinacionTrivial<Arreglo<tipo>, Arreglo<tipo>>);

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
   * \param numeroDeRondas    Número de rondas.
   * \param tamanioDelBloque  Tamaño de bloque (entrada, salida).
   * \param desbalanceo       Grado de desbalanceo de la red; por defecto 0.
   * \param funcionDeRonda    Función de ronda par; por defecto implementación
   *                          trivial.
   * \param operadorSuma      Función para combinar bloques; por defecto
   *                          implementación trivial.
   *
   * \throw BalanceInvalido Si el grado de desbalanceo dado se sale del tamaño
   * de bloque.
   */

  template <typename tipo>
  RedFeistelDesbalanceada<tipo>::RedFeistelDesbalanceada(
    unsigned int numeroDeRondas,
    unsigned int tamanioDeBloque,
    int desbalanceo,
    FuncionDeRonda* funcionDeRonda,
    FuncionDeCombinacion* operadorSuma
  )
  : RedFeistel<tipo> {numeroDeRondas, tamanioDeBloque,
      funcionDeRonda, operadorSuma},
    mDesbalanceo {desbalanceo}
  {
    if (static_cast<unsigned int>(valorAbsoluto(desbalanceo))
      > tamanioDeBloque / 2)
      throw BalanceInvalido{
        "El desbalanceo se sale del tamaño de bloque."};
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
    Arreglo<tipo> auxiliar;
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      /* Partición */
      Arreglo<Arreglo<tipo>> partes = textoEnClaro[0] / Arreglo<int>{
        (static_cast<int>(textoEnClaro[0].obtenerNumeroDeElementos()) / 2)
        + mDesbalanceo};

      /* Operación normal */
      auxiliar = std::move(partes[1]);
      partes[1] = std::move(mOperadorSuma->operar(
        {partes[0], mFuncionDeRonda->operar({auxiliar})}));
      partes[0] = std::move(auxiliar);

      temporal = std::move(static_cast<Arreglo<int>>(partes[0])
        + static_cast<Arreglo<int>>(partes[1]));
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
    Arreglo<tipo> auxiliar;
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      /* Partición */
      Arreglo<Arreglo<tipo>> partes = textoCifrado[0] / Arreglo<int>{
        (static_cast<int>(textoCifrado[0].obtenerNumeroDeElementos()) / 2)
        + desbalanceoInverso};

      /* Operación normal */
      auxiliar = std::move(partes[0]);
      partes[0] = std::move(mOperadorSuma->deoperar(
        {partes[1], mFuncionDeRonda->operar({auxiliar})}));
      partes[1] = std::move(auxiliar);

      temporal = std::move(static_cast<Arreglo<int>>(partes[0])
        + static_cast<Arreglo<int>>(partes[1]));
    }
    return temporal;
  }

}

#endif
