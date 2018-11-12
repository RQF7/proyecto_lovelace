/**
 * \file
 * \brief Declaración de pruebas para el codificador.
 *
 */

#ifndef __CODIFICADOR_PRUEBA__
#define __CODIFICADOR_PRUEBA__

#include "prueba.hh"

namespace UtilidadesPruebas
{
  /**
   * \brief
   */

  class CodificadorPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      CodificadorPrueba();

      /** \brief  */
      static bool probarBase64();

      /** \brief  */
      static bool probarBase32();

      /** \brief  */
      static bool probarBase16();
  };
}

#endif
