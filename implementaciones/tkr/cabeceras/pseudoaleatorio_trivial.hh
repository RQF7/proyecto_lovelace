/**
 * \file
 * \brief Declaración de una función pseudoaleatoria temporal.
 */

#ifndef __PSEUDOALEATORIOA_TRIVIAL__
#define __PSEUDOALEATORIOA_TRIVIAL__

#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Imitación de una función pseudoaleatoria para generar tokens.
   *
   * No es criptográficamente segura; solo es para las pruebas. Para el esfuerzo
   * de escritura de esta clase, lo mismo daría que escribiera la de a verdad,
   * pero entonces no podría mostrar que TKR funciona con cualquier tipo
   * de función pseudoaleatoria.
   */

  class PseudoaleatorioTrivial
  : public Utilidades::Funcion<ArregloDeDigitos, int>
  {
    public:
      /** \brief Generación de token pseudoaleatorio trivial. */
      ArregloDeDigitos operar(const std::vector<int>& entrada) override;
  };
}

#endif
