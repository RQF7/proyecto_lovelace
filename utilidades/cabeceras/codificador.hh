/**
 * \file
 * \brief Declaración de codificador.
 *
 * Proyecto Lovelace.
 */

#ifndef __CODIFICADOR__
#define __CODIFICADOR__

#include "arreglo.hh"
#include "../interfaces_comunes/funcion_con_inverso.hh"
#include <string>
#include <vector>

namespace Utilidades
{
  /**
   * \brief Codificador de datos binarios en base 64, 32 o 16.
   *
   * Implementación de un codificador/decodificador de datos binarios en
   * base 64, 32 0 16. Dentro de los límites razonablas para una
   * implementación de uso interno, se sigue lo establecido en el RFC 4648
   * (v. gr. se excluyen las verificaciones de seguridad, dado que tanto la
   * entrada como la salida los controla esta aplicación).
   *
   * Tanto base64 como base32 necesitan un caracter espceial de *padding* para
   * la correcta decodificación de los datos (un «=»); base16 no lo necesita.
   *
   * Esta clase es una implementación de una FuncionConInverso que recibe un
   * un arreglo de bytes y regresa una cadena codificada. La decodificación
   * invierte los tipos de entrada y salida.
   *
   * \todo Arreglar operación de los paddings para la base 32. Hay una
   * excepción de acceso ilegal.
   *
   * \sa https://tools.ietf.org/html/rfc4648
   */

  class Codificador
  : public FuncionConInverso<std::string, Arreglo<unsigned char>>
  {
    public:

      /** \brief Enumera las posibles bases. */
      enum class Base {Base64, Base32, Base16};

      /** \brief Nueva instancia de codificador. */
      Codificador(Base base = Base::Base64);

      /** \brief Destructor de codificador. */
      ~Codificador();

      /** \brief */
      std::string operar(
        const std::vector<Arreglo<unsigned char>>& entrada) override;

      /** \brief */
      Arreglo<unsigned char> deoperar(
        const std::vector<std::string>& entrada) override;

    private:

      /** \brief Tipo de base para codificar/decodificar. */
      Base mBase;

      /** \brief Indica el tamaño del buffer de origen. */
      int mTopeOrigen;

      /** \brief Indica el tamaño del buffer de destino. */
      int mTopeDestino;

      /** \brief Memoria para bytes de origen. */
      unsigned char* mBufferOrigen;

      /** \brief Memoria para bytes de destino. */
      unsigned char* mBufferDestino;

      /** \brief Apuntador a función de codificación. */
      void (Codificador::*mFuncionCodificacion)();

      /** \brief Apuntador a función de decodificación. */
      void (Codificador::*mFuncionDecodificacion)();

      /** \brief Operación interna de codificación. */
      void codificarBuffers(std::string &cadena, int limite);

      /** \brief Operación interna de decodificación. */
      void decodificarBuffers(Arreglo<unsigned char> &arreglo, int contador,
        int limite);

      /** \brief Codificación en base 64 mediante corrimientos de bits. */
      void codificarBase64();

      /** \brief Decodificación en base 64 mediante corrimientos de bits. */
      void decodificarBase64();

      /** \brief Codificación en base 32 mediante corrimientos de bits. */
      void codificarBase32();

      /** \brief Decodificación en base 32 mediante corrimientos de bits. */
      void decodificarBase32();

      /** \brief Codificación en base 16 mediante corrimientos de bits. */
      void codificarBase16();

      /** \brief Decodificación en base 16 mediante corrimientos de bits. */
      void decodificarBase16();

      /** \brief Alfabeto para el texto codificado. */
      static const std::string mAlfabeto;
  };
}

#endif
