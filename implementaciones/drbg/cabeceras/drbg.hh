/**
 * \file
 * \brief Declaración de un DRBG.
 *
 * Proyecto Lovelace.
 */

#ifndef __DRBG__
#define __DRBG__

#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/cabeceras/error.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Generador de bits pseudoaleatorios.
   *
   * Implementación de un generador de bits pseudoaleatorios (DRBG) de acuerdo
   * a la
   * [recomendación 800-90A del NIST](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-90Ar1.pdf).
   * El estándar especifíca el generador en términos de 5 funciones:
   *
   * * Instanciación (el contructor).
   * * Generación de bits (operar).
   * * Cambio de semilla (cambiarSemilla).
   * * Desinstanciacion (desinstanciar).
   * * Prueba de salud (probarSalud).
   *
   * Esta clase define el comportamiento genérico de cualquier generador. Para
   * obtener un generador concreto es necesario implementar la operación
   * generarBytes.
   *
   * \sa HashDRBG y CTRDRBG.
   */

  class DRBG
  : public Utilidades::Funcion<Arreglo<unsigned char>, entero>
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

      /**
       * \brief Interfaz requerida para una fuente de aleatoriedad.
       *
       * Se le mandan parámetros mediante enteros sin signo y se espera recibir
       * arreglos de bytes (la entropía).
       */

      using FuenteDeAleatoriedad =
        Utilidades::Funcion<Arreglo<unsigned char>, unsigned int>;

      /** \brief Función generadora de bits pseudoaleatorios. */
      Arreglo<unsigned char>
        operar(const std::vector<entero>& entrada) override;

      /** \brief Error para representar una fuerza de seguiridad no soportada.*/
      struct FuerzaNoSoportada : public Utilidades::Error
      { inline FuerzaNoSoportada(std::string mensaje)
        : Utilidades::Error{mensaje} {} };

      /** \brief Error para representar una cadena de personzalización
       *  demasiado grande. */
      struct PersonalizacionDemasiadoGrande : public Utilidades::Error
      { inline PersonalizacionDemasiadoGrande(std::string mensaje)
        : Utilidades::Error{mensaje} {} };

    protected:

      /** \brief Construcción de una nueva instancia. */
      DRBG(FuenteDeAleatoriedad *fuenteDeAlatoriedad,
        Arreglo<unsigned char> cadenaDePersonalizacion,
        NivelDeSeguridad nivelDeSeguridad,
        unsigned int longitudSemila, entero longitudPersonalizacion,
        entero longitudMaxima, entero maximoDePeticiones);

      /** \brief Función de cambio de semilla. */
      virtual void cambiarSemilla();

      /** \brief Función para eliminar información crítica. */
      virtual void desinstanciar();

      /** \brief Apuntador a clase-función que genera entropía. */
      FuenteDeAleatoriedad *mFuenteDeAlatoriedad;

      /** \brief Cadena opcional de personalización. */
      Arreglo<unsigned char> mCadenaDePersonalizacion;

      /**
       * \brief Nivel de seguridad soportado por la instancia.
       *
       * Forma parte de lo que en el NIST llaman «información administrativa»
       * (que a su vez es parte del estado interno del generador). Este valor
       * no es crítico: la seguridad no depende de que se mantenga en secreto
       * o no.
       */

      NivelDeSeguridad mNivelDeSeguridad;

      /**
       * \brief Longitud de la semilla.
       *
       * «seedlen» en el documento del NIST.
       */

      unsigned int mLongitudSemilla;

      /**
       * \brief Longitud máxima de la cadena de personalización.
       *
       * «max_personalization_string_length» en el documento del NIST.
       */

      entero mLongitudPersonalizacion;

      /**
       * \brief Máximo número de bits disponibles por petición.
       *
       * «max_number_of_bits_per_request» en el documento del NIST.
       */

      entero mLongitudMaxima;

      /**
       * \brief Especifica la vida útil de una semilla.
       *
       * «reseed_interval» en le documento del NIST.
       */

      entero mMaximoDePeticiones;

      /** \brief Contador de peticiones desde la última instanciación de la
       *  semilla. */
      entero mContadorDePeticiones;

      /**
       * \brief Semilla de algoritmo.
       *
       * Técnicamente la «semilla» solamente está presente en este arreglo
       * al momento de la construcción o después de una llamada a
       * «cambiarSemilla»; después solo se encuentra la actualización que
       * las demás funciones hacen sobre la semilla.
       *
       * Esto es lo que los documentos del NIST llaman valor «V». Junto con
       * otros posibles valores de los implementadores, el valor d eeste arreglo
       * es «crítico»: la seguridad de la implementación depende de que sea
       * secreto.
       */

      Arreglo<unsigned char> mSemilla;

      /** \brief Función generadora de bits (definida por concretos). */
      virtual Arreglo<unsigned char> generarBytes(entero longitud) = 0;
  };
}

#endif
