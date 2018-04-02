/**
 * \file
 * \brief Implementación de clase de TKR.
 */

#include "cabeceras/tkr.hh"
#include "../utilidades/cabeceras/utilidades_tarjetas.hh"
#include "../acceso_a_datos/cabeceras/registro.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../utilidades/cabeceras/utilidades_matematicas.hh"
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

ArregloDeDigitos TKR::tokenizar(
  const ArregloDeDigitos& pan                   /**< Número de tarjeta. */
)
{
  Registro informacion = mBaseDeDatos->buscarPorPan(pan);
  if (informacion.obtenerToken() == Arreglo<int>{})
  {
    auto division = pan
      / Arreglo<unsigned int>{6, pan.obtenerNumeroDeElementos() - 1};
    ArregloDeDigitos temporal =
      mFuncionPseudoaleatoria->operar(
        {static_cast<ArregloDeDigitos>(division[1]).obtenerNumeroDeElementos()});
    temporal = static_cast<ArregloDeDigitos>(division[0]) || temporal;
    informacion.colocarToken(temporal
      || ArregloDeDigitos{modulo(algoritmoDeLuhn(temporal) + 1, 10)});
    informacion.colocarPAN(pan);
    mBaseDeDatos->guardar(informacion);
  }
  return informacion.obtenerToken();
}

/**
 * Proceso de detokenización. Simplemente busca en la base de datos el
 * PAN asociado al token dado.
 *
 * \return PAN asociado al token dado.
 */

ArregloDeDigitos TKR::detokenizar(
  const ArregloDeDigitos& token             /** Token (generado previamente). */
)
{
  Registro informacion = mBaseDeDatos->buscarPorToken(token);
  if (informacion.obtenerPAN() == Arreglo<int>{})
    throw TokenInexistente{"El token no está en la base de datos."};
  return informacion.obtenerPAN();
}
