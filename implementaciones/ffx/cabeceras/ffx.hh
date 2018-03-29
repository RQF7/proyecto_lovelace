/**
 * \file
 * \brief Clase genérica de FFX.
 * Proyecto Lovelace.
 */

#ifndef __FFX__
#define __FFX__

#include "combinacion_por_caracter.hh"
#include "combinacion_por_bloque.hh"
#include "../../redes_feistel/cabeceras/red_feistel.hh"
#include "../../redes_feistel/cabeceras/red_feistel_alternante.hh"
#include "../../redes_feistel/cabeceras/red_feistel_desbalanceada.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/interfaces_comunes/funcion_con_inverso.hh"

namespace Implementaciones
{
  /**
   * \brief Clase de FFX.
   *
   * Implementación genérica de FFX: no define ningún tipo de alfabeto; deja
   * al usuario de la clase la definición de todos los parámetros de FFX.
   * Tanto FFXA10 como FFXA2 son instanciaciones específicas de esta clase.
   *
   * Al igual que las propias redes Feistel, esta clase también es una
   * implementación de una función con inverso (operaciones de ida y vuelta),
   * por lo que en realidad se puede utilizar a FFX dentro du una función de
   * ronda de una red Feistel (que a su vez puede o no tener que ver con
   * una instanciación de otro FFX).
   */

  template <typename tipo /**< Tipo de dato con el que se opera. */ >
  class FFX : public Utilidades::FuncionConInverso<Arreglo<tipo>, Arreglo<tipo>>
  {
    public:

      /** \brief Enumeración de los tipos de operación de combinación. */
      enum class TipoDeCombinacion {porBloque, porCaracter};

      /** \brief Enumeración de los tipos de red Feistel. */
      enum class TipoDeRed {alternante, desbalanceada};

      /** \brief Uso de alias definido en red Feistel para una
       *  función de ronda. */
      using FuncionDeRonda =
        typename RedFeistel<tipo>::FuncionDeRonda;

      /** \brief Uso de alias definido en red Feistel para una
       *  función de combinación. */
      using FuncionDeCombinacion =
        typename RedFeistel<tipo>::FuncionDeCombinacion;

      /** \brief Inicialización de red interna. */
      FFX(unsigned int radix, unsigned int tamanioDeMensaje,
        TipoDeCombinacion tipoDeCombinacion, TipoDeRed tipoDeRed,
        int desbalanceo, unsigned int numeroDeRondas,
        FuncionDeRonda *funcionDeRondaPar,
        FuncionDeRonda *funcionDeRondaImpar);

      /** \brief Liberación de memoria. */
      ~FFX();

      /** \brief Proceso de cifrado. */
      Arreglo<tipo> operar(
        const std::vector<Arreglo<tipo>> &entrada) override;

      /** \brief Proceso de descifrado. */
      Arreglo<tipo> deoperar(
        const std::vector<Arreglo<tipo>> &entrada) override;

    private:

      /** \brief Apuntador a red interna (polimorfismo). */
      RedFeistel<tipo> *mRedFeistel;
  };

  /**
   * Se imita la interfaz definida en el la especificación del algoritmo, aunque
   * en algunos casos resulte un tanto disparejo con respecto a otras de mis
   * implementaciones; por ejemplo, la red Feistel y el tipo de operación de
   * combinación se manejan a través de enumeraciones, mientras que la función
   * de ronda sí es un parámetro abierto (una implementación más genérica
   * dejaría a todos los parámetros abiertos).
   *
   * El apuntador a función de ronda para las impares solamente se ocupa
   * cuando el tipo de red usado es alternante.
   *
   * Lo que se hace en el constructor es interpretar las enumeraciones para
   * instanciar a la red Feistel.
   */

  template <typename tipo>
  FFX<tipo>::FFX(
    /** Cardinalidad del alfabeto. */
    unsigned int radix,
    /** Tamaño de cadenas procesadas. */
    unsigned int tamanioDeMensaje,
    /** Tipo de operación de combinación a ocupar. */
    TipoDeCombinacion tipoDeCombinacion,
    /** Tipo de red Feistel a ocupar. */
    TipoDeRed tipoDeRed,
    /** Nivel de desbalanceo de la red. */
    int desbalanceo,
    /** Número de rondas. */
    unsigned int numeroDeRondas,
    /** Apuntador a función de ronda (pares). */
    FuncionDeRonda *funcionDeRondaPar,
    /** Apuntador a función de ronda (impares). */
    FuncionDeRonda *funcionDeRondaImpar
  )
  {
    /* Operación de combinación. */
    FuncionDeCombinacion* operacionCombinacion = nullptr;
    if (tipoDeCombinacion == TipoDeCombinacion::porCaracter)
      operacionCombinacion = new CombinacionPorCaracter<tipo>{radix};
    else
      operacionCombinacion = new CombinacionPorBloque<tipo>{radix};

    /* Tipo de red Feistel. */
    if (tipoDeRed == TipoDeRed::alternante)
      mRedFeistel = new RedFeistelAlternante<tipo>{
        numeroDeRondas,
        tamanioDeMensaje,
        desbalanceo,
        funcionDeRondaPar,
        funcionDeRondaImpar,
        operacionCombinacion
      };
    else
      mRedFeistel = new RedFeistelDesbalanceada<tipo>{
        numeroDeRondas,
        tamanioDeMensaje,
        desbalanceo,
        funcionDeRondaPar,
        operacionCombinacion
      };
  }

  /**
   * El esquema para la liberación de memoria reservada de forma dinámica
   * es el mismo que para todas las redes Feistel: son los destructores de las
   * clases destino los encargados de liberar la memoria; en este caso, el
   * destructor de esta clase solamente libera el apuntador a la red Feistel
   * interna, mientras que los apuntadores a las operaciones de combinación
   * y de ronda son responsabilidad del destructor de la red Feistel.
   */

  template <typename tipo>
  FFX<tipo>::~FFX()
  {
    delete mRedFeistel;
  }

  /**
   * Simplemente llama a la operación de cifrado de la red Feistel interna.
   *
   * \return Arreglo con entrada cifrada.
   */

  template <typename tipo>
  Arreglo<tipo> FFX<tipo>::operar(
    const std::vector<Arreglo<tipo>> &entrada
  )
  {
    return mRedFeistel->operar(entrada);
  }

  /**
   * Simplemente llama a la operación de descifrado de la red Feistel interna.
   *
   * \return Arreglo con entrada descifrada.
   */

  template <typename tipo>
  Arreglo<tipo> FFX<tipo>::deoperar(
    const std::vector<Arreglo<tipo>> &entrada
  )
  {
    return mRedFeistel->deoperar(entrada);
  }
}

#endif
