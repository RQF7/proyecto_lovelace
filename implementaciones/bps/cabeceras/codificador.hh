/* ========================================================================= */
/* ============================== Codificador ============================== */
/* ======================================================================daz */

/**
 * Proyecto Lovelace.
 * 
 * \file
 * \brief Definición de la clase del codificador.
 * 
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <gmpxx.h>
#include <gmp.h>

#ifndef CODIFICADOR_H_
#define CODIFICADOR_H_

/* ========================================================================= */

class Codificador{

private:
  std::vector<char> m_ALFABETO;

public:
  /** \brief Constructor de la clase sin argumentos. */
  Codificador();

  /** \brief Constructor de la clase con argumentos. */
  Codificador(std::vector<char> alfabeto);

  /** \brief Función para cambiar el alfabeto del codificador. */
  void setAlfabeto(std::vector<char> alfabeto);

  /** \brief Función para codificar un carácter. */
  char codificar(char c);

  /** \brief Función para decodificar un carácter. */
  char decodificar(char c);

  /** 
   * \brief Función para obtener la cadena de caracteres resultantes 
   * de la suma modular de las codificaciones de los caracteres de 
   * las cadenas dadas como argumento. 
   */
  std::string sumaMod(std::string cadena_a, std::string cadena_b);

  /** 
   * \brief Función para obtener la cadena de caracteres resultantes 
   * de la resta modular de las codificaciones de los caracteres de 
   * las cadenas dadas como argumento. 
   */
  std::string restaMod(std::string cadena_a, std::string cadena_b);

};

/* ========================================================================= */

#endif
