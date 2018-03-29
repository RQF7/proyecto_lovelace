/**
 * \file
 * \brief Declaración de clase de TKR.
 */

#ifndef __TKR__
#define __TKR__

#include "pseudoaleatorio_trivial.hh"
#include "../../acceso_a_datos/cabeceras/cdv.hh"
#include "../../acceso_a_datos/cabeceras/acceso_simulado.hh"
#include "../../utilidades/cabeceras/algoritmo_tokenizador.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Algoritmo tokenizador TKR
   *
   * Los únicos datos que necesita para operar son una referencia al DAO (el
   * acceso a los datos, el acceso al «card data vault») y una referencia a
   * la función pseudoaleatoria usada para generar tokens.
   */

  class TKR : public AlgoritmoTokenizador
  {
    public:

      /** \brief Alias para la función pseudoaleatoria. */
      using FuncionPseudoaleatoria =
        Utilidades::Funcion<ArregloDeDigitos, unsigned int>;

      /* \brief Constructor de instancia. */
      TKR(FuncionPseudoaleatoria* funcionPseudoaleatoria =
          new PseudoaleatorioTrivial,
        CDV* baseDeDatos =
          new AccesoSimulado);

      /** \brief Libearación de memoria. */
      ~TKR();

      /** \brief El token dado no existe. */
      struct TokenInexistente : public Utilidades::Error {
        inline TokenInexistente(std::string mensaje)
        : Utilidades::Error{mensaje} {}};

    private:

      /** \brief Apuntador a una función pseudoaleatoria. */
      FuncionPseudoaleatoria *mFuncionPseudoaleatoria;

      /** \brief Apuntador a una clase de acceso a datos. */
      CDV* mBaseDeDatos;

      /** Operación de tokenización (declarada por la interfaz). */
      ArregloDeDigitos tokenizar(const ArregloDeDigitos& pan) override;

      /** Operación de detokenización (declarada por la interfaz). */
      ArregloDeDigitos detokenizar(const ArregloDeDigitos& token) override;
  };
}

#endif
