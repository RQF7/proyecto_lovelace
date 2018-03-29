/**
 * \file
 * \brief Implementación de pruebas de acceso a la base de datos.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/acceso_mysql.hh"
#include "cabeceras/acceso_mysql_prueba.hh"
#include "cabeceras/registro.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include <cppconn/exception.h>
#include <iostream>
#include <vector>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace sql;
using namespace std;

AccesoMySQLPrueba::AccesoMySQLPrueba()
: Utilidades::Prueba{"pruebas de acceso a MySQL"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Prueba inserciones y búsquedas",
    AccesoMySQLPrueba::probarAcceso
  });
}

/**
 * Verifica el acceso a la base: inserciones, búsquedas y eliminaciones.
 *
 * \return Estado de la prueba.
 */

bool AccesoMySQLPrueba::probarAcceso()
{
  AccesoMySQL acceso {};
  Registro registro {0, ArregloDeDigitos(12345ull), ArregloDeDigitos(67891ull)};
  acceso.guardar(registro);

  Registro pruebaUno = acceso.buscarPorPan(ArregloDeDigitos(12345ull));
  Registro pruebaDos = acceso.buscarPorToken(ArregloDeDigitos(67891ull));
  cout << "Prueba uno:" << endl << pruebaUno
       << "Prueba dos:" << endl << pruebaDos;

  if (pruebaUno.obtenerToken() != ArregloDeDigitos(67891ull) ||
    pruebaDos.obtenerPAN() != ArregloDeDigitos(12345ull))
    return false;

  acceso.eliminar(pruebaUno.obtenerIdentificador());
  try
  {
    Registro pruebaTres = acceso.buscarPorPan(ArregloDeDigitos(12345ull));
  }
  catch (SQLException &excepcion)
  {
    cout << "Prueba tres: " << excepcion.what() << endl;
    string resultado =
      "MySQL_Prepared_ResultSet::getInt: can't fetch because not on result set";
    if (excepcion.what() != resultado)
      return false;
  }

  return true;
}
