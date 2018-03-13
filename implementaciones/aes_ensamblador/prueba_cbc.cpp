#include "cabeceras/cbc.hh"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

char* obtenerNombreSalida(char* nombreOrigen)
{
  char *nombreArchivoDestino = (char*) malloc (strlen(nombreOrigen) + 4);
  memcpy(nombreArchivoDestino, nombreOrigen, strlen(nombreOrigen));
  memcpy(nombreArchivoDestino+strlen(nombreOrigen), ".cbc", 4);
  return nombreArchivoDestino;
}

int main(int argc, char* argv[])
{
  if(argc!=4)
  {
    cout << "Uso correcto: " << argv[0] << " [nombreArchivoOrigen] "
         <<"[nombreArchivoLlave] [nombreArchivoIV]" << endl;
    return 0;
  }

  /** Abrir el archivo origen en modo binario */
  ifstream archivoOrigen;
  archivoOrigen.open(argv[1], ios::binary);
  if(!archivoOrigen.is_open())
  {
    cout << "Error al abrir el archivo origen." << endl;
    exit(0);
  }

  /** Abrir el archivo de la llave en modo binario */
  ifstream archivoLlave;
  archivoLlave.open(argv[2], ios::binary);
  if(!archivoLlave.is_open())
  {
    cout << "Error al abrir el archivo de la llave." << endl;
    exit(0);
  }

  /** Abrir el archivo de la llave en modo binario */
  ifstream archivoIni;
  archivoIni.open(argv[3], ios::binary);
  if(!archivoIni.is_open())
  {
    cout << "Error al abrir el archivo del vector de inicialización." << endl;
    exit(0);
  }

  char* nombreArchivoDestino = obtenerNombreSalida(argv[1]);
  char* nombreArchivoDestino2 = obtenerNombreSalida(nombreArchivoDestino);

  CBC cifrador = CBC(AES_256);
  cifrador.leerLlave(archivoLlave);
  cifrador.leerVectorIni(archivoIni);
  cifrador.cifrarArchivoExacto(archivoOrigen, nombreArchivoDestino);

  /** Abrir el archivo de la llave en modo binario */
  ifstream archivoCifrado;
  archivoCifrado.open(nombreArchivoDestino, ios::binary);
  if(!archivoCifrado.is_open())
  {
    cout << "Error al abrir el archivo cifrado." << endl;
    exit(0);
  }

  cifrador.descifrarArchivoExacto(archivoCifrado, nombreArchivoDestino2);
  
  return 1;
}