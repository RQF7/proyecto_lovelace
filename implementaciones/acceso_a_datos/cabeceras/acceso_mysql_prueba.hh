/**
 * \file
 * \brief Declaración de pruebas con acceso a base de datos.
 *
 * Proyecto Lovelace.
 */

#ifndef __ACCESO_MYSQL_PRUEBA__
#define __ACCESO_MYSQL_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas de acceso a base de datos de MySQL.
   */

  class AccesoMySQLPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      AccesoMySQLPrueba();

      /** \brief Prueba de la operación de redistribución. */
      static bool probarAcceso();
  };
}

#endif
