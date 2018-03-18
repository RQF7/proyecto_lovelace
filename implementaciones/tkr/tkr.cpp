/**
 * \file
 * \brief Implementación de clase de TKR.
 */

#include "cabeceras/tkr.hh"
#include "../acceso_a_datos/cabeceras/registro.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <iostream>

using namespace Implementaciones;
using namespace std;

/**
 * Inicialización de parámetros.
 */

TKR::TKR(
  FuncionPseudoaleatoria *funcionPseudoaleatoria, /**< Apuntador a función
                                                   *   pseudoaleatoria. */
  CDV* baseDeDatos                                /**< Apuntador a acceso a
                                                   *   base de datos. */
)
: mFuncionPseudoaleatoria {funcionPseudoaleatoria},
  mBaseDeDatos {baseDeDatos}
{
}

/**
 * Libera la memoria a la que apuntan los dats miembro.
 */

TKR::~TKR()
{
  delete mFuncionPseudoaleatoria;
  delete mBaseDeDatos;
}

/**
 * Proceso para generar un token a partir de un número de tarjeta. Primero
 * se busca en la base de datos, si ya hay un token para el número dado, es
 * este el que se regresa; sino, se crea uno (y se inserta en la base) con la
 * función pseudoaleatoria.
 *
 * \return Token asociado al PAN dado.
 */

Arreglo<int> TKR::tokenizar(
  const Arreglo<int>& pan                   /**< Número de tarjeta. */
)
{
  Registro informacion = mBaseDeDatos->buscarPorPan(pan);
  if (informacion.obtenerToken() == Arreglo<int>{})
  {
    auto temporal = mFuncionPseudoaleatoria->operar({});
    informacion.colocarToken(temporal);
    mBaseDeDatos->guardar(informacion);
  }
  return informacion.obtenerToken();
}

/**
 * Proceso de detokenización. Simplemente busca en la base de datos el
 * PAN asociado al token dado.
 *
 * \return PAN asociado al token dado.
 *
 * \todo Lanzar excepción en caso de búsqueda infructuosa.
 */

Arreglo<int> TKR::detokenizar(
  const Arreglo<int>& token                 /** Token (generado previamente). */
)
{
  Registro informacion = mBaseDeDatos->buscarPorToken(token);
  return informacion.obtenerPAN();
}
