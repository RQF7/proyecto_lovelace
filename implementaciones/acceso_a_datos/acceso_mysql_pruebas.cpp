/**
 * \file
 * \brief Implementación de acceso a base de datos de pruebas en MySQL.
 */

#include "cabeceras/acceso_mysql_pruebas.hh"
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
 * con la base de datos. El parámetro de base está dado por defecto y es
 * lovelace_pruebas.
 */

AccesoMySQLPruebas::AccesoMySQLPruebas(
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

AccesoMySQLPruebas::~AccesoMySQLPruebas()
{
  delete mConexion;
}

/**
 * Registra en la base de datos de pruebas el tiempo al algoritmo tokenizador
 * [algoritmo] hacer [numTokenizaciones] tokenizaciones. Los posibles valores
 * para los algoritmos están definidos mediante constantes en la cabecera.
 */
void AccesoMySQLPruebas::registrarTiempoCifrado(
  const int algoritmo,
  const int tiempo,
  const int numTokenizaciones
)
{
  string instruccion {"INSERT INTO desempenio_tokenizacion (algoritmo, tiempo, num_operaciones) VALUES (?, ?, ?)"};
  PreparedStatement* declaracion = mConexion->prepareStatement(instruccion);
  declaracion->setInt(1, algoritmo);
  declaracion->setInt(2, tiempo);
  declaracion->setInt(3, numTokenizaciones);
  declaracion->executeQuery();
  delete declaracion;
  return;
}

/**
 * Registra en la base de datos de pruebas el tiempo al algoritmo tokenizador
 * [algoritmo] hacer [numTokenizaciones] detokenizaciones. Los posibles valores
 * para los algoritmos están definidos mediante constantes en la cabecera.
 */
void AccesoMySQLPruebas::registrarTiempoDescifrado(
  const int algoritmo,
  const int tiempo,
  const int numTokenizaciones
)
{
  string instruccion {"INSERT INTO desempenio_detokenizacion (algoritmo, tiempo, num_operaciones) VALUES (?, ?, ?)"};
  PreparedStatement* declaracion = mConexion->prepareStatement(instruccion);
  declaracion->setInt(1, algoritmo);
  declaracion->setInt(2, tiempo);
  declaracion->setInt(3, numTokenizaciones);
  declaracion->executeQuery();
  delete declaracion;
  return;
}
