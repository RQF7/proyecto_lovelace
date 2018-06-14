/**
 * \file
 * \brief Declaración de una fuente de aleatoriedad desde hardware.
 *
 * Proyecto Lovelace.
 */

#ifndef __ALEATORIEDAD_HARDWARE__
#define __ALEATORIEDAD_HARDWARE__

#include <cryptopp/rdrand.h>
#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"

namespace Implementaciones
{
  /**
   * \brief Fuente de aleatoriedad que recibe entropía desde hardware.
   *
   * Utiliza la implementación de cryptopp RDSEED.
   */

  class AleatoriedadHardware
  : public Utilidades::Funcion<Arreglo<unsigned char>, unsigned int>
  {
    public:

      /** \brief Contructor de fuente. */
      AleatoriedadHardware();

      /** \brief Destructor de fuente. */
      ~AleatoriedadHardware();

      /** \brief Operación de fuente. */
      Arreglo<unsigned char> operar(
        const std::vector<unsigned int>& entrada) override;

      /** \brief Error; no hay entropía por hardware implementada. */
      struct SinEntropiaPorHardware : public Utilidades::Error
      { inline SinEntropiaPorHardware(std::string mensaje)
        : Utilidades::Error{mensaje} {} };

    private:

      /** \brief Envoltura de instrucciones de intel. */
      CryptoPP::RDSEED mGenerador;
  };
}

#endif
