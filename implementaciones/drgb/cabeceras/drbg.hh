/**
 * \file
 * \brief Declaración de un DRGB.
 *
 * Proyecto Lovelace.
 */

#ifndef __DRGB__
#define __DRGB__

#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/cabeceras/error.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Generado de bits pseudoaleatorios.
   *
   * Implementación de un generador de bits pseudoaleatorios (DRGB) de acuerdo
   * a la (recomendación 800-90A del NIST)[]. El estándar especifíca el
   * generador en términos de 5 funciones:
   *
   * * Instanciación (el contructor).
   * * Generación de bits (operar).
   * * Cambio de semilla (cambiarSemilla).
   * * Desinstanciacion (desinstanciar).
   * * Prueba de salud (probarSalud).
   */

  class DRBG : public Funcion<,unsigned int>
  {
    public:

      /**
       * \brief Niveles de seguridad soportados.
       *
       * El nivel representa la máxima seguridad que pueden solicitar
       * los clientes.
       */

      enum class NivelDeSeguridad
      {
        nivel112 = 112,
        nivel128 = 128,
        nivel192 = 192,
        nivel256 = 256
      };

      /** \brief Construcción de una nueva instancia. */
      DRBG(FuenteDeAleatoriedad fuenteDeAlatoriedad,
        std::string cadenaDePersonalizacion = "",
        NivelDeSeguridad nivelDeSeguridad = NivelDeSeguridad::nivel112);

      /** \brief Liberación de memoria. */
      ~DRGB();

      /** \brief Función generadora de bits pseudoaleatorios. */
      operar(const std::vector<unsigned int>& entrada) override;

      /** \brief */
      cambiarSemilla();

      /** \brief */
      desinstanciar();

      /** \brief */
      probarSalud();

      /** \brief Error para representar una fuerza de seguiridad no soportada.*/
      struct FuerzaNoSoportada : public Utilidades::Error
      { inline FuerzaNoSoportada(std::string mensaje)
        : Utilidades::Error{mensaje} {} };

    private:

      /** \brief */
      FuenteDeAleatoriedad fuenteDeAlatoriedad;

      /** \brief Nivel de seguridad soportado por la instancia. */
      NivelDeSeguridad mNivelDeSeguridad;

      /** \brief Contador de peticiones desde la última instanciación de la
       *  semilla. */
      unsigned int mContadorDePeticiones;

      /** \brief Especifica la vida útil de una semilla. */
      unsigned int mMaximoDePeticiones;

      /** \brief */
      Arreglo<unsigned int> mSemilla;
  };
}

#endif
