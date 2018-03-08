/**
 * \file
 * \brief Definición e implementación de FFX
 *
 * Fuera de la clase pero en el mismo espacio de nombres se declaran funciones
 * de suma y resta (por caracter y por bloque) para usar como argumentos en
 * la operación de combinación de la red Feistel. Estas funciones reciben
 * valores numéricos desde los argumentos del template (no de la función), para
 * que la firma siga sirviendo como argumento de la red Feistel (los alias
 * definidos ahí).
 *
 * \todo ¿Cómo hace esto el compilador? ¿Cuál es la diferencia entre un
 * argumento de template y uno de función?
 *
 * En cuanto a las implementaciones de las funciones, técnicamente ambas
 * versiones funcionan bien, sin embargo, la versión por bloques es más lenta
 * que la versión por caracter; esto porque la primera tiene que hacer
 * conversiones de número a arreglo y de arreglo a número.
 *
 * Proyecto Lovelace.
 */

#ifndef __FFX__
#define __FFX__

#include "arreglo.hh"
#include "red_feistel.hh"
#include "red_feistel_alternante.hh"
#include "red_feistel_desbalanceada.hh"

#include <cryptopp/aes.h>
#include <cryptopp/cbcmac.h>

namespace Implementaciones
{

  /**
   * \brief Implementación de FFX.
   *
   * \tparam tipo Tipo de dato con el que opera el algoritmo.
   */

  template <typename tipo>
  class FFX
  {
    public:

      /** \brief Enumera los tipos de redes Feistel. */
      enum class TipoDeRed {alternante, desbalanceada};

      /** \brief Enumera los tipos de suma. */
      enum class TipoDeSuma {porCaracter, porBloque};

      /** \brief Inicialización de parámetros de FFX. */
      FFX(unsigned char *llave, unsigned char *tweak, int tamanioTweak,
        int numeroDeRondas, int tamanioDeMensaje,
        int desbalanceo = 0, TipoDeRed tipoDeRed = TipoDeRed::alternante,
        TipoDeSuma tipoDeSuma = TipoDeSuma::porCaracter,
        funcionDeOperacion<tipo> funcionDeRonda = operacionTrivial<tipo>,
        funcionDeOperacion<tipo> funcionDeRondaImpar = nullptr, int radix = 10);

      /** \brief Proceso de cifrado. */
      Arreglo<tipo> cifrar(Arreglo<tipo> textoEnClaro);

      /** \brief Proceso de descifrado. */
      Arreglo<tipo> descifrar(Arreglo<tipo> textoCifrado);

    private:

      /** \brief */
      int mRadix;

      /** \brief Red Feistel. */
      RedFeistel<tipo> mRedFeistel = nullptr;

  };

  /**
   * El desbalanceo por defecto es 0 (lo más cerca del centro posible).
   * El radix por defecto es 10: valor utilizado para el cifrado de dígitos.
   */

  template <typename tipo>
  FFX<tipo>::FFX(
    /** */
    unsigned char *llave,
    /** */
    unsigned char *tweak,
    /** */
    int tamanioTweak,
    /** Número de rondas de la red Feistel subyacente. */
    int numeroDeRondas,
    /** Tamaño de las cadenas */
    int tamanioDeMensaje,
    /** Grado de desbalanceo */
    int desbalanceo,
    /** Tipo de red Feistel a ocupar. */
    TipoDeRed tipoDeRed,
    /** Tipo de suma a utilizar. */
    TipoDeSuma tipoDeSuma,
    /** Función ocupada en cada ronda. */
    funcionDeOperacion<tipo> funcionDeRonda,
    /** Función ocupada en rondas impares (solo para redes alternantes). */
    funcionDeOperacion<tipo> funcionDeRondaImpar,
    /** Cardinalidad de alfabeto. */
    int radix
  )
  {
    /* Instanciar funciones de suma y resta */
    funcionDeCombinacion<tipo> operadorSuma =
      (tipoDeSuma == TipoDeSuma::porBloque)
      ? sumaPorBloque<tipo, radix>
      : sumaPorCaracter<tipo, radix>;
    funcionDeCombinacion<tipo> operadorResta =
      (tipoDeSuma == TipoDeSuma::porBloque)
      ? restaPorBloque<tipo, radix>
      : restaPorCaracter<tipo, radix>;

    /* Crear función de ronda */
    funcionDeOperacion<tipo> funcionDeRondaTmp = funcionRondaCbcMacAes<tipo,
      llave, tweak, tamanioTweak, tipoDeRed, tipoDeSuma, radix,
      tamanioDeMensaje, desbalanceo, numeroDeRondas>;

    /* Instanciar red Feistel. */
    if (tipoDeRed == TipoDeRed::alternante)
      mRedFeistel = RedFeistelAlternante<tipo>{numeroDeRondas,
        tamanioDeMensaje, desbalanceo, funcionDeRondaTmp, funcionDeRondaTmp,
        operadorSuma, operadorResta};
    else
      mRedFeistel = RedFeistelDesbalanceada<tipo>{numeroDeRondas,
        tamanioDeMensaje, desbalanceo, funcionDeRondaTmp,
        operadorSuma, operadorResta};
  }

  /**
   * \return Mensaje cifrado.
   */

  template <typename tipo>
  Arreglo<tipo> FFX<tipo>::cifrar(
    Arreglo<tipo> textoEnClaro        /**< Mensaje a cifrar. */
  )
  {
    return mRedFeistel.cifrar(textoEnClaro);
  }

  /**
   * \return Mensaje descifrado.
   */

  template <typename tipo>
  Arreglo<tipo> FFX<tipo>::descifrar(
    Arreglo<tipo> textoCifrado        /**> Mensaje a descifrar. */
  )
  {
    return mRedFeistel.descifrar(textoCifrado);
  }

}

#endif
