/**
 * \file
 * \brief Definición de funciones comunes relacionadas con números de tarjetas.
 */

#include "cabeceras/utilidades_tarjetas.hh"
#include "../../utilidades/cabeceras/utilidades_matematicas.hh"

using namespace Implementaciones;

/**
 * Implementación del algoritmo de Luhn.
 *
 * \return Dígito verificador.
 */

int Implementaciones::algoritmoDeLuhn(
  /** Representación en arreglo del número de entrada */
  const Arreglo<int>& entrada
)
{
  int suma = 0;
  for (int i = entrada.obtenerNumeroDeElementos() - 1, j = 0; i >= 0; i--, j++)
    suma += (j % 2 == 0)
      ? (modulo(entrada[i] * 2, 10) + (entrada[i] * 2 / 10))
      : entrada[i];
  return modulo(suma * 9, 10);
}
