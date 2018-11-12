/**
 * \file
 * \brief Declaración de pruebas de AES.
 *
 * Proyecto Lovelace.
 */

#ifndef __AES_PRUEBA__
#define __AES_PRUEBA__

#include "../../../utilidades/cabeceras/prueba.hh"

namespace ImplementacionesPruebas
{
  /**
   * \brief Pruebas de AES.
   */

  class AESPrueba : public Utilidades::Prueba
  {
    public:
      /** \brief Registro de pruebas en vector de funciones. */
      AESPrueba();

      /** \brief Prueba cifrado y descifrado para AES de 128. */
      static bool probarAES128();

      /** \brief Prueba cifrado y descifrado para AES de 192. */
      static bool probarAES192();

      /** \brief Prueba cifrado y descifrado para AES de 256. */
      static bool probarAES256();
  };
}
#endif
