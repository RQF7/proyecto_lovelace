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
 * \param entrada       Representación en arreglo del número de entrada.
 * \param ignorarUltimo Indica si se toma o no en cuenta el último elemento.
 *
 * \return Dígito verificador.
 */

int Implementaciones::algoritmoDeLuhn(
  const Arreglo<int>& entrada,
  bool ignorarUltimo
)
{
  int suma = 0;
  int inicio = (ignorarUltimo) ? 2 : 1;
  for (int i = entrada.obtenerNumeroDeElementos() - inicio, j = 0;
    i >= 0; i--, j++)
    suma += (j % 2 == 0)
      ? (modulo(entrada[i] * 2, 10) + (entrada[i] * 2 / 10))
      : entrada[i];
  return modulo(suma * 9, 10);
}
