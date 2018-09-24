/**
 * \file
 * \brief Declaración de clase de acceso base de datos de mysql.
 *
 * Proyecto Lovelace.
 */

#ifndef __ACCESO_MYSQL__
#define __ACCESO_MYSQL__

#include "cdv.hh"
#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
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
        std::string base = "lovelace_cdv",
        int cliente_id = 0,
        std::string estadoDeToken_id = "actual");

      /** \brief Cierra la conexión con la base. */
      ~AccesoMySQL();

      /** \brief Busca el PAN dado en la base de datos. */
      Registro buscarPorPan(const ArregloDeDigitos& PAN) override;

      /** \brief Busca el token dado en la base de datos. */
      Registro buscarPorToken(const ArregloDeDigitos& token) override;

      /** \brief Guarda el registro dado en la base de datos. */
      void guardar(const Registro& registro) override;

      /** \brief Elimina el registro con el identificador dado. */
      void eliminar(int identificador) override;

      /** \brief Obtiene el valor del contador. */
      entero obtenerContador(std::string nombre) override;

      /** virtual Coloca el valor del contador. */
      void colocarContador(std::string nombre, entero valor) override;

      /** \brief Actualiza el identificador del cliente. */
      void actualizarCliente_id(int cliente_id) override;

      /** \brief Actualiza el valor del estado del token. */
      void actualizarEstadoDelToken_id(std::string estadoToken_id) override;

    private:
      /** \brief Controlador de conexiones. */
      sql::Driver *mControlador;

      /** \brief Instancia de conexión. */
      sql::Connection *mConexion;

      /** \brief Identificador del cliente. */
      int mClienteId;

      /** \brief Estado del token. */
      std::string mEstadoDeTokenId;
  };
}

#endif
