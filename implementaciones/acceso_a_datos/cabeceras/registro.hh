/**
 * \file
 * \brief Declaración de clase de modelo de datos.
 */

#ifndef __REGISTRO__
#define __REGISTRO__

 #include "../../../utilidades/cabeceras/arreglo.hh"
 #include <ostream>

namespace Implementaciones
{
  /**
   * \brief Representación de tupla PAN-token-información asociada.
   *
   * Al momento de escribir esto, esta el la única clase del modelo de datos
   * para el programa tokenizador. Un registro tiene un arreglo de enteros
   * que representan al PAN, un arreglo de enteros que representan al token
   * corresponiente y un arreglo que representa a la información asociada.
   *
   * Al tratarse de una clase de solo datos (lo que en java llaman «bean»),
   * todos los métodos («setters» y «getters») son *inline*: se declaran y
   * definen en la cabecera.
   */

  class Registro
  {
    private:

      /** \brief Índice dentro de base de datos. */
      int mIdentificador;

      /** \brief Arreglo con el número de tarjeta. */
      Arreglo<int> mPAN;

      /** \brief Arreglo con el valor sustituto (token). */
      Arreglo<int> mToken;

    public:

      /** \brief Inicialización de miembros. */
      Registro(int identificador, Arreglo<int> pan, Arreglo<int> token)
      : mIdentificador {identificador}, mPAN {pan}, mToken {token}
      {
      }

      /** \brief Regresa el identificador del registor. */
      inline int obtenerIdentificador() { return mIdentificador; }

      /** \brief Regresa el PAN de la estructura. */
      inline Arreglo<int> obtenerPAN() { return mPAN; }

      /** \brief Regresa el token de la estructura. */
      inline Arreglo<int> obtenerToken() { return mToken; }

      /** \brief Coloca el identificador del registro. */
      inline void colocarIdentificador(int identificador)
        { mIdentificador = identificador; }

      /** \brief Coloca el PAN en la estructura. */
      inline void colocarPAN(const Arreglo<int>& pan) { mPAN = pan; }

      /** \brief Coloca el token en la estructura. */
      inline void colocarToken(const Arreglo<int> &token) { mToken = token; }

      /** Función de impresión como amiga */
      friend std::ostream& operator<<(std::ostream &flujo,
        const Registro& registro);
  };

  /** \brief Imprimir registro en flujo. */
  inline std::ostream& operator<<(std::ostream &flujo,
    const Registro& registro){
    std::cout << "Identificador: " << registro.mIdentificador << std::endl
              << "PAN: " << registro.mPAN << std::endl
              << "Token: " << registro.mToken << std::endl;
    return flujo;
  }
}

#endif
