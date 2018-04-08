/**
 * \file
 * \brief Declaración de clase PseudoaleatorioDRBG.
 *
 * De tan trivial que es, se encuentra definida por completo con miembros
 * inline.
 *
 * Proyecto Lovelace.
 */

#ifndef __PSEUDOALEATORIO_DRBG__
#define __PSEUDOALEATORIO_DRBG__

#include "drbg.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Generación de número pseudoaleatorio usando un DRBG
   *
   * Por sí solo un DRBG ya es para crear números pseudoaleatorios (por lo que
   * la existencia de esta clase es un poco superflua). La idea es que funciones
   * de forma equivalente a PseudoaleatorioAES y sea usada como función interna
   * para la FuncionRN (que a su vez es ocupada dentro de TKR).
   */

  class PseudoaleatorioDRBG
  : public Utilidades::Funcion<Arreglo<unsigned char>, entero>
  {
    public:

      /** \brief Construcción de nueva instancia. */
      inline PseudoaleatorioDRBG(DRBG *drbg) : mDrbg {drbg} {}

      /** \brief Comunicación con DRBG. */
      inline Arreglo<unsigned char> operar(
        const std::vector<entero>& entrada) override
        { return mDrbg->operar({entrada[0]}); }

    private:

      /** \brief Apuntador a DRBG subyacente. */
      DRBG *mDrbg;
  };
}

#endif
