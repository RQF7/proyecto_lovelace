/**
 * \file
 * \brief Definición de la clase del cifrador BPS.
 * Proyecto Lovelace.
 */

#ifndef __CIFRADOR_BPS__
#define __CIFRADOR_BPS__

#include "codificador.hh"
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <gmpxx.h>
#include <gmp.h>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

namespace Implementaciones
{
  class CifradorBPS
  {
    private:
      std::vector<char> mAlfabeto;      /* Alfabeto S. */
      unsigned int      mNumRondas;     /* Número de rondas w. */
      Codificador       mCodificador;
      unsigned int      mTipoCifrador;

    public:
      /** \brief Constructor de la clase. */
      CifradorBPS(std::vector<char> alfabeto, unsigned int numRondas);

      /** \brief Constructor de la clase con tipo de cifrador como argumento. */
      CifradorBPS(std::vector<char> alfabeto, unsigned int numRondas,
                                              unsigned int cifrador);

      /** \brief Método para cifrar un mensaje dada una llave y un tweak. */
      std::string cifrar(std::string mensaje, CryptoPP::byte llave[],
                                                    mpz_class tweak);

      /** \brief Método para descifrar un mensaje dada una llave y un tweak. */
      std::string descifrar(std::string mensaje, CryptoPP::byte llave[],
                                                       mpz_class tweak);

      /** \brief Método para obtener el alfabeto con que trabaja el cifrador. */
      std::vector<char> obtenerAlfabeto();

      /** \brief Método para obtener el numero de rondas del cifrador. */
      unsigned int obtenerNumRondas();

      /** \brief Método para cambiar el alfabeto con que trabaja el cifrador. */
      void colocarAlfabeto(std::vector<char> alfabeto);

      /** \brief Método para cambiar el numero de rondas del cifrador. */
      void colocarNumRondas(unsigned int numRondas);

      /** \brief Método para cambiar el tipo de cifrador F. */
      void colocarTipoCifrador(unsigned int tipo);

  };
}

#endif
