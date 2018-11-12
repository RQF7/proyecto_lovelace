/**
 * \file
 * \brief Declaración de clase de simulación de acceso a datos.
 *
 * Proyecto Lovelace.
 */

#ifndef __ACCESO_SIMULADO__
#define __ACCESO_SIMULADO__

#include "cdv.hh"
#include "registro.hh"
#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include <string>

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
      Registro buscarPorPan(const ArregloDeDigitos& PAN) override;

      /** \brief Busca el token dado en la base de datos. */
      Registro buscarPorToken(const ArregloDeDigitos& token) override;

      /** \brief Guarda el registro dado en la base de datos. */
      void guardar(const Registro& registro) override;

      /** \brief Simula la eliminación de un registro. */
      void eliminar(int identificador) override;

      /** \brief Obtiene el valor del contador. */
      inline entero obtenerContador(std::string nombre) override
      {
        return 0;
      }

      /** virtual Coloca el valor del contador. */
      inline void colocarContador(std::string nombre, entero valor) override
      {
      }

      /** virtual Coloca el valor del contador. */
      inline void actualizarCliente_id(int cliente_id) override
      {
      }

      /** virtual Coloca el valor del contador. */
      inline void actualizarEstadoDelToken_id(std::string estadoDeToken_id) override
      {
      }
  };
}

#endif
