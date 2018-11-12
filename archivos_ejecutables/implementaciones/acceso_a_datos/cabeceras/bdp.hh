/**
 * \file
 * \brief Declaración de interfaz de acceso a dao para pruebas.
 */

#ifndef __BDP__
#define __BDP__

#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include <string>

namespace Implementaciones
{
  /**
   * \brief Interfaz de acceso a los datos de pruebas.
   *
   * Definición de comunicación con una fuente de datos. Define las operaciones
   * que cualquier clase concreta de acceso a datos de pruebas debe de cumplir.
   */

  class BDP
  {
    public:
      /** \brief Destructor virtual. */
      virtual ~BDP()
      {
      }

      /** \brief Registra el tiempo de tokenización. */
      virtual void registrarTiempoCifrado(
        const int Algoritmo,
        const int tiempo,
        const int numTokenizaciones
      ) = 0;

      /** \brief Registra el tiempo de tokenización. */
      virtual void registrarTiempoDescifrado(
        const int Algoritmo,
        const int tiempo,
        const int numDetokenizaciones
      ) = 0;
  };
}

#endif
