/**
 * \file
 * \brief Definición de una fuente de aleatoriedad trivial.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/aleatoriedad_trivial.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <fstream>
#include <string>
#include <vector>

using namespace Implementaciones;
using namespace std;

/**
 * Adquiere el recurso del archivo. Lo mantiene abierto durante la vida útil
 * del objeto.
 */

AleatoriedadTrivial::AleatoriedadTrivial(
  string nombreDeArchivo                  /**< Ruta al archivo fuente. */
)
: mArchivo {nombreDeArchivo, fstream::in | fstream::binary}
{
}

/**
 * Cierra el archivo interno.
 */

AleatoriedadTrivial::~AleatoriedadTrivial()
{
  mArchivo.close();
}

/**
 * Regresa el número de bytes solicitados como un arreglo de bytes.
 * La lectura inicial la hace con un arreglo duro; regresa el arreglo
 * construido mediante copia de una región de memoria ya reservada.
 *
 * \return Arreglo con bytes leídos desde archivo.
 */

Arreglo<unsigned char> AleatoriedadTrivial::operar(
  const std::vector<unsigned int>& entrada    /**< Número de bytes a leer. */
)
{
  unsigned char *arregloDuro = new unsigned char[entrada[0]];
  mArchivo.read(reinterpret_cast<char*>(arregloDuro), entrada[0]);
  return Arreglo<unsigned char>(entrada[0], move(arregloDuro));
}
