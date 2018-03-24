/**
 * \file
 * \brief Declaración de clase de conjunto de pruebas.
 */

#ifndef __CONJUNTO_DE_PRUEBAS__
#define __CONJUNTO_DE_PRUEBAS__

#include "prueba.hh"
#include <string>
#include <vector>

namespace Utilidades
{
  /**
   * \brief Clase deshechable para suite de pruebas.
   *
   * Encapsula la ejecución de un conjunto de pruebas.
   */

  class ConjuntoDePruebas
  {
    public:
      /** \brief Construye y ejecuta la suite de pruebas. */
      [[noreturn]]
      ConjuntoDePruebas(std::string mensaje, std::vector<Prueba>);
  };
}

#endif
