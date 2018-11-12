/**
 * \file
 * \brief Declaración de clase de acceso base de datos de pruebas en mysql.
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

/** Constante para algoritmo tokenizador BPS.*/
#define ID_BPS 1
/** Constante para algoritmo tokenizador TKR.*/
#define ID_TKR 2
/** Constante para algoritmo tokenizador FFX.*/
#define ID_FFX 3
/** Constante para algoritmo tokenizador AHR.*/
#define ID_AHR 4
/** Constante para algoritmo tokenizador DRBG.*/
#define ID_DRBG 5

namespace Implementaciones
{
  /**
   * \brief Implmentación de DAO para acceder a la base de datos de pruebas
  *   mediante MySQL.
   *
   * Encapsula la conexión al servidor de MySQL.
   */

  class AccesoMySQLPruebas : public BDP
  {
    public:
      /** \brief Inicia la conexión con la base de datos. */
      AccesoMySQLPruebas(std::string ip, int puerto,
        std::string usuario,
        std::string contrasenia,
        std::string = "lovelace_pruebas");

      /** \brief Cierra la conexión con la base. */
      ~AccesoMySQLPruebas();

      /** \brief Registra el tiempo de tokenización. */
      void registrarTiempoCifrado(
        const int algoritmo,
        const int tiempo,
        const int numTokenizaciones) override;

      /** \brief Registra el tiempo de detokenización. */
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
}

#endif
