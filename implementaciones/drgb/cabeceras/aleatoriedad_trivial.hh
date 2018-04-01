/**
 * \file
 * \brief Declaración de una fuente de aleatoriedad trivial.
 *
 * Proyecto Lovelace.
 */

#ifndef __ALEATORIEDAD_TRIVIAL__
#define __ALEATORIEDAD_TRIVIAL__

#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <fstream>
#include <string>
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Fuente de aleatoriedad que recibe entropía desde un archivo.
   *
   * Por defecto funciona leyendo bytes desde «/dev/random».
   */

  class AleatoriedadTrivial
  : public Utilidades::Funcion<Arreglo<unsigned char>, unsigned int>
  {
    public:

      /** \brief Contructor de fuente. */
      AleatoriedadTrivial(std::string nombreDeArchivo = "/dev/random");

      /** \brief Destructor de fuente. */
      ~AleatoriedadTrivial();

      /** \brief Operación de fuente. */
      Arreglo<unsigned char> operar(
        const std::vector<unsigned int>& entrada) override;

    private:

      /** \brief Flujo a archivo. */
      std::fstream mArchivo;
  };
}

#endif
