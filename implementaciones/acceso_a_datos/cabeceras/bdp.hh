/**
 * \file
 * \brief Declaración de interfaz de acceso a dao.
 */

#ifndef __BDP__
#define __BDP__

#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include <string>

  /**
   * \brief Interfaz de acceso a los datos de pruebas.
   *
   * Definición de comunicación con una fuente de datos. Define las operaciones
   * que cualquier clase concreta de acceso a datos debe de cumplir. Todo el
   * código del espacio de implementaciones debe utilizar esta interfaz.
   */

class BDP
{
  public:
    /** \brief Destructor virtual. */
    virtual ~BDP()
    {
    }

    /** \brief Guarda el registro dado en la base de datos. */
    virtual void registrarTiempoCifrado(
      const int Algoritmo,
      const int tiempo,
      const int numTokenizaciones
    ) = 0;

    /** \brief Guarda el registro dado en la base de datos. */
    virtual void registrarTiempoDescifrado(
      const int Algoritmo,
      const int tiempo,
      const int numDetokenizaciones
    ) = 0;
};

#endif
