/**
 * \file
 * \brief Definición de la clase del cifrado BC.
 * Proyecto Lovelace.
 */

#ifndef __CIFRADOR_BC___
#define __CIFRADOR_BC___

#include "codificador.hh"
#include "cifrador_de_ronda.hh"
#include <iostream>
#include <iomanip>
#include <vector>
#include <gmpxx.h>
#include <gmp.h>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

namespace Implementaciones
{
  class CifradorBC
  {
    private:
      std::vector<char> mAlfabeto;             /* Alfabeto S. */
      unsigned int      mCardinalidad;         /* Cardinalidad s. */
      unsigned int      mTamBloque;            /* Tamaño de bloque b. */
      unsigned int      mNumRondas;            /* Número de rondas w. */
      Codificador       mCodificador;
      CifradorDeRonda   mCifradorDeRonda;      /* Cifrador de ronda F. */

    public:
      /** \brief Constructor de la clase sin argumentos. */
      CifradorBC();

      /** \brief Constructor de la clase con argumentos de alfabeto,
      tamaño de bloque y número de rondas. */
      CifradorBC(std::vector<char> alfabeto, unsigned int tamBloque,
                                             unsigned int numRondas);

      /** \brief Constructor de la clase con argumentos de alfabeto,
      tamaño de bloque, número de rondas y cifrado. */
      CifradorBC(std::vector<char> alfabeto, unsigned int tamBloque,
                      unsigned int numRondas, unsigned int cifrador);

      /** \brief Método para generar el número resultante de la
       *  composición de un mensaje en el dominio del alfabeto. */
      mpz_class componer(std::string mensaje);

      /** \brief Método para generar la cadena resultante de la
       *  descomposición de un número en el dominio del alfabeto. */
      std::string descomponer(mpz_class numMensaje, unsigned int longitud);

      /** \brief Método para cifrar un mensaje dada una llave y un tweak. */
      std::string cifrar(std::string mensaje, CryptoPP::byte llave[],
                                                     mpz_class tweak);

      /** \brief Método para descifrar un mensaje dada una llave y un tweak. */
      std::string descifrar(std::string mensaje, CryptoPP::byte llave[],
                                                        mpz_class tweak);

      /** \brief Método para obtener el alfabeto con que trabaja el cifrado. */
      std::vector<char> obtenerAlfabeto();

      /** \brief Método para obtener el tamaño de bloque del cifrado. */
      unsigned int obtenerTamBloque();

      /** \brief Método para obtener el numero de rondas del cifrado. */
      unsigned int obtenerNumRondas();

      /** \brief Método para obtener el cifrado de ronda interno. */
      CifradorDeRonda obtenerCifradorDeRonda();

      /** \brief Método para cambiar el alfabeto con que trabaja el cifrado. */
      void colocarAlfabeto(std::vector<char> alfabeto);

      /** \brief Método para cambiar el tamaño de bloque del cifrado. */
      void colocarTamBloque(unsigned int tamBloque);

      /** \brief Método para cambiar el numero de rondas del cifrado. */
      void colocarNumRondas(unsigned int numRondas);

      /** \brief Método para cambiar el tipo de cifrado F. */
      void colocarTipoCifrador(unsigned int tipo);

  };
}

/* ========================================================================= */

#endif
