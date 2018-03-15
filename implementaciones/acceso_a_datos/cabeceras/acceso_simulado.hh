/**
 * \file
 * \brief Declaración de clase de simulación de acceso a datos.
 */

#ifndef __ACCESO_SIMULADO__
#define __ACCESO_SIMULADO__

#include "cdv.hh"
#include "registro.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"

namespace Implementaciones
{
  /**
   * \brief Implementación trivial de un DAO.
   *
   * Permite simular la operación de un DAO. Con esta clase se pueden probar los
   * algoritmos dependientes sin tener que hacer el propio acceso a base de
   * datos a la par.
   */

  class AccesoSimulado : public CDV
  {
    public:
      /** \brief Busca el PAN dado en la base de datos. */
      Registro buscarPorPan(const Arreglo<int>& PAN) override;

      /** \brief Busca el token dado en la base de datos. */
      Registro buscarPorToken(const Arreglo<int>& token) override;

      /** \brief Guarda el registro dado en la base de datos. */
      void guardar(const Registro& registro) override;
  };
}

#endif
