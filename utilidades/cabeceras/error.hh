/**
 * \file
 * \brief Declaración de clase base para excepciones.
 */

#ifndef __ERROR_H__
#define __ERROR_H__

#include "color.hh"
#include <iostream>
#include <exception>
#include <string>

namespace Utilidades
{
  /**
   * \brief Clase base para todas las excpeciones.
   *
   * Mantiene un mensaje como dato miembro, da manera que sirva como
   * indicador del error. Al momento de la construcción se imprime en
   * la salida de errores estándar este mensaje.
   */

  class Error : std::exception
  {
    public:
      /** \brief Nueva instancia de error. */
      inline Error(std::string mensaje) : mMensaje { mensaje }
        { std::cerr << *this; }

    private:
      /** \brief Mensaje de error. */
      std::string mMensaje;

      /** \brief Función de impresión amiga. */
      friend std::ostream &operator<<(std::ostream &flujo, const Error &error);
  };

  /** \brief Definición de función de impresión. */
  inline std::ostream &operator<<(std::ostream &flujo, const Error &error)
    { flujo << Color::Rojo << error.mMensaje
            << Color::Original << std::endl; return flujo; }
}

#endif
