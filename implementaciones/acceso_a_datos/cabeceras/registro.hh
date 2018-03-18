/**
 * \file
 * \brief Declaración de clase de modelo de datos.
 */

#ifndef __REGISTRO__
#define __REGISTRO__

 #include "../../../utilidades/cabeceras/arreglo.hh"
 #include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
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
   * todos los métodos («setters» y «getter») son *inline*: se declaran y
   * definen en la cabecera.
   */

  class Registro
  {
    private:

      /** \brief Índice dentro de base de datos. */
      int mIdentificador;

      /** \brief Arreglo con el número de tarjeta. */
      entero mPAN;

      /** \brief Arreglo con el valor sustituto (token). */
      entero mToken;

      /** \brief Mes de caducidad [0, 11]. */
      int mMes;

      /** \brief Año de caducidad */
      int mAnio;

      /** \brief Código de seguridad. */
      int mCodigo;

    public:

      /** \brief Inicialización de miembros. */
      Registro(int identificador, entero pan, entero token,
        int anio = 0, int mes = 0, int codigo = 0)
      : mIdentificador {identificador}, mPAN {pan}, mToken {token},
         mMes {mes}, mAnio {anio}, mCodigo {codigo}
      {
      }

      /** \brief Regresa el identificador del registor. */
      inline int obtenerIdentificador() { return mIdentificador; }

      /** \brief Regresa el PAN de la estructura. */
      inline entero obtenerPAN() { return mPAN; }

      /** \brief Regresa el token de la estructura. */
      inline entero obtenerToken() { return mToken; }

      /** \brief Regresa el mes de caducidad. */
      inline int obtenerMes() { return mMes; }

      /** \brief Regresa el año de caducidad. */
      inline int obtenerAnio() { return mAnio; }

      /** \brief Regresa el código del registro. */
      inline int obtenerCodigo() { return mCodigo; }

      /** \brief Coloca el identificador del registro. */
      inline void colocarIdentificador(int identificador)
        { mIdentificador = identificador; }

      /** \brief Coloca el PAN en la estructura. */
      inline void colocarPAN(entero pan) { mPAN = pan; }

      /** \brief Coloca el token en la estructura. */
      inline void colocarToken(entero token) { mToken = token; }

      /** \brief Coloca el mes dado en la estructura. */
      inline void colocarMes(int mes) { mMes = mes; }

      /** \brief Coloca el año dado en la estructura. */
      inline void colocarAnio(int anio) { mAnio = anio; }

      /** \brief Coloca el código de seguridad en la estructura. */
      inline void colocarCodigo(int codigo) { mCodigo = codigo; }

      /** Función de impresión como amiga */
      friend std::ostream& operator<<(std::ostream &flujo,
        const Registro& registro);
  };

  /** \brief Imprimir registro en flujo. */
  inline std::ostream& operator<<(std::ostream &flujo,
    const Registro& registro){
    std::cout << "Identificador: " << registro.mIdentificador << std::endl
              << "PAN: " << registro.mPAN << std::endl
              << "Token: " << registro.mToken << std::endl
              << "Caducidad: "
              << registro.mMes << "/" << registro.mAnio << std::endl
              << "Código: " << registro.mCodigo << std::endl;
    return flujo;
  }
}

#endif
