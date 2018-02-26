/**
 * \file
 * \brief Clase contenedor para funciones de prueba, utilidades
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_DE_PRUEBA__
#define __FUNCION_DE_PRUEBA__

#include <string>

/**
 * \brief Definición de un apuntador a función de prueba.
 *
 * Una función de prueba se define como una función que no recibe
 * parámetros, y que regresa un booleano: si se pasa o no la prueba.
 */

using apuntadorAFuncion = bool(*)(void);

/**
 * \brief Contenedor para funciones de prueba.
 *
 * Clase enteramente de datos que sirve para identificar a una función
 * de prueba.
 */

class FuncionDePrueba
{
  private:

    /** \brief Cadena que describe qué hace la función. */
    std::string mDescripcion;

    /** \brief Apuntador a función de prueba:
     *  sin argumentos, regresa booleano. */
    apuntadorAFuncion mFuncion;

  public:

    /** \brief Realiza la inicialización de los datos miembro. */
    FuncionDePrueba(
      std::string descripcion,    /**< Cadena que describe la función. */
      apuntadorAFuncion funcion   /**< Apuntador a función. */
    ) : mDescripcion {descripcion}, mFuncion {funcion} {}

    /** \brief Regresa la descripción de la función. */
    inline std::string obtenerDescripcion() const {return mDescripcion;}

    /** \brief Regresa el apuntador a la función. */
    inline apuntadorAFuncion obtenerFuncion() const {return mFuncion;}
};

#endif
