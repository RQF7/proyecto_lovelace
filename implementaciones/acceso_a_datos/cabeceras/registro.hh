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
   * todos los métodos («setters» y «getter») son *inline*: se declaran y
   * definen en la cabecera.
   */

  class Registro
  {
    private:

      /** \brief Arreglo con el número de tarjeta. */
      Arreglo<int> mPAN;

      /** \brief Arreglo con el valor sustituto (token). */
      Arreglo<int> mToken;

      /** \brief Arreglo con la información asociada. */
      Arreglo<int> mInformacionAsociada;

    public:

      /** \brief Inicialización de miembros. */
      Registro(const Arreglo<int> &pan, const Arreglo<int> &token,
        const Arreglo<int> &informacionAsociada)
      : mPAN {pan}, mToken {token}, mInformacionAsociada {informacionAsociada}
      {
      }

      /** \brief Regresa el PAN de la estructura. */
      inline Arreglo<int> obtenerPAN() { return mPAN; }

      /** \brief Regresa el token de la estructura. */
      inline Arreglo<int> obtenerToken() { return mToken; }

      /** \brief Regresa la información asociada de la estructura, */
      inline Arreglo<int> obtenerInformacionAsociada() {
        return mInformacionAsociada; }

      /** \brief Coloca el PAN en la estructura. */
      inline void colocarPAN(const Arreglo<int>& pan) { mPAN = pan; }

      /** \brief Coloca el token en la estructura. */
      inline void colocarToken(const Arreglo<int>& token) { mToken = token; }

      /** \brief Coloca la información asociada en la estructura. */
      inline void colocarInformacionAsociada(
        const Arreglo<int>& informacionAsociada){
        mInformacionAsociada = informacionAsociada; }

      /** Función de impresión como amiga */
      friend std::ostream& operator<<(std::ostream &flujo,
        const Registro& registro);
  };

  /** \brief Imprimir registro en flujo. */
  inline std::ostream& operator<<(std::ostream &flujo,
    const Registro& registro){
    std::cout << "PAN: " << registro.mPAN << std::endl
              << "Token: " << registro.mToken << std::endl
              << "Información asociada: "
              << registro.mInformacionAsociada << std::endl;
    return flujo;
  }
}

#endif
