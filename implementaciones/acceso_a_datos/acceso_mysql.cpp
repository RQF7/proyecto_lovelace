/*
 * \file
 * \brief
 */

#include "cabeceras/acceso_mysql.hh"
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <string>

using namespace sql;
using namespace std;

/**
 * Utiliza los parámetros dados para crear una nueva instancia de conexión
 * con la base de datos.
 */

AccesoMySQL::AccesoMySQL(
  string ip,              /**< Dirección ip del servidor de MySQL. */
  int puerto,             /**< Puerto del servidor de MySQL. */
  string usuario,         /**< Nombre de usuario. */
  string contrasenia,     /**< Contraseña. */
  string base             /**< Nombre de la base de datos. */
)
: mControlador {get_driver_instance()},
  mConexion {mControlador->connect("tcp://" + ip + ":" + puerto,
    usuario, contrasenia)}
{
  mConexion->setScema(base);
}

/**
 * Libera la instancia de la conexión. La ionstancia del controlador es
 * liberada por el propio conector.
 */

AccesoMySQL::~AccesoMySQL()
{
  delete mConexion;
}

/**
 *
 */
