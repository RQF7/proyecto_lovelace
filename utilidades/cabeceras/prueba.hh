/**
 * \file
 * \brief Superclase de todas las pruebas, declaración.
 * Proyecto Lovelace.
 */

#ifndef __PRUEBA__
#define __PRUEBA__

#include <vector>
#include "funcion_de_prueba.hh"

namespace Utilidades
{
  /**
   * \brief Superclase común a todas las pruebas.
   *
   * Agrupa un conjunto de funciones booleanas que prueban el funcionamiento
   * del código.
   */

  class Prueba
  {
    public:

      /** \brief Nueva instancia de pruebas. */
      inline Prueba(std::string mensaje) : mMensaje {mensaje} {}

      /** \brief Ejecuta todas las pruebas registradas en la lista de pruebas. */
      bool probar();

      /** \brief Regresa el mensaje para la bitácora. */
      inline std::string obtenerMensaje() const { return mMensaje; }

      /** \brief Regresa el tamaño del vector. */
      inline int obtenerNumeroDePruebas() const
        { return mListaDePruebas.size(); }

    protected:

      /** \brief Lista de funciones de prueba. */
      std::vector<FuncionDePrueba> mListaDePruebas;

    private:

      /** \brief Título del conjunto de pruebas agrupadas. */
      std::string mMensaje;
  };
}

#endif
