/**
 * \file
 * \brief Declaración de clase abstracta de algoritmo tokenizador.
 */

#ifndef __ALGORITMO_TOKENIZADDOR__
#define __ALGORITMO_TOKENIZADDOR__

#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../../utilidades/cabeceras/error.hh"
#include "../../../utilidades/interfaces_comunes/funcion_con_inverso.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Estándar de interfaz para un algoritmo tokenizador.
   *
   * Un algoritmo tokenizador es cualquier cosa que implemente los dos métodos
   * puramente abstractos de esta clase. El algoritmo tokenizador es a su vez
   * una función con inverso; la implementación que se hace de operar y deoperar
   * es simplemente una construcción alrededor de tokenizarIntermedio y
   * descifrarIntermedio.
   *
   * Los métodos puramente abstractos llevan el sufijo de «intermedio» dado
   * que (salvo ocasiones extrañas) no son implementados por un algoritmo
   * tokenizador concreto, sino que son implementados por las clasificaciones
   * de estos (reversibles e irreversibles). Esta clase solamente se encarga
   * de proveer una interfaz común a todos los algoritmos tokenizadores y
   * de hacer validaciones de entradas.
   */

  class AlgoritmoTokenizador
  : public Utilidades::FuncionConInverso<ArregloDeDigitos, ArregloDeDigitos>
  {
    public:

      /** \brief Operación de tokenización. */
      ArregloDeDigitos operar(
        const std::vector<ArregloDeDigitos> &entrada) override;

      /** \brief Operación de detokenización. */
      ArregloDeDigitos deoperar(
        const std::vector<ArregloDeDigitos> &entrada) override;

      /** \brief Error para representar formatos inválidos. */
      struct TarjetaMalFormada : public Utilidades::Error
        { inline TarjetaMalFormada(std::string mensaje)
          : Utilidades::Error{mensaje} {} };

    protected:

      /** \brief Operación de tokenización abstracta para implementadores. */
      virtual ArregloDeDigitos tokenizarIntermedio(
        const ArregloDeDigitos& entrada) = 0;

      /** \brief Operación de detokenización abstracta para implementadores. */
      virtual ArregloDeDigitos detokenizarIntermedio(
        const ArregloDeDigitos& entrada) = 0;

    private:

      /** \brief Valida el token o el PAN dados. */
      void validarEntrada(const ArregloDeDigitos& arreglo,
        int desfaseDeDigitoVerificador = 0);
  };
}

#endif
