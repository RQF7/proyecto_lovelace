/**
 * \file
 * \brief Declaración de funciones comunes relacionadas con números de tarjetas.
 */

#ifndef __UTILIDADES_TARJETAS__
#define __UTILIDADES_TARJETAS__

#include "../../../utilidades/cabeceras/arreglo.hh"

namespace Implementaciones
{

  /** \brief Cálculo dígito verificador del arreglo dado. */
  int algoritmoDeLuhn(const Arreglo<int>& entrada);

}

#endif
