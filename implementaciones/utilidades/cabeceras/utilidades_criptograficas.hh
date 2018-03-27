/**
 * \file
 * \brief Declaración de funciones comunes relacionadas con criptografía.
 */

#ifndef __UTILIDADES_CRIPTOGRAFICAS__
#define __UTILIDADES_CRIPTOGRAFICAS__

#include "../../../utilidades/cabeceras/arreglo.hh"

namespace Implementaciones
{

  /** \brief Genera una llave aleatoria de la longitud solicitada. */
  Arreglo<unsigned char> generarLlave(int longitud);

}

#endif
