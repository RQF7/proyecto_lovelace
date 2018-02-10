/*
 * Super clase de todas las pruebas, declaración.
 * Proyecto Lovelace.
 */

#ifndef __PRUEBA__
#define __PRUEBA__

#include <vector>
#include "funcion_de_prueba.hh"

/**
 * \brief Superclase común a todas las pruebas.
 *
 * Agrupa un conjunto de funciones booleanas que prueban el funcionamiento
 * del código.
 */

class Prueba
{
  public:

    /** \brief Ejecuta todas las pruebas registradas en la lista de pruebas. */
    bool probar();

  protected:

    /** \brief Lista de funciones de prueba. */
    std::vector<FuncionDePrueba> mListaDePruebas;
};

#endif
