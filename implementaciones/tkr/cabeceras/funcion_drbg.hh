/**
 * \file
 * \brief Declaración de función que interactúa con DRBG, tipo TKR.
 *
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_DRBG__
#define __FUNCION_DRBG__

#include "../../drbg/cabeceras/drbg.hh"
#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"

namespace Implementaciones
{

  /**
   * \brief Equivalente de función RN con DRBG.
   *
   * Un intento de optimización con especto a la versión anterior (en donde el
   * equivalente se encontraba un nivel más abajo, junto con el
   * pseudoaleatorioAES).
   */

  class FuncionDRBG
  : public Utilidades::Funcion<ArregloDeDigitos, unsigned int>
  {
    public:

      /** \brief Inicialización de DRBG interno. */
      FuncionDRBG(DRBG *drbg);

      /** \brief Operación de función. */
      ArregloDeDigitos operar(const std::vector<unsigned int>& entrada) override;

    private:

      /** \brief Apuntador a generador pseudoaleatorio. */
      DRBG *mDrbg;
  };
}

#endif
