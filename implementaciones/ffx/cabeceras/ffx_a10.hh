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

#ifndef __FFX_A10__
#define __FFX_A10__

#include "arreglo.hh"
#include "combinacion_por_caracter.hh"
#include "funcion_con_inverso.hh"
#include "red_feistel.hh"
#include "red_feistel_alternante.hh"
#include "red_feistel_desbalanceada.hh"
#include "ronda_ffx_a10.hh"
#include <cmath>

namespace Implementaciones
{

  /**
   * \brief Implementación de FFX.
   *
   * \tparam tipo Tipo de dato con el que opera el algoritmo.
   */

  template <typename tipo>
  class FFXA10 : FuncionConInverso<Arreglo<tipo>, Arreglo<tipo>>
  {
    public:

      /** \brief Inicialización de parámetros de FFX. */
      FFXA10(unsigned char *llave, unsigned char *tweak, int tamanioTweak,
        int tamanioDeMensaje, int radix = 10);

      /** \brief Proceso de cifrado. */
      Arreglo<tipo> operar(
        const std::vector<Arreglo<tipo>> &entrada) override;

      /** \brief Proceso de descifrado. */
      Arreglo<tipo> deoperar(
        const std::vector<Arreglo<tipo>> &entrada) override;

    private:

      /** \brief */
      int mRadix;

      RondaFFXA10<tipo> mFuncionRondaPar;

      RondaFFXA10<tipo> mFuncionRondaImpar;

      CombinacionPorCaracter<tipo> mCombinacion;

      /** \brief Red Feistel. */
      RedFeistelAlternante<tipo> mRedFeistel;

  };

  /**
   * El desbalanceo por defecto es 0 (lo más cerca del centro posible).
   * El radix por defecto es 10: valor utilizado para el cifrado de dígitos.
   */

  template <typename tipo>
  FFXA10<tipo>::FFXA10(
    /** */
    unsigned char *llave,
    /** */
    unsigned char *tweak,
    /** */
    int tamanioTweak,
    /** Tamaño de las cadenas */
    int tamanioDeMensaje,
    /** Cardinalidad de alfabeto. */
    int radix
  )
  : mFuncionRondaPar
  {
      llave,
      tweak,
      tamanioTweak,
      1,
      1,
      radix,
      static_cast<int>(floor(tamanioDeMensaje / 2)),
      0,
      12
    },
    mFuncionRondaImpar
    {
      llave,
      tweak,
      tamanioTweak,
      1,
      1,
      radix,
      static_cast<int>(ceil(tamanioDeMensaje / 2)),
      0,
      12
    },
    mCombinacion {radix},
    mRedFeistel
    {
      12,
      tamanioDeMensaje,
      0,
      mFuncionRondaPar,
      mFuncionRondaImpar,
      mCombinacion
    }
  {
  }

  /**
   * \return Mensaje cifrado.
   */

  template <typename tipo>
  Arreglo<tipo> FFXA10<tipo>::operar(
    const std::vector<Arreglo<tipo>> &entrada    /**< Mensaje a cifrar. */
  )
  {
    return mRedFeistel.operar({entrada[0]});
  }

  /**
   * \return Mensaje descifrado.
   */

  template <typename tipo>
  Arreglo<tipo> FFXA10<tipo>::deoperar(
    const std::vector<Arreglo<tipo>> &entrada
  )
  {
    return mRedFeistel.deoperar({entrada[0]});
  }

}

#endif
