/**
 * \file
 * \brief Implementación de clase de TKR.
 */

#include "cabeceras/tkr.hh"
#include "../acceso_a_datos/cabeceras/registro.hh"
#include "../../utilidades/cabeceras/arreglo.hh"

using namespace Implementaciones;

TKR::TKR(
  FuncionPseudoaleatoria *funcionPseudoaleatoria,
  CDV* baseDeDatos
)
: mFuncionPseudoaleatoria {funcionPseudoaleatoria},
  mBaseDeDatos {baseDeDatos}
{
}

TKR::~TKR()
{
  delete mFuncionDeRonda;
  delete mBaseDeDatos;
}

Arreglo<int> TKR::cifrar(
  Arreglo<int> pan, Arreglo<int> informacionAdicional
)
{
  Registro informacion = mBaseDeDatos.buscarPorPan(pan);
  if (informacion.obtenerToken() == Arreglo<int>{})
  {
    informacion.colocarToken(mFuncionPseudoaleatoria.operar());
    informacion.guardar();
  }
  return informacion.obtenerToken();
}

Arreglo<int> TKR::descifrar(
  Arreglo<int> token, Arreglo<int> informacionAdicional
)
{
  Registro informacion = mBaseDeDatos.buscarPorToken(token);
  return informacion.obtenerPAN();
}
