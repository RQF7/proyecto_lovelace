/**
 * \file
 * \brief Definición de la clase del codificador.
 *
 * Proyecto Lovelace.
 */

#ifndef __CODIFICADOR__
#define __CODIFICADOR__

#include <iostream>
#include <iomanip>
#include <vector>
#include <gmpxx.h>
#include <gmp.h>

class Codificador
{
  private:
    std::vector<char> mAlfabeto;

  public:
    /** \brief Constructor de la clase sin argumentos. */
    Codificador();

    /** \brief Constructor de la clase con argumentos. */
    Codificador(std::vector<char> alfabeto);

    /** \brief Función para cambiar el alfabeto del codificador. */
    void colocarAlfabeto(std::vector<char> alfabeto);

    /** \brief Función para codificar un carácter. */
    char codificar(char c);

    /** \brief Función para decodificar un carácter. */
    char decodificar(char c);

    /** \brief Función para obtener la cadena de caracteres resultantes
     *  de la suma modular de las codificaciones de los caracteres de
     *  las cadenas dadas como argumento. */
    std::string sumaMod(std::string cadenaA, std::string cadenaB);

    /** \brief Función para obtener la cadena de caracteres resultantes
     *  de la resta modular de las codificaciones de los caracteres de
     *  las cadenas dadas como argumento. */
    std::string restaMod(std::string cadenaA, std::string cadenaB);

    /* Me parece que los anteriores son demasiado largos para tratarse de
     * resúmenes. */
};

#endif
