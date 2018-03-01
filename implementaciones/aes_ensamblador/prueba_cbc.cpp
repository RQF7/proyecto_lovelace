#include "cabeceras/cbcmac.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc!=3)
  {
    cout << "Uso correcto: " << argv[0] << " [nombreArchivoOrigen] "
         <<"[nombreArchivoLlave]" << endl;
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

  /** Leer el archivo de la llave y obtener su tamaño */
  unsigned char *vectorLlave = leerLlave(archivoLlave);
  int tamLlave = determinarTamanioLlave(strlen((char*)vectorLlave));

  unsigned char* textoCifrado;
  textoCifrado = cbcMac(archivoOrigen, vectorLlave, tamLlave);

  /** Abrir archivo de salida */
  fstream archivoDestino;
  char* nombreArchivoDestino;
  nombreArchivoDestino = obtenerNombreSalida(argv[1]);
  archivoDestino.open(nombreArchivoDestino, ios::binary | ios::out);
  if(!archivoDestino.is_open())
  {
    cout << "Error al abrir el archivo destino." << endl;
    return 0;
  }

  /** Escribir CBC residual en el archivo de salida */
  archivoDestino.write((char*)textoCifrado, TAM_BLOQUE);
  
  /** Cerrar ficheros */
  archivoDestino.close();
  archivoOrigen.close();

  /** Liberar memoria */
  delete [] textoCifrado;
  
  return 1;
}