/**
 * \file
 * \brief
 */

#include "cabeceras/acceso_mysql.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <iostream>

using namespace Implementaciones;
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
  mConexion {mControlador->connect("tcp://" + ip + ":" + to_string(puerto),
    usuario, contrasenia)}
{
  mConexion->setSchema(base);
}

/**
 * Libera la instancia de la conexión. La instancia del controlador es
 * liberada por el propio conector.
 */

AccesoMySQL::~AccesoMySQL()
{
  delete mConexion;
}

/**
 *
 */

Registro AccesoMySQL::buscarPorPan(
  const ArregloDeDigitos& PAN
)
{
  string consulta {"SELECT * FROM registro WHERE pan = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(consulta);
  declaracion->setString(1, PAN.obtenerCadena());
  ResultSet* resultado = declaracion->executeQuery();
  resultado->next();
  Registro registro {
    resultado->getInt("identificador"),
    PAN,
    ArregloDeDigitos(resultado->getString("token"))
  };
  delete declaracion;
  delete resultado;
  return registro;
}

/**
 *
 */

Registro AccesoMySQL::buscarPorToken(
  const ArregloDeDigitos& token
)
{
  string consulta {"SELECT * FROM registro WHERE token = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(consulta);
  declaracion->setString(1, token.obtenerCadena());
  ResultSet* resultado = declaracion->executeQuery();
  resultado->next();
  Registro registro {
    resultado->getInt("identificador"),
    ArregloDeDigitos(resultado->getString("pan")),
    token
  };
  delete declaracion;
  delete resultado;
  return registro;
}

/**
 *
 */

void AccesoMySQL::guardar(
  const Registro& registro
)
{
  string instruccion {"INSERT INTO registro VALUES (?, ?, ?)"};
  PreparedStatement* declaracion = mConexion->prepareStatement(instruccion);
  declaracion->setInt(1, 0);
  declaracion->setString(2, registro.obtenerPAN().obtenerCadena());
  declaracion->setString(3, registro.obtenerToken().obtenerCadena());
  declaracion->executeQuery();
  delete declaracion;
  return;
}

/**
 *
 */

void AccesoMySQL::eliminar(
  int identificador
)
{
  string instruccion {"DELETE FROM registro WHERE identificador = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(instruccion);
  declaracion->setInt(1, identificador);
  declaracion->executeQuery();
  delete declaracion;
  return;
}
