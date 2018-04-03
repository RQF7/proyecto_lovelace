/**
 * \file
 * \brief Implementación de un DRBG.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/drbg.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <string>
#include <vector>

using namespace Implementaciones;
using namespace std;

/**
 * La fuente de aleatoriedad y la cadena de personalización son usadas para
 * inicializar la samilla; el estándar del NIST también incluye un nonce para
 * esto: pueden ser bits adicionales de la fuente de aleatoriedad, una marca de
 * tiempo o un contador; para simplificar las interfaces, en esta implementación
 * se utiliza la misma fuente de aleatoriedad para producir el nonce.
 *
 * De las interfaces que se manejan en el estándar solamente falta la bandera
 * de predicción de resistencias; como no estoy seguro de que nuestras fuentes
 * de aleatoriedad soporten eso, de momento no la incluyo.
 *
 * \throw PersonalizacionDemasiadoGrande Si la cadena de personzalización
 *                                       excede lo dado en
 *                                       \p longitudPersonalizacion.
 */

DRBG::DRBG(
  /** Apuntador a función generadora de entroía.
   *  (la clase no es respondable de esta memoria). */
  FuenteDeAleatoriedad *fuenteDeAlatoriedad,
  /** Cadena opcional de personalización. */
  Arreglo<unsigned char> cadenaDePersonalizacion,
  /** Máximo nivel de seguridad soportado. */
  NivelDeSeguridad nivelDeSeguridad,
  /** Longitud de la semilla. */
  unsigned int longitudSemilla,
  /** Longitud máxima de la cadena de personalización. */
  entero longitudPersonalizacion,
  /** Máximo número de bits disponibles por petición. */
  entero longitudMaxima,
  /** Vida útil de una semilla. */
  entero maximoDePeticiones
)
: mFuenteDeAlatoriedad {fuenteDeAlatoriedad},
  mCadenaDePersonalizacion {cadenaDePersonalizacion},
  mNivelDeSeguridad {nivelDeSeguridad},
  mLongitudSemilla {longitudSemilla},
  mLongitudPersonalizacion {longitudPersonalizacion},
  mLongitudMaxima {longitudMaxima},
  mMaximoDePeticiones {maximoDePeticiones},
  mContadorDePeticiones {0},
  mSemilla {mFuenteDeAlatoriedad->operar({mLongitudSemilla})}
{
  if (mCadenaDePersonalizacion.obtenerNumeroDeElementos() >
    mLongitudPersonalizacion)
    throw PersonalizacionDemasiadoGrande{
      string{"La cadena de personalización no debe exceder los"}
      + to_string(mLongitudPersonalizacion) + string{" bytes."}};
}

/**
 * La fuerza de seguridad de la salida es el mínimo de entre la longitud
 * de la salida y el nivel de la instanciación.
 *
 * \param entrada El primer elemento indica la longitud deseada para la salida.
 *                El segundo elemento (opcional) indica la fuera de seguridad
 *                deseada. Si no se da, se supone la de la instancia.
 *
 * \throw FuerzaNoSoportada Si la fuerza solicitada es mayor que el nivel de
 *                          seguridad provisto por la instanciación.
 */

Arreglo<unsigned char> DRBG::operar(const vector<unsigned int>& entrada)
{
  if (entrada.size() == 2)
    if (entrada[1] > static_cast<unsigned int>(mNivelDeSeguridad))
      throw FuerzaNoSoportada{
        "La instanciación no soporta ese nivel de seguridad."};

  mContadorDePeticiones++;
  if (mContadorDePeticiones > mMaximoDePeticiones)
    cambiarSemilla();

  return generarBytes(entrada[0]);
}

/**
 * Vuelve a determinar una semilla basándose en la salida de la
 * fuente de aleatoriedad. Reinicia el contador de peticiones.
 *
 * Esta función puede tanto ser llamada por los clientes como ser llamada desde
 * la función generadora (cuando se alcanza la vida útil de la semilla).
 */

void DRBG::cambiarSemilla()
{
  mContadorDePeticiones = 0;
  mSemilla = mFuenteDeAlatoriedad->operar({mLongitudSemilla});
}

/**
 * Elimina (pone en ceros) la información crítica que se mantiene en la
 * esta clase: el valor de la semilla.
 */

void DRBG::desinstanciar()
{
  mSemilla.colocarConstante(0);
}
