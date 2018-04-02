/**
 * \file
 * \brief Declaración de la clase del cifrador BPS.
 *
 * Proyecto Lovelace.
 */

#ifndef __CIFRADOR_BPS__
#define __CIFRADOR_BPS__

#include "codificador.hh"
#include "../../utilidades/cabeceras/algoritmo_tokenizador_reversible.hh"
#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"

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
  /**
   * \brief
   *
   * Implementa la interfaz de un AlgoritmoTokenizadorReversible: tanto para
   * tokenizar como para detokenizar recibe el número de cuenta y el tweak.
   */

  class CifradorBPS
  : public AlgoritmoTokenizadorReversible
  {
    private:

      /** \brief Número de rondas internas. */
      unsigned int      mNumRondas;

      /** \brief Tipo de cifrado: AES o TDES. */
      unsigned int      mTipoCifrador;

      /** \brief Llave a ocupar en el cifrado y descifrado. */
      unsigned char* mLlave;

      /** \brief Vector con caracteres de alfabeto. */
      std::vector<char> mAlfabeto;

      /** \brief ¿Codificador? */
      Codificador       mCodificador;

    public:

      /** \brief Constructor de la clase. */
      CifradorBPS(std::vector<char> alfabeto, unsigned int numRondas);

      /** \brief Constructor de la clase con tipo de cifrador como argumento. */
      CifradorBPS(std::vector<char> alfabeto, unsigned int numRondas,
                                              unsigned int cifrador);

      /** \brief Constructor con alfabeto por defecto. */
      CifradorBPS(unsigned int numRondas, unsigned int cifrador,
        unsigned char* llave, std::vector<char> alfabeto =
        std::vector<char>{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});

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

    private:

      /** \brief Operación de tokenización (declarada por la interfaz). */
      ArregloDeDigitos tokenizar(
        const ArregloDeDigitos& numeroDeCuenta,
        const ArregloDeDigitos& tweak) override;

      /** \brief Operación de detokenización (declarada por la interfaz). */
      ArregloDeDigitos detokenizar(
        const ArregloDeDigitos& numeroDeCuenta,
        const ArregloDeDigitos& tweak) override;

  };
}

#endif
