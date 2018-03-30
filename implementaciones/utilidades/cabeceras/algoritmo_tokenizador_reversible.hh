/**
 * \file
 * \brief Declaración de un algoritmo tokenizador reversible.
 */

#ifndef __ALGORITMO_TOKENIZADOR_REVERSIBLE__
#define __ALGORITMO_TOKENIZADOR_REVERSIBLE__

#include "algoritmo_tokenizador.hh"
#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"

namespace Implementaciones
{
  /**
   * \brief Algoritmos tokenizadores reversibles.
   *
   * En esta clasificación se colocan los algoritmos que ocupan un esquema
   * criptográfico estándar: reciben un mensaje y un llave y entregan un
   * texto cifrado. A diferencia de los irreversibles (que ocupan una base de
   * datos para su operación) estos algoritmos solamente reciben el
   * identificador de la tarjeta
   */

  class AlgoritmoTokenizadorReversible : public AlgoritmoTokenizador
  {
    private:

      /** \brief Operación de tokenización intermedia
       *  (declarada por la interfaz). */
      ArregloDeDigitos tokenizarIntermedio(
        const ArregloDeDigitos& pan) override;

      /** \brief Operación de detokenización intermedia
       *  (declarada por la interfaz). */
      ArregloDeDigitos detokenizarIntermedio(
        const ArregloDeDigitos& token) override;

    protected:

      /** \brief Operación de tokenización abstracta para implementadores. */
      virtual ArregloDeDigitos tokenizar(
        const ArregloDeDigitos& identificadorDeCuenta) = 0;

      /** \brief Operación de detokenización abstracta para implementadores. */
      virtual ArregloDeDigitos detokenizar(
        const ArregloDeDigitos& identificadorDeCuenta) = 0;
  };
}

#endif
