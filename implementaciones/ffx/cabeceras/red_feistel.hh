/**
 * \file
 * \brief Implementación y definición de una red Feistel.
 *
 * Mismo caso que con la declaración del arreglo: como se trata de una clase
 * con plantillas, la declaración y la definición deben de estar en el mismo
 * archivo (reestricción de compilación).
 *
 * Proyecto Lovelace.
 */

#ifndef __RED_FEISTEL__
#define __RED_FEISTEL__

#include "arreglo.hh"

namespace Implementaciones
{
  /* Declaración *************************************************************/

  /** \brief Operación trivial: regresa copia del bloque dado. */
  template <typename tipo>
  Arreglo<tipo> operacionTrivial(const Arreglo<tipo>& arreglo);

  /** \brief Comprobación trivial: regresa solo el primer bloque. */
  template <typename tipo>
  Arreglo<tipo> combinacionTrivial(const Arreglo<tipo>& arregloUno,
    const Arreglo<tipo>& arregloDos);

  /**
   * \brief Implementación de red Feistel balanceada.
   *
   * \tparam tipo Tipo de dato con el que opera la red.
   *
   * \todo Excepciones de tamaños.
   * \todo Argumentos de función de ronda. ¿Cómo pasarlos sin hacerlos miembro
   * de esta clase.
   */

  template <typename tipo>
  class RedFeistel
  {

    /**
     * \brief Apuntador a función de operación.
     *
     * Una «función de operación» procesa un bloque: recibe una referencia
     * constante a un arreglo del tipo de datos con el que opera la red y
     * entrega un nuevo arreglo (con el mismo tipo de dato).
     *
     * Posibles implementaciones de esto son cifradores por bloque, funciones
     * hash, etc.
     */

    using funcionDeOperacion = Arreglo<tipo>(*)(const Arreglo<tipo>&);

    /**
     * \brief Apuntador a función de combinación.
     *
     * Una «función de combinación» procesa dos bloques: recibe dos
     * referencias constantes a arreglos del mismo tipo de dato con el que
     * opera la red y entrega un nuevo arreglo.
     *
     * Pensado como interfaz a funciones de XOR, de suma modular por caracter
     * o de suma modular por bloque.
     */

    using funcionDeCombinacion = Arreglo<tipo>(*)(const Arreglo<tipo>&,
      const Arreglo<tipo>&);

    public:

      /** \brief Red Feistel balanceada. */
      RedFeistel(int numeroDeRondas, int tamanioDeBloque,
        funcionDeOperacion funcionDeRonda = operacionTrivial<tipo>,
        funcionDeCombinacion operadorSuma = combinacionTrivial<tipo>);

      /** \brief Operación de cifrado de la red. */
      Arreglo<tipo> cifrar(const Arreglo<tipo>& textoEnClaro);

      /** \brief Operación de descifrado de la red. */
      Arreglo<tipo> descifrar(const Arreglo<tipo>& textoCifrado);

    private:

      /** \brief Número de rondas de la red. */
      int mNumeroDeRondas;

      /** \brief Tamaño de los bloques. */
      int mTamanioDeBloque;

      /** \brief Función de ronda. */
      funcionDeOperacion mFuncionDeRonda;

      /** \brief Operación de combinación. */
      funcionDeCombinacion mOperadorSuma;

      /** \brief */
      int mRondaActual;
  };

  /* Definición **************************************************************/

  /**
   * Construye una red Feistel con los parámetros dados. Si no se especifíca
   * una función de ronda y/o un operador, estos actúan en modo trivial.
   * Inicializa el contador de ronda actual en cero.
   *
   * \todo Lanzar excepción cuando el tamaño de bloque sea impar.
   */

  template <typename tipo>
  RedFeistel<tipo>::RedFeistel(
    int numeroDeRondas,            /**< Número de rondas. */
    int tamanioDeBloque,           /**< Tamaño de bloque (entrada, salida). */
    funcionDeOperacion funcionDeRonda,  /**< Función de ronda. */
    funcionDeCombinacion operadorSuma   /**< Función para combinar bloques. */
  )
  : mNumeroDeRondas {numeroDeRondas},
    mTamanioDeBloque {tamanioDeBloque},
    mFuncionDeRonda {funcionDeRonda},
    mOperadorSuma {operadorSuma},
    mRondaActual {0}
  {
  }

  /**
   * Realiza todas las rondas del proceso de cifrado. La operación de una
   * ronda se resume como:
   * PI_{i} = PD_{i - 1}
   * PD_{i} = F(PD_{i - 1}) \xor PI_{i - 1}
   *
   * \return Bloque cifrado.
   *
   * \note **Importante:** los *move* del ciclo agilizan la operación de la
   * red; en luegar de estar haciendo copias inútiles, simplemente se
   * actualizan apuntadores.
   *
   * \sa http://www.cplusplus.com/reference/utility/move/
   *
   * \todo La operación de partición tendría que ser una sola función.
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistel<tipo>::cifrar (
    const Arreglo<tipo>& textoEnClaro       /**< Bloque a cifrar. */
  )
  {
    Arreglo<tipo> parteIzquierda = textoEnClaro.partir(2, 0);
    Arreglo<tipo> parteDerecha = textoEnClaro.partir(2, 1);
    Arreglo<tipo> auxiliar (mTamanioDeBloque / 2);
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      auxiliar = std::move(parteDerecha);
      parteDerecha =
        std::move(mOperadorSuma(parteIzquierda, mFuncionDeRonda(auxiliar)));
      parteIzquierda = std::move(auxiliar);
    }
    return parteIzquierda + parteDerecha;
  }

  /**
   * Realiza todas las rondas del proceso de descifrado. La operación de una
   * ronda se resume como:
   * PD_{i - 1} = PI_{i}
   * PI_{i - 1} = f(PD_{i - 1}) \xor PD_{i}
   *
   * \return Bloque descifrado.
   *
   * \sa http://www.cplusplus.com/reference/utility/move/
   *
   * \todo Las particiones se tendrían que hacer en una sola función.
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistel<tipo>::descifrar (
    const Arreglo<tipo>& textoCifrado       /**< Bloque a descifrar. */
  )
  {
    Arreglo<tipo> parteIzquierda = textoCifrado.partir(2, 0);
    Arreglo<tipo> parteDerecha = textoCifrado.partir(2, 1);
    Arreglo<tipo> auxiliar (mTamanioDeBloque / 2);
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      auxiliar = std::move(parteIzquierda);
      parteIzquierda =
        std::move(mOperadorSuma(parteDerecha, mFuncionDeRonda(auxiliar)));
      parteDerecha = std::move(auxiliar);
    }
    return parteIzquierda + parteDerecha;
  }

  /**
   * \note Con fines ilustrativos solamente:
   * aparte de la implementación dada, se consideran otras dos. La primera
   * recibe el arreglo por valor (no por referencia) y su cuerpo es:
   * ```
   * return Arreglo<tipo>(arreglo);
   * ```
   * La segunda también recibe el arreglo por valor, pero su cuerpo es:
   * ```
   * return Arreglo<tipo>(std::move(arreglo));
   * ```
   * El compilador efectúa una operación de copia (`O(n)`) al llamar a una
   * función con argumentos por valor y una operación de movimiento (`O(1)`)
   * al regreso de cada función. Dicho esto, podemos decir que la primera
   * versión ejecuta dos operaciones de copia, una detrás de la otra, y una
   * operación de movimiento (`O(n) + O(n) + O(1)`); la segunda versión es
   * una mejora, dado que quita una de las operaciones de copia redundantes
   * (`O(n) + O(1) + O(1)`). La versión original (la que recibe el argumento
   * por referencia), efectúa casi las mismas operaciones que la segunda
   * versión, solo que con un orden distinto y con una sintaxis más clara
   * (`O(1) + O(n) + O(1)`); en este caso la primera operación no corresponde
   * a una llamada al constructor por movimiento, sino que es el costo de la
   * creación de la referencia. En todo caso, la versión  que hay que evitar
   * a toda costa es la primera, dado que hay una copia redundante.
   *
   * \return Copia de bloque dado.
   *
   * \sa http://www.cplusplus.com/reference/utility/move/
   *
   * \todo ¿Tiene caso hacer implementación trivial con puras operaciones de
   * movimiento? Tal vez como ejercicio de C++, pero no con espera de que
   * se ocupe en algún lado.
   */

  template <typename tipo>
  Arreglo<tipo> operacionTrivial(
    const Arreglo<tipo>& arreglo      /**< Referencia a bloque de entrada. */
  )
  {
    return Arreglo<tipo>(arreglo);
  }

  /**
   * El primer bloque es el del lado izquierdo, mientras que el segundo bloque
   * es la salida de la función de ronda. Al regresar solo el primer bloque,
   * se busca que, en una red con funciones de ronda y de combinaciones
   * triviales, la salida sea el mismo bloque (si el número de rondas es par),
   * o el bloque de entrada invertido (si el número de rondas es impar).
   *
   * \return Copia del primer bloque.
   */

  template <typename tipo>
  Arreglo<tipo> combinacionTrivial(
    const Arreglo<tipo>& arregloUno,  /**< Referencia a primer bloque. */
    const Arreglo<tipo>& arregloDos   /**< Referencia a segudo bloque. */
  )
  {
    return Arreglo<tipo>(arregloUno);
  }

}

#endif
