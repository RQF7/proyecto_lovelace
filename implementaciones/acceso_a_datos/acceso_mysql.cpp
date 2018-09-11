/**
 * \file
 * \brief Implementación de acceso a base de datos en MySQL.
 */

#include "cabeceras/acceso_mysql.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../utilidades/cabeceras/utilidades_matematicas.hh"
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
 * Busca registros por el PAN dado. Regresa la primera coincidencia (en una
 * base consistente, la única); si no hay, regresa un registro vacío.
 *
 * \return Instancia de Registro con información de base de datos.
 */

Registro AccesoMySQL::buscarPorPan(
  const ArregloDeDigitos& PAN       /**< PAN a buscar en los registros. */
)
{
  string consulta {"SELECT * FROM programa_tokenizador_token WHERE pan = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(consulta);
  declaracion->setString(1, PAN.obtenerCadena());
  ResultSet* resultado = declaracion->executeQuery();
  Registro registro {};
  if (resultado->next())
  {
    registro.colocarIdentificador(resultado->getInt("id"));
    registro.colocarPAN(PAN);
    registro.colocarToken(ArregloDeDigitos{resultado->getString("token")});
  }
  delete declaracion;
  delete resultado;
  return registro;
}

/**
 * Busca registros por el token dado. Regresa la primera coincidencia (en una
 * base comsistente, la única); si no hay coincidencias regresa un registro
 * vacío.
 *
 * \return Instancia de Registro con información de base de datos.
 */

Registro AccesoMySQL::buscarPorToken(
  const ArregloDeDigitos& token         /**< Token a buscar. */
)
{
  string consulta {"SELECT * FROM programa_tokenizador_token "
    "WHERE token = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(consulta);
  declaracion->setString(1, token.obtenerCadena());
  ResultSet* resultado = declaracion->executeQuery();
  Registro registro {};
  if (resultado->next())
  {
    registro.colocarIdentificador(resultado->getInt("id"));
    registro.colocarPAN(ArregloDeDigitos(resultado->getString("pan")));
    registro.colocarToken(token);
  }
  delete declaracion;
  delete resultado;
  return registro;
}

/**
 * Guarda el registro dado el base de datos. No hace ningún tipo de comprobacón
 * de duplicados: el token se inserta como viene; lo mismo para el PAN y el
 * token.
 *
 * TODO: El usuario y el tipo de token asignados son triviales; actualizar
 * interfaz para que se reciban desde los argumentos.
 */

void AccesoMySQL::guardar(
  const Registro& registro              /**< Nuevo registro. */
)
{
  string instruccion {"INSERT INTO programa_tokenizador_token (id, token, pan) "
    "VALUES (?, ?, ?)"};
  PreparedStatement* declaracion = mConexion->prepareStatement(instruccion);
  declaracion->setInt(1, 0);
  declaracion->setString(2, registro.obtenerToken().obtenerCadena());
  declaracion->setString(3, registro.obtenerPAN().obtenerCadena());
  declaracion->executeQuery();
  delete declaracion;
  return;
}

/**
 * Elimina el registor que coincida con el identificador dado.
 */

void AccesoMySQL::eliminar(
  int identificador         /**< Identificador de registro a eliminar. */
)
{
  string instruccion {"DELETE FROM programa_tokenizador_token "
    "WHERE id = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(instruccion);
  declaracion->setInt(1, identificador);
  declaracion->executeQuery();
  delete declaracion;
  return;
}

/**
 * Consulta en la base de datos el valor del contador solicitado.
 *
 * \return Valor de contador.
 */

entero AccesoMySQL::obtenerContador(
  std::string nombre                  /**< Nombre del contador en la base. */
)
{
  string instruccion {"SELECT * FROM programa_tokenizador_contador "
    "WHERE nombre = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(instruccion);
  declaracion->setString(1, nombre);
  ResultSet* resultado = declaracion->executeQuery();
  resultado->next();
  entero valor {resultado->getUInt64("valor")};
  delete resultado;
  delete declaracion;
  return valor;
}

/**
 * Guarda en el contador dado el valor dado.
 */

void AccesoMySQL::colocarContador(
  std::string nombre,               /**< Nombre del contador en la base. */
  entero valor                      /**< Valor a guardar. */
)
{
  string instruccion {"UPDATE programa_tokenizador_contador "
    "SET valor = ? WHERE nombre = ?"};
  PreparedStatement* declaracion = mConexion->prepareStatement(instruccion);
  declaracion->setUInt64(1, valor);
  declaracion->setString(2, nombre);
  declaracion->executeQuery();
  delete declaracion;
  return;
}
