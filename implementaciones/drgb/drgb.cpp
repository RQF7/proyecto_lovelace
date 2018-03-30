/**
 * \file
 * \brief Implementación de un DRGB.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/drgb.hh"
#include <vector>

using namespace Implementaciones;
using namespace std;

/**
 *
 * La fuente de aleatoriedad y la cadena de personalización son usadas para
 * inicializar la samilla; el estándar del NIST también incñuye un nonce para
 * esto: pueden ser bits adicionales de la fuente de aleatoriedad, una marca de
 * tiempo o un contador; para simplificar las interfaces, en esta implementación
 * se utiliza la misma fuente de aleatoriedad para producir el nonce.
 *
 * \param nivelDeSeguridad Máximo nivel de seguridad soportado.
 */

DRGB::DRGB(
  NivelDeSeguridad nivelDeSeguridad
)
: mContadorDePeticiones {0}
{
}

/**
 *
 */

DRGB::~DRGB()
{

}

/**
 *
 * La fuerza de seguridad de la salida es el mínimo de entre la longitud
 * de la salida y el nivel de la instanciación.
 *
 * \param entrada El primer elemento del vector indica la fuerza de seguridad
 *                que se requiere para la salida.
 *
 * \throw FuerzaNoSoportada Si la fuerza solicitada es mayor que el nivel de
 *                          seguridad provisto por la instanciación.
 */

DRGB::operar(const vector<unsigned int>& entrada)
{
  if (entrada[0] > static_cast<unsigned int>(mNivelDeSeguridad))
    throw FuerzaNoSoportada{
      "La instanciación no soporta ese nivel de seguridad."}

  mContadorDePeticiones++;
  if (mContadorDePeticiones > mMaximoDePeticiones)
    cambiarSemilla();
}

/**
 * Vuelve a determinar una semilla basándose en la salida de la
 * fuente de aleatoriedad. Reinicia el contador de peticiones.
 *
 * Esta función puede tanto ser llamada por los clientes como ser llamada desde
 * la función generadora (cuando se alcanza la vida útil de la semilla).
 */

DRGB::cambiarSemilla()
{
  mContadorDePeticiones = 0;
}

/**
 *
 */

DRGB::desinstanciar()
{

}

/**
 *
 */

DRGB::probarSalud()
{

}
