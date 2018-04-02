/**
 * \file
 * \brief Declaración de un algoritmo tokenizador reversible.
 */

#ifndef __ALGORITMO_TOKENIZADOR_IRREVERSIBLE__
#define __ALGORITMO_TOKENIZADOR_IRREVERSIBLE__

#include "algoritmo_tokenizador.hh"
#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"

namespace Implementaciones
{
  /**
   * \brief Algoritmos tokenizadores irreversibles.
   *
   * En esta clasificación se colocan los algoritmos que ocupan una base de
   * datos para su operación; por esta razón (a diferencia de los reversibles)
   * estos algoritmos reciben el PAN o el token compleltos.
   */

  class AlgoritmoTokenizadorIrreversible : public AlgoritmoTokenizador
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
        const ArregloDeDigitos& pan) = 0;

      /** \brief Operación de detokenización abstracta para implementadores. */
      virtual ArregloDeDigitos detokenizar(
        const ArregloDeDigitos& token) = 0;
  };
}

#endif
