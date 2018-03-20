/**
 * \file
 * \brief Prueba de las utilidades matemáticas.
 * Proyecto Lovelace.
 */

#ifndef __ARREGLO_DE_DIGITOS_PRUEBA__
#define __ARREGLO_DE_DIGITOS_PRUEBA__

#include "prueba.hh"

namespace UtilidadesPruebas
{
  /**
   * \brief Pruebas de las operaciones por caracter.
   */

  class ArregloDeDigitosPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Regitro de pruebas en vector de funciones. */
      ArregloDeDigitosPrueba();

      /** \brief Prueba los contructores. */
      static bool probarConstructores();
  };
}

#endif
