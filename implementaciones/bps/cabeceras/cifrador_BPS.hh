/* ========================================================================= */
/* ============================== Cifrador BPS ============================= */
/* ======================================================================daz */

/**
 * Proyecto Lovelace.
 * 
 * \file
 * \brief Definición de la clase del cifrador BPS.
 * 
 */

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

#ifndef CIFRADOR_BPS_H_
#define CIFRADOR_BPS_H_

/* ========================================================================= */

class CifradorBPS{

private:
  std::vector<char> m_ALFABETO;      /* Alfabeto S. */
  unsigned int      m_NUM_RONDAS;    /* Numero de rondas w. */
  Codificador       m_codificador;

public:
  /** \brief Constructor de la clase. */
  CifradorBPS(std::vector<char> alfabeto, unsigned int num_rondas);

  /** \brief Método para cifrar un mensaje dada una llave y un tweak. */
  std::string cifrar(std::string mensaje, CryptoPP::byte llave[], 
                                                 mpz_class tweak);

  /** \brief Método para descifrar un mensaje dada una llave y un tweak. */
  std::string descifrar(std::string mensaje, CryptoPP::byte llave[], 
                                                    mpz_class tweak);

  /** \brief Método para obtener el alfabeto con que trabaja el cifrador. */
  std::vector<char> getAlfabeto();

  /** \brief Método para obtener el numero de rondas del cifrador. */
  unsigned int getNumRondas();

  /** \brief Método para cambiar el alfabeto con que trabaja el cifrador. */
  void setAlfabeto(std::vector<char> alfabeto);

  /** \brief Método para cambiar el numero de rondas del cifrador. */
  void setNumRondas(unsigned int num_rondas);

};

/* ========================================================================= */

#endif
