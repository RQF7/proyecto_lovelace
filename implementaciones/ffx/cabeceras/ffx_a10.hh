/**
 * \file
 * \brief Parámetros FFX A10.
 * Proyecto Lovelace.
 */

#ifndef __FFX_A10__
#define __FFX_A10__

#include "ffx.hh"
#include "ronda_ffx_a10.hh"
#include "../../redes_feistel/cabeceras/red_feistel.hh"
#include "../../redes_feistel/cabeceras/red_feistel_alternante.hh"
#include "../../redes_feistel/cabeceras/red_feistel_desbalanceada.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"
#include <cmath>

namespace Implementaciones
{

  /**
   * \brief Colección de parámetros A10.
   *
   * Clase que simplifica la interfaz de FFX definiendo valores propios
   * que permiten trabajar con cadenas de dígitos. Corresponden a los
   * parámetros especificados en la especificación del algoritmo.
   */

  template <typename tipo /**< Tipo de dato con el que se opera. */>
  class FFXA10 : public FFX<tipo>
  {
    public:

      /** \brief Inicialización de parámetros de FFX A10. */
      FFXA10(unsigned char *llave, unsigned char *tweak,
        unsigned int tamanioTweak, unsigned int tamanioDeMensaje);
  };

  /**
   * Todo el punto de esta clase se encuentra en la lista de inicialización:
   * se trata de la instanciación de los parámetros de FFX según la
   * colección A10.
   *
   * \note Se que la determinación del número de rondas dependiendo del tamaño
   * de los mensajes en la lista de inicialización resulta un tanto repetitiva,
   * sin embargo, de momento no encuentro otra forma de expresarlo: lo más
   * lógico es definir un entero miembro e inicializarlo primero;
   * lamentablemente son las clases base las que se inicializan antes que la
   * propia, por lo que hacer eso tendría un comportamiento raro (probablemente
   * se ocuparía el valor por defecto de un entero).
   */

  template <typename tipo>
  FFXA10<tipo>::FFXA10(
    /** Llave para la función de ronda. */
    unsigned char *llave,
    /** Tweak para la función de ronda. */
    unsigned char *tweak,
    /** Tamaño del tweak dado. */
    unsigned int tamanioTweak,
    /** Tamaño de los mensajes a procesar. */
    unsigned int tamanioDeMensaje
  )
  : FFX<tipo>{
    /* Cardinalidad (radix). */
    10u,
    tamanioDeMensaje,
    FFX<tipo>::TipoDeCombinacion::porCaracter,
    FFX<tipo>::TipoDeRed::alternante,
    /* Desbalanceo. */
    0,
    /* Número de rondas (dependen de el tamaño del mensaje). */
    (tamanioDeMensaje <= 5) ? 24u :
    (tamanioDeMensaje <= 9) ? 18u :
    12u,

    /* Función de ronda par. */
    new RondaFFXA10<tipo>{
      llave,
      tweak,
      tamanioTweak,
      static_cast<int>(FFX<tipo>::TipoDeCombinacion::porCaracter),
      static_cast<int>(FFX<tipo>::TipoDeRed::alternante),
      /* Cardinalidad (radix). */
      10,
      tamanioDeMensaje,
      /* Posición del split (el desbalanceo es 0). */
      static_cast<int>(floor(tamanioDeMensaje / 2.0)),
      /* Número de rondas (dependen de el tamaño del mensaje). */
      (tamanioDeMensaje <= 5) ? 24u :
      (tamanioDeMensaje <= 9) ? 18u :
      12u},

    /* Función de ronda impar. */
    new RondaFFXA10<tipo>{
      llave,
      tweak,
      tamanioTweak,
      static_cast<int>(FFX<tipo>::TipoDeCombinacion::porCaracter),
      static_cast<int>(FFX<tipo>::TipoDeRed::alternante),
      /* Cardinalidad (radix). */
      10u,
      tamanioDeMensaje,
      /* Posición del split (el desbalanceo es 0). */
      static_cast<int>(ceil(tamanioDeMensaje / 2.0)),
      /* Número de rondas (dependen de el tamaño del mensaje). */
      (tamanioDeMensaje <= 5) ? 24u :
      (tamanioDeMensaje <= 9) ? 18u :
      12u}
    }
  {
  }

}

#endif
