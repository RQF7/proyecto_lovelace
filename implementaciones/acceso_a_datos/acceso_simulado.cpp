/**
 * \file
 * \brief Definción de clase de simulación de acceso a datos.
 */

#include "cabeceras/acceso_simulado.hh"
#include "cabeceras/registro.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"

using namespace Implementaciones;

/**
 * Simula que no se encuentra ningún registro con el PAN dado.
 * Para la mayoría de los posibles clientes esto es lo más útil.
 *
 * \return Registro vacío.
 */

Registro AccesoSimulado::buscarPorPan(
  const ArregloDeDigitos& PAN             /**< Número de tarjeta a buscar. */
)
{
  return Registro{0, PAN, {12345678ull}};
}

/**
 * Simula que sí se encontró el registro (el caso contrario debaría ser una
 * excepción en muchos usuarios).
 *
 * \return Registro con PAN e información asociada constantes.
 */

Registro AccesoSimulado::buscarPorToken(
  const ArregloDeDigitos& token            /**< Token a buscar. */
)
{
  return Registro{0, {12345678ull}, token};
}

/**
 * Bueno, como se trata de una simulación, aquí no se hace nada.
 */

void AccesoSimulado::guardar(
  const Registro& registro              /**< Registro a ignorar. */
)
{
}
