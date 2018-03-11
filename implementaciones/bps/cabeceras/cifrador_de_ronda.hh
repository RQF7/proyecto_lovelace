/**
 * \file
 * \brief Definición de la clase del cifrador de ronda.
 *
 * \todo Mejor la clase para cifrar con otros cifradores por bloques.
 * Proyecto Lovelace.
 */

#ifndef __CIFRADOR_DE_RONDA__
#define __CIFRADOR_DE_RONDA__

#include <iostream>
#include <iomanip>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

class CifradorDeRonda
{
  public:
    /** \brief Constructor de la clase sin argumentos. */
    CifradorDeRonda();

    /** \brief Método para obtener el tamaño de bloque del cifrador. */
    unsigned int obtenerTamBloque();

    /** \brief Método para cifrar un mensaje con la llave dada. */
    std::string cifrar(std::string mensaje, CryptoPP::byte llave[]);

    /** \brief Método para descifrar un mensaje con la llave dada. */
    std::string descifrar(std::string mensaje, CryptoPP::byte llave[]);
};

#endif
