/**
 * \file
 * \brief Declaración de clase de acceso base de datos de mysql.
 *
 * Proyecto Lovelace.
 */

#ifndef __ACCESO_MYSQL_PRUEBAS__
#define __ACCESO_MYSQL_PRUEBAS__

#include "bdp.hh"
#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <string>


  /**
   * \brief Implmentación de DAO para acceder a Mysql.
   *
   * Encapsula la conexión al servidor de MySQL.
   */

class AccesoMySQLPruebas : public BDP
{
  public:
    /** \brief Inicia la conexión con la base de datos. */
    AccesoMySQLPruebas(std::string ip = "127.0.0.1", int puerto = 3306,
      std::string usuario = "administrador_lovelace_pruebas",
      std::string contrasenia = "l0v3lac3-padmin",
      std::string base = "lovelace_pruebas");
    /** \brief Cierra la conexión con la base. */
    ~AccesoMySQLPruebas();

    /** \brief Elimina el registro con el identificador dado. */
    void registrarTiempoCifrado(
      const int algoritmo,
      const int tiempo,
      const int numTokenizaciones) override;

    /** \brief Elimina el registro con el identificador dado. */
    void registrarTiempoDescifrado(
      const int algoritmo,
      const int tiempo,
      const int numTokenizaciones) override;

  private:
    /** \brief Controlador de conexiones. */
    sql::Driver *mControlador;
    /** \brief Instancia de conexión. */
    sql::Connection *mConexion;
};

#endif
