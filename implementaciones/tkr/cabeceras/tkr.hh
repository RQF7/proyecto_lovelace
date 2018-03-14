/**
 * \file
 * \brief Declaración de clase de TKR.
 */

#ifndef __TKR__
#define __TKR__

#include "pseudoaleatoria_trivial.hh"
#include "../../acceso_a_datos/cabeceras/cdv.hh"
#include "../../acceso_a_datos/cabeceras/acceso_simulado.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <vector>

namespace Implementaciones
{
  class TKR : public AlgoritmoTokenizador
  {
    public:

      using FuncionPseudoaleatoria =
        Utilidades::Funcion<Arreglo<tipo>, Arreglo<tipo>>;

      TKR(FuncionPseudoaleatoria* funcionPseudoaleatoria =
          new PseudoaleatoriaTrivial,
        CDV* baseDeDatos =
          new AccesoSimulado);

      ~TKR();

      Arreglo<int> cifrar(
        Arreglo<int> pan, Arreglo<int> informacionAdicional) override;

      Arreglo<int> descifrar(
        Arreglo<int> token, Arreglo<int> informacionAdicional) override;

    private:

      FuncionPseudoaleatoria *mFuncionPseudoaleatoria;

      CDV* mBaseDeDatos;
  };
}

#endif
