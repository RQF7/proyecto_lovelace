/**
 * \file
 * \brief Interfza ejecutable a algoritmos tokenizadores.
 *
 * Proyecto Lovelace.
 */

#include "utilidades/cabeceras/utilidades_criptograficas.hh"
#include <iostream>
#include <fstream>
#include <string>

using namespace Implementaciones;
using namespace std;

/** \brief Mensaje con instrucciones. */
void imprimirAyuda();

/** \brief Genración de llave pseudoaleatoria. */
void generarLlave(string nombreDeArchivo, int longitud);

/**
 * Función principal de interfaz con algoritmos tokenizadores. Recibe de
 * los argumentos de la línea de comandos la operación y actúa en consecuencia.
 *
 * \return Estado de ejecución.
 */

int main(int numeroDeArgumentos, char** argumentos)
{
  /* Discriminación por número de argumentos. */
  if (numeroDeArgumentos < 3)
  {
    imprimirAyuda();
    return EXIT_FAILURE;
  }

  string operacion {argumentos[1]};
  /* Generar llave. */
  if (operacion == "-k")
  {
    string nombreDeArchivo {argumentos[2]};
    int longitud {stoi(string{argumentos[3]})};
    cout << "Generar llave de " << longitud << " bits." << endl;
    generarLlave(nombreDeArchivo, longitud);
    cout << "Llave guardada en " << nombreDeArchivo << "." << endl;
  }
  /* Tokenizar. */
  else if (operacion == "-e")
  {

  }
  /* Detokenizar. */
  else if (operacion == "-d")
  {

  }
  /* Ayuda. */
  else if (operacion == "-d")
  {
    imprimirAyuda();
  }
  else
  {
   imprimirAyuda();
   return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/**
 * Imprime en la salida estándar un mensaje dirigido al usuario del programa
 * indicando cómo es la operación correcta.
 */

void imprimirAyuda()
{
  cout << "Uso de programa: " << endl
      << "./binarios/lovelace OPERACIÓN ARGUMENTOS" << endl
      << "OPERACIÓN := -k | -e | -d | -h " << endl
      << "-k NOMBRE_DE_ARCHIVO LONGITUD" << endl
      << "  Genera una llave aleatoria de la longitud solicitada y" << endl
      << "  la guarda en el archivo dado." << endl
      << "-e MÉTODO PAN ARCHIVO_DE_LLAVE" << endl
      << "  Genera el token del PAN dado con el método y la llave" << endl
      << "  especificados."
      << "-d MÉTODO TOKEN ARCHIVO_DE_LLAVE" << endl
      << "  Detokeniza el token dado con el método y la llave" << endl
      << "  especificados." << endl
      << "MÉTODO := TKR | FFX | BPS | HAR" << endl
      << "-k" << endl
      << "  Imprime este mensaje." << endl
      << endl;
}

/**
 * Genera una llave aleatoria de la longitud solicitada y la guarda en el
 * archivo de la ruta dada.
 */

void generarLlave(
  string nombreDeArchivo,     /**< Ruta a archivo destino. */
  int longitud                /**< Longitud en bytes de llave. */
)
{
  unsigned char* llave = generarLlave(longitud);
  fstream archivo {nombreDeArchivo.c_str(),
    fstream::out | fstream::binary | fstream::trunc};
  archivo.write(reinterpret_cast<const char*>(llave), longitud);
  archivo.close();
  delete[] llave;
}
