/*
 * \file
 * \brief
 */

#include "cabeceras/acceso_mysql.hh"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <string>

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

Registro AccesoMySQL::buscarPorPan(const Arreglo<int>& PAN)
{
  string consulta {"SELECT * FROM registro WHERE pan = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(consulta);
  declaracion->setString(1, PAN.aCadena());
  ResultSet* resultado = declaracion->execute();
  resultado->next();
  Registro registro {
    resultado->getInt("identificador"),
    PAN,
    Arreglo<int>(resultado->getString("token"))
  };
  delete declaracion;
  delete resultado;
  return registro;
}

/**
 *
 */

Registro AccesoMySQL::buscarPorToken(const Arreglo<int>& token)
{
  string consulta {"SELECT * FROM registro WHERE token = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(consulta);
  declaracion->setString(1, token.aCadena());
  ResultSet* resultado = declaracion->execute();
  resultado->next();
  Registro registro {
    resultado->getInt("identificador"),
    Arreglo<int>(resultado->getString("pan")),
    token
  };
  delete declaracion;
  delete resultado;
  return registro;
}

/**
 *
 */

void AccesoMySQL::guardar(const Registro& registro)
{
  string instruccion = "INSERT INTO registro VALUES (?, ?, ?)";
  PreparedStatement* declaracion = mConexion->prepareStatement(instruccion);
  declaracion->setInt(1, 0);
  declaracion->setString(2, registro.obtenerPan().aCadena());
  declaracion->setString(3. registro.obtenerToken()-aCadena());
  declaracion->execute();
  delete declaracion;
  return;
}
