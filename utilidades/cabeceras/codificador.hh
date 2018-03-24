/**
 * \file
 * \brief
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
   * \brief
   */

  class Codificador
  : public FuncionConInverso<std::string, Arreglo<unsigned char>>
  {
    public:

      /** \brief */
      enum class Base {Base64, Base32, Base16};

      /** \brief */
      Codificador(Base base = Base::Base64);

      /** \brief */
      ~Codificador();

      /** \brief */
      std::string operar(std::vector<Arreglo<unsigned char>>& entrada);

      /** \brief */
      Arreglo<unsigned char> deoperar(std::vector<std::string>& entrada);

    private:

      /** \brief */
      Base mBase;

      /** \brief */
      int mTopeOrigen;

      /** \brief */
      int mTopeDestino;

      /** \brief */
      unsigned char* mBufferOrigen;

      /** \brief */
      unsigned char* mBufferDestino;

      /** \brief */
      void codificarBuffers(std::string &cadena, int limite);

      /** \brief */
      void decodificarBuffers(Arreglo<unsigned char> &arreglo, int contador,
        int limite);

      /** \brief */
      void codificarBase64();

      /** \brief */
      void decodificarBase64();

      /** \brief */
      void codificarBase32();

      /** \brief */
      void decodificarBase32();

      /** \brief */
      void codificarBase16();

      /** \brief */
      void decodificarBase16();

      /** \brief */
      static const std::string mAlfabeto;
  };
}

#endif
