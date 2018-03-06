/* ========================================================================= */
/* ============================== Cifrador BC ============================== */
/* ======================================================================daz */

/**
 * Proyecto Lovelace.
 * 
 * \file
 * \brief Definición de la clase del cifrador BC.
 * 
 */

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

#ifndef CIFRADOR_BC_H_
#define CIFRADOR_BC_H_

/* ========================================================================= */

class CifradorBC{

private:
  std::vector<char> m_ALFABETO;            /* Alfabeto S. */
  unsigned int      m_CARDINALIDAD;        /* Cardinalidad s. */
  unsigned int      m_TAM_BLOQUE;          /* Tamaño de bloque b. */
  unsigned int      m_NUM_RONDAS;          /* Numero de rondas w. */
  Codificador       m_codificador;
  CifradorDeRonda   m_CIFRADOR_DE_RONDA;   /* Cifrador de ronda F. */

public:
  /** \brief Constructor de la clase sin argumentos. */
  CifradorBC();

  /** \brief Constructor de la clase con argumentos. */
  CifradorBC(std::vector<char> alfabeto, unsigned int tam_bloque, 
                                         unsigned int num_rondas);

  /** 
   * \brief Método para generar el numero resultante de la 
   * composición de un mensaje en el dominio del alfabeto. 
   */
  mpz_class componer(std::string mensaje);

  /** 
   * \brief Método para generar la cadena resultante de la 
   * descomposición de un numero en el dominio del alfabeto. 
   */
  std::string descomponer(mpz_class num_mensaje, unsigned int longitud);

  /** \brief Método para cifrar un mensaje dada una llave y un tweak. */
  std::string cifrar(std::string mensaje, CryptoPP::byte llave[], 
                                                 mpz_class tweak);

  /** \brief Método para descifrar un mensaje dada una llave y un tweak. */
  std::string descifrar(std::string mensaje, CryptoPP::byte llave[], 
                                                    mpz_class tweak);

  /** \brief Método para obtener el alfabeto con que trabaja el cifrador. */
  std::vector<char> getAlfabeto();

  /** \brief Método para obtener el tamaño de bloque del cifrador. */
  unsigned int getTamBloque();

  /** \brief Método para obtener el numero de rondas del cifrador. */
  unsigned int getNumRondas();

  /** \brief Método para obtener el cifrador de ronda interno. */
  CifradorDeRonda getCifradorDeRonda();

  /** \brief Método para cambiar el alfabeto con que trabaja el cifrador. */
  void setAlfabeto(std::vector<char> alfabeto);

  /** \brief Método para cambiar el tamaño de bloque del cifrador. */
  void setTamBloque(unsigned int tam_bloque);

  /** \brief Método para cambiar el numero de rondas del cifrador. */
  void setNumRondas(unsigned int num_rondas);

};

/* ========================================================================= */

#endif
