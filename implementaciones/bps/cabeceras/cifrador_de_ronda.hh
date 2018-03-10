/* ========================================================================= */
/* =========================== Cifrador De Ronda =========================== */
/* ======================================================================daz */

/**
 * Proyecto Lovelace.
 * 
 * \file
 * \brief Definición de la clase del cifrador de ronda.
 * 
 * \todo Mejor la clase para cifrar con otros cifradores por bloques.
 */

#ifndef CIFRADOR_DE_RONDA_H_
#define CIFRADOR_DE_RONDA_H_

#include <iostream>
#include <iomanip>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

/* ========================================================================= */

class CifradorDeRonda{

public:
  /** \brief Constructor de la clase sin argumentos. */
  CifradorDeRonda();

  /** \brief Método para obtener el tamaño de bloque del cifrador. */
  unsigned int getTamBloque();

  /** \brief Método para cifrar un mensaje con la llave dada. */
  std::string cifrar(std::string mensaje, CryptoPP::byte llave[]);

  /** \brief Método para descifrar un mensaje con la llave dada. */
  std::string descifrar(std::string mensaje, CryptoPP::byte llave[]);

};

/* ========================================================================= */

#endif
