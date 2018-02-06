/*
 * Clase contenedor para funciones de prueba, utilidades
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_DE_PRUEBA__
#define __FUNCION_DE_PRUEBA__

#include <string>

using apuntadorAFuncion = bool(*)(void);

class FuncionDePrueba
{
  private:
    std::string mDescripcion;
    apuntadorAFuncion mFuncion;

  public:
    FuncionDePrueba(std::string descripcion, apuntadorAFuncion funcion)
      : mDescripcion {descripcion}, mFuncion {funcion} {}
    inline std::string obtenerDescripcion() const {return mDescripcion;}
    inline apuntadorAFuncion obtenerFuncion() const {return mFuncion;}
};

#endif
