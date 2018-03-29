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

#include "funcion_de_ronda_trivial.hh"
#include "funcion_de_combinacion_trivial.hh"
#include "../../../utilidades/cabeceras/error.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include "../../../utilidades/interfaces_comunes/funcion_con_inverso.hh"
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
   */

  template <typename tipo>
  class RedFeistel
  : public Utilidades::FuncionConInverso<Arreglo<tipo>, Arreglo<tipo>>
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

      using FuncionDeRonda = Utilidades::Funcion<Arreglo<tipo>, Arreglo<tipo>>;

      /**
       * \brief Definición de operación de combinación.
       *
       * Define el template de la clase *Funcion* que usa de forma interna la
       * red Feistel para la operación de combinación. La única diferencia con
       * respecto al tipo de la función de operación es que esta tiene una
       * operación inversa (la interfaz *FuncionConInverso* implementa a su
       * vez a la interfaz de *Funcion*).
       */

      using FuncionDeCombinacion = Utilidades::FuncionConInverso<Arreglo<tipo>,
        Arreglo<tipo>>;

    public:

      /** \brief Construcción de red Feistel balanceada. */
      RedFeistel(unsigned int numeroDeRondas, unsigned int tamanioDeBloque,
        FuncionDeRonda* funcionDeRonda =
          new FuncionDeRondaTrivial<Arreglo<tipo>, Arreglo<tipo>>,
        FuncionDeCombinacion* operadorSuma =
          new FuncionDeCombinacionTrivial<Arreglo<tipo>, Arreglo<tipo>>);

      /** \brief Constructor vacío. */
      RedFeistel();

      /** \brief Destructor. */
      ~RedFeistel();

      /** \brief Operación de cifrado de la red. */
      virtual Arreglo<tipo> operar(
        const std::vector<Arreglo<tipo>>& textoEnClaro) override;

      /** \brief Operación de descifrado de la red. */
      virtual Arreglo<tipo> deoperar(
        const std::vector<Arreglo<tipo>>& textoCifrado) override;

    protected:

      /** \brief Número de rondas de la red. */
      unsigned int mNumeroDeRondas;

      /** \brief Tamaño de los bloques. */
      unsigned int mTamanioDeBloque;

      /** \brief Función de ronda. */
      FuncionDeRonda* mFuncionDeRonda;

      /** \brief Operación de combinación. */
      FuncionDeCombinacion* mOperadorSuma;

      /** \brief Ronda actual (pensando en implementaciones
       *  concurrentes). */
      unsigned int mRondaActual;
  };

  /** \brief Balanceo inválido en generalizaciones. */
  struct BalanceInvalido : public Utilidades::Error {
    inline BalanceInvalido(std::string mensaje)
    : Utilidades::Error{mensaje} {}};

  /* Definición **************************************************************/

  /**
   * Construye una red Feistel con los parámetros dados. Si no se especifíca
   * una función de ronda y/o un operador, estos actúan en modo trivial.
   * Inicializa el contador de ronda actual en cero. Si no se da una operación
   * inversa a la suma, se deja esta para ambas operaciones.
   *
   * \param numeroDeRondas  Número de rondas.
   * \param tamanioDeBloque Tamaño de bloque (entrada, salida).
   * \param funcionDeRonda  Función de ronda; por defecto implementación
                            trivial.
   * \param operadorSuma    Función para combinar bloques; por defecto
                            implementación trivial.
   *
   * \todo Lanzar excepción cuando el tamaño de bloque sea impar.
   * Pensándolo bien... este constructor también lo usan las clases derivadas.
   * ¿Se necesitan dos distintos?
   *
   */

  template <typename tipo>
  RedFeistel<tipo>::RedFeistel(
    unsigned int numeroDeRondas,
    unsigned int tamanioDeBloque,
    FuncionDeRonda* funcionDeRonda,
    FuncionDeCombinacion* operadorSuma
  )
  : mNumeroDeRondas {numeroDeRondas},
    mTamanioDeBloque {tamanioDeBloque},
    mFuncionDeRonda {funcionDeRonda},
    mOperadorSuma {operadorSuma},
    mRondaActual {0u}
  {
  }

  /**
   * Permite tener objetos sin "sin inicializar".
   */

  template <typename tipo>
  RedFeistel<tipo>::RedFeistel()
  {
  }

  /**
   * Libera la memoria reservada para la función de ronda y la función de
   * combinación.
   *
   * \note Para que esto funcione en código polimórfico, el destructor de la
   * superclase debe ser virtual.
   */

  template <typename tipo>
  RedFeistel<tipo>::~RedFeistel()
  {
    delete mFuncionDeRonda;
    delete mOperadorSuma;
  }

  /**
   * Realiza todas las rondas del proceso de cifrado. La operación de una
   * ronda se resume como:
   * \f[
   * PI_{i} = PD_{i - 1}
   * \f]
   * \f[
   * PD_{i} = F(PD_{i - 1}) \oplus PI_{i - 1}
   * \f]
   *
   * \return Bloque cifrado.
   *
   * \note **Importante:** los *move* del ciclo agilizan la operación de la
   * red; en luegar de estar haciendo copias inútiles, simplemente se
   * actualizan apuntadores.
   *
   * \sa http://www.cplusplus.com/reference/utility/move/
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistel<tipo>::operar(
    const std::vector<Arreglo<tipo>>& textoEnClaro      /**< Bloque a cifrar. */
  )
  {
    Arreglo<Arreglo<tipo>> partes = textoEnClaro[0] / Arreglo<unsigned int>{
      textoEnClaro[0].obtenerNumeroDeElementos() / 2};
    Arreglo<tipo> auxiliar (mTamanioDeBloque / 2);
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      auxiliar = std::move(partes[1]);
      partes[1] = std::move(
        mOperadorSuma->operar({partes[0],
          mFuncionDeRonda->operar({auxiliar})}));
      partes[0] = std::move(auxiliar);
    }
    return static_cast<Arreglo<int>>(partes[0])
      + static_cast<Arreglo<int>>(partes[1]);
  }

  /**
   * Realiza todas las rondas del proceso de descifrado. La operación de una
   * ronda se resume como:
   * \f[
   * PD_{i - 1} = PI_{i}
   * \f]
   * \f[
   * PI_{i - 1} = f(PD_{i - 1}) \oplus PD_{i}
   * \f]
   *
   * \return Bloque descifrado.
   *
   * \sa http://www.cplusplus.com/reference/utility/move/
   */

  template <typename tipo>
  Arreglo<tipo> RedFeistel<tipo>::deoperar(
    const std::vector<Arreglo<tipo>>& textoCifrado   /**< Bloque a descifrar. */
  )
  {
    Arreglo<Arreglo<tipo>> partes = textoCifrado[0] / Arreglo<unsigned int>{
      textoCifrado[0].obtenerNumeroDeElementos() / 2};
    Arreglo<tipo> auxiliar (mTamanioDeBloque / 2);
    for (mRondaActual = 0; mRondaActual < mNumeroDeRondas; mRondaActual++)
    {
      auxiliar = std::move(partes[0]);
      partes[0] = std::move(
        mOperadorSuma->deoperar({partes[1],
          mFuncionDeRonda->operar({auxiliar})}));
      partes[1] = std::move(auxiliar);
    }
    return static_cast<Arreglo<int>>(partes[0])
      + static_cast<Arreglo<int>>(partes[1]);
  }

}

#endif
