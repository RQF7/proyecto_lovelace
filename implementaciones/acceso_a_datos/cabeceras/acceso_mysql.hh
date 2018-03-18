/**
 * \file
 * \brief Declaración de clase de acceso base de datos de mysql.
 *
 * Proyecto Lovelace.
 */

#ifndef __ACCESO_MYSQL__
#define __ACCESO_MYSQL__

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <string>

namespace Implementaciones
{
  /**
   * \brief Implmentación de DAO para acceder a Mysql.
   *
   * Encapsula la conexión al servidor de MySQL.
   */

  class AccesoMySQL : public CDV
  {
    public:
      /** \brief Inicia la conexión con la base de datos. */
      AccesoMySQL(std::string ip = "127.0.0.1", int puerto = 3306,
        std::string usuario = "administrador_lovelace_cdv",
        std::string contrasenia = "l0v3lac3-admin",
        std::string base = "lovelace_cdv");

      /** \brief Cierra la conexión con la base. */
      ~AccesoMySQL();

      /** \brief Busca el PAN dado en la base de datos. */
      Registro buscarPorPan(entero PAN) override;

      /** \brief Busca el token dado en la base de datos. */
      Registro buscarPorToken(entero token) override;

      /** \brief Guarda el registro dado en la base de datos. */
      void guardar(const Registro& registro) override;

    private:
      /** \brief Controlador de conexiones. */
      sql::Driver *mControlador;

      /** \brief Instancia de conexión. */
      sql::Connection *mConexion;
  };
}

#endif
