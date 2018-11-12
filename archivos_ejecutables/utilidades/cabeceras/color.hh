/**
 * \file
 * \brief Hack para salida con colores.
 *
 * Proyecto Lovelace.
 */

#ifndef __COLOR__
#define __COLOR__

#include <iostream>

/**
 * \brief Enuemera el catálogo de colores.
 *
 * Relación entre colores y enteros ANSI necesarios para colocar color en
 * la salida estándar. Solo se toman en cuenta los colores de letra, no
 * los colores de fondo.
 *
 * Con «Original» se regresa al comportamiento normal.
 *
 * \sa https://en.wikipedia.org/wiki/ANSI_escape_code#graphics
 */

enum class Color {
  Negro     = 30,
  Rojo      = 31,
  Verde     = 32,
  Amarillo  = 33,
  Azul      = 34,
  Magenta   = 35,
  Cian      = 36,
  Blanco    = 37,
  Original  =  0,
};

/**
 * \brief Impresión en flujo de un color.
 *
 * Aplica la secuencia de caracteres ASCII necesaria para aplicar el
 * color dado en la salida estándar.
 * Permite hacer cosas como:
 * ```
 * cout << Color::Rojo << "¡Hola!" << Color::Original << endl;
 * cout << "bla, bla, bla..." << endl;
 * cout << Color::Verde << "¡Adiós!" << endl;
 * ```
 *
 * \note No todas las terminales soportan los colores. El comportamiento
 * real también depende de la configuración actual de la terminal (en mi
 * gnome-terminal) casi todo sale con escala de grises, excepto el rojo).
 *
 * \return Referencia a flujo dado.
 */

inline std::ostream& operator<<(
  std::ostream& flujo,              /**< Referencia a flujo. */
  const Color& color                /**< Color de salida. */
)
  { flujo << "\033[1;" << static_cast<int>(color) << "m"; return flujo; }

#endif
