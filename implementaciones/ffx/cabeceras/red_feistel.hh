/**
 * \file
 * \brief Implementación y declaración de una red Feistel.
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
#include "funcion.hh"
#include "funcion_con_inverso.hh"
#include "funcion_de_ronda_trivial.hh"
#include "funcion_de_combinacion_trivial.hh"
#include <vector>

namespace Implementaciones
{

  /**
   * \brief Implementación de red Feistel balanceada.
   *
   * Implementa la interfaz de *Funcion* (a través de *FuncionConInverso*);
   * de esta manera, la función de ronda de una red Feistel, podría ser otra
   * red Feistel.
   *
   * \tparam tipo Tipo de dato con el que opera la red.
   *
   * \todo Excepciones de tamaños.
   * \todo Argumentos de función de ronda. ¿Cómo pasarlos sin hacerlos miembro
   * de esta clase.
   */

  template <typename tipo>
  class RedFeistel : public FuncionConInverso<Arreglo<tipo>, Arreglo<tipo>>
  {
    public:

      /**
       * \brief Definición de tipo de funciones de ronda.
       *
       * Define el template de la clase *Funcion* que usa de forma interna la
       * red Feistel para la función de ronda. Esta función toma a la entrada
       * referencias de arreglos y regresa un nuevo arreglo; el tipo de datos de
       * estos arreglos es tomado del template de la Red.
       */

      using FuncionDeRonda = Funcion<Arreglo<tipo>, Arreglo<tipo>>;

      /**
       * \brief Definición de operación de combinación.
       *
       * Define el template de la clase *Funcion* que usa de forma interna la
       * red Feistel para la operación de combinación. La única diferencia con
       * respecto al tipo de la función de operación es que esta tiene una
       * operación inversa (la interfaz *FuncionConInverso* implementa a su
       * vez a la interfaz de *Funcion*).
       */

      using FuncionDeCombinacion = FuncionConInverso<Arreglo<tipo>,
        Arreglo<tipo>>;

    protected:

      /** \brief Función de ronda usada por defecto. */
      static FuncionDeRondaTrivial<Arreglo<tipo>, Arreglo<tipo>>
        funcionDeRondaPorDefecto;

      /** \brief Función de combinación usada por defecto. */
      static FuncionDeCombinacionTrivial<Arreglo<tipo>, Arreglo<tipo>>
        funcionDeCombinacionPorDefecto;

    public:

      /** \brief Construcción de red Feistel balanceada. */
      RedFeistel(int numeroDeRondas, int tamanioDeBloque,
        FuncionDeRonda& funcionDeRonda =
          RedFeistel<tipo>::funcionDeRondaPorDefecto,
        FuncionDeCombinacion& operadorSuma =
          RedFeistel<tipo>::funcionDeCombinacionPorDefecto);

      /** \brief Operación de cifrado de la red. */
      virtual Arreglo<tipo> operar(
        const std::vector<Arreglo<tipo>>& textoEnClaro) override;

      /** \brief Operación de descifrado de la red. */
      virtual Arreglo<tipo> deoperar(
        const std::vector<Arreglo<tipo>>& textoCifrado) override;

    protected:

      /** \brief Número de rondas de la red. */
      int mNumeroDeRondas;

      /** \brief Tamaño de los bloques. */
      int mTamanioDeBloque;

      /** \brief Función de ronda. */
      FuncionDeRonda& mFuncionDeRonda;

      /** \brief Operación de combinación. */
      FuncionDeCombinacion& mOperadorSuma;

      /** \brief Ronda actual (pensando en implementaciones
       *  concurrentes). */
      int mRondaActual;
  };

  /* Definición **************************************************************/

  /**
   * Referencia a una función de ronda trivial.
   *
   * \note Tanto para este miembro como para la función de combinación por
   * defecto, para poder ser ligados de alguna manera a los argumentos del
   * constructor, deben por fuerza ser estáticos: como se trata de
   * referencias no constantes, el ligador necesita reservar su espacio
   * de manera distinta a las expresiones constantes; las funciones no
   * pueden ser constantes, dado que en la mayoría de las implementaciones
   * reales se espera guardar (y cambiar) en el estado del objeto
   * información propia de este (e.g. la llave o el tweak). La desventaja
   * de este método es que se reserva espacio para las funciones se ocupen
   * o no (como cualquier miembro estático); la ventaja es que el código
   * de mis pruebas triviales está mucho más limpio, y al fin y al cabo,
   * son funciones muy muy pequeñas.
   */

  template <typename tipo>
  FuncionDeRondaTrivial<Arreglo<tipo>, Arreglo<tipo>>
    RedFeistel<tipo>::funcionDeRondaPorDefecto;

  /**
   * Referencia a una función de combinación trivial.
   *
   * \note Estas líneas corresponden a la definición de los miembros estáticos,
   * mientras que las anteriores (las que están dentro de la clase) corresponden
   * a la declaración (aunque se parezcan bastante, sin la definición, el
   * ligador se pierde).
   */

  template <typename tipo>
  FuncionDeCombinacionTrivial<Arreglo<tipo>, Arreglo<tipo>>
    RedFeistel<tipo>::funcionDeCombinacionPorDefecto;

  /**
   * Construye una red Feistel con los parámetros dados. Si no se especifíca
   * una función de ronda y/o un operador, estos actúan en modo trivial.
   * Inicializa el contador de ronda actual en cero. Si no se da una operación
   * inversa a la suma, se deja esta para ambas operaciones.
   *
   * \todo Lanzar excepción cuando el tamaño de bloque sea impar.
   * Pensándolo bien... este constructor también lo usan las clases derivadas.
   * ¿Se necesitan dos distintos?
   */

  template <typename tipo>
  RedFeistel<tipo>::RedFeistel(
    /** Número de rondas. */
    int numeroDeRondas,
    /** Tamaño de bloque (entrada, salida). */
    int tamanioDeBloque,
    /** Función de ronda; por defecto implementación trivial. */
    FuncionDeRonda& funcionDeRonda,
    /** Función para combinar bloques; por defecto implementación trivial. */
    FuncionDeCombinacion& operadorSuma
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
  Arreglo<tipo> RedFeistel<tipo>::operar(
    const std::vector<Arreglo<tipo>>& textoEnClaro      /**< Bloque a cifrar. */
  )
  {
    Arreglo<tipo> parteIzquierda = textoEnClaro[0].partir(2, 0);
    Arreglo<tipo> parteDerecha = textoEnClaro[0].partir(2, 1);
    Arreglo<tipo> auxiliar (mTamanioDeBloque / 2);
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      auxiliar = std::move(parteDerecha);
      parteDerecha = std::move(
        mOperadorSuma.operar({parteIzquierda,
          mFuncionDeRonda.operar({auxiliar})}));
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
  Arreglo<tipo> RedFeistel<tipo>::deoperar(
    const std::vector<Arreglo<tipo>>& textoCifrado   /**< Bloque a descifrar. */
  )
  {
    Arreglo<tipo> parteIzquierda = textoCifrado[0].partir(2, 0);
    Arreglo<tipo> parteDerecha = textoCifrado[0].partir(2, 1);
    Arreglo<tipo> auxiliar (mTamanioDeBloque / 2);
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      auxiliar = std::move(parteIzquierda);
      parteIzquierda = std::move(
        mOperadorSuma.deoperar({parteDerecha,
          mFuncionDeRonda.operar({auxiliar})}));
      parteDerecha = std::move(auxiliar);
    }
    return parteIzquierda + parteDerecha;
  }

}

#endif
