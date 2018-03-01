#include "cabeceras/cbcmac.h"
#include <iostream>
#include <fstream>
#include <math.h> 
#include <string.h> 
#include "libaesni/iaesni.h"

using namespace std;

char* obtenerNombreSalida(char* nombreOrigen)
{
  char *nombreArchivoDestino = (char*) malloc (strlen(nombreOrigen) + 4);
  memcpy(nombreArchivoDestino, nombreOrigen, strlen(nombreOrigen));
  memcpy(nombreArchivoDestino+strlen(nombreOrigen), ".mac", 4);
  return nombreArchivoDestino;
}

void leerBloque(ifstream &archivoOrigen, long long int inicio, int tamBloque, unsigned char* archivo)
{
  /** Leer el archivo */
  archivoOrigen.seekg(inicio, ios::beg);
  archivoOrigen.read((char*)archivo, tamBloque);
  return;
}

void cifrarBloque(unsigned char* textoClaro, unsigned char* textoCifrado, unsigned char* vectorLlave, int tamLlave)
{
  switch (tamLlave)
  {
    case AES_128:
      intel_AES_enc128(textoClaro, textoCifrado, vectorLlave, 1);
      break;
    case AES_192:
      intel_AES_enc192(textoClaro, textoCifrado, vectorLlave, 1);
      break;
    case AES_256:
      intel_AES_enc256(textoClaro, textoCifrado, vectorLlave, 1);
      break;
    default:
      cout << "Tamaño de llave inválido." << endl;
      exit(1);
  }
  return;
}

void xorSimple(unsigned char* textoClaro, unsigned char* textoCifrado, unsigned char* archivo)
{
  /** Hacer XOR entre el bloque leído y el bloque cifrado anterior */
  for(int j=0; j<TAM_BLOQUE; j++)
  {
    textoClaro[j] = archivo[j] ^ textoCifrado[j];
  }
  return;
}

unsigned char* leerLlave(ifstream &archivoLlave)
{
  streampos inicioArchivo, finArchivo;

  inicioArchivo = archivoLlave.tellg();
  archivoLlave.seekg(0, ios::end);
  finArchivo = archivoLlave.tellg();
  int tamLlaveL = finArchivo - inicioArchivo;

  unsigned char *llave = (unsigned char*) malloc (tamLlaveL);
  archivoLlave.seekg(0, ios::beg);
  archivoLlave.read((char*)llave, tamLlaveL);

  return llave;
}

int determinarTamanioLlave(int longitudLlave)
{
  switch(longitudLlave)
  {
    case 16:
      return AES_128;
      break;
    case 24:
      return AES_192;
      break;
    case 32:
      return AES_256;
      break;
    default:
      cout << "Archivo de llave inválido." << endl;
      exit(1);
  }
  return 0;
}

unsigned char* cbcMac(ifstream &archivoOrigen, unsigned char* vectorLlave, int tamLlave)
{
  /** Obtener el tamaño del archivo origen */
  streampos inicioArchivo, finArchivo;
  long long int tamArchivo;

  inicioArchivo = archivoOrigen.tellg();
  archivoOrigen.seekg(0, ios::end);
  finArchivo = archivoOrigen.tellg();
  tamArchivo = finArchivo - inicioArchivo;
  cout << "Tamaño del archivo: " << tamArchivo << endl;

  /** Calcular número de bloques */
  long long int numBloques;
  numBloques = ceil((tamArchivo + sizeof(long long int)) / (double) TAM_BLOQUE);

  int tamLongLongInt = sizeof(long long int);

  /** Arreglos donde se almacenarán los datos */
  unsigned char *textoClaro = new unsigned char [TAM_BLOQUE],
                *textoCifrado = new unsigned char [TAM_BLOQUE],
                *archivo = new unsigned char[TAM_BLOQUE];

  /** CBC-MAC para primer bloque*/

  /** Determinar tamaño del primer bloque */
  long long int desfase = tamArchivo;
  if(numBloques > 1){
     desfase = TAM_BLOQUE - tamLongLongInt;
  }

  cout  << "Primer bloque. " << endl
        << "Leyendo " << desfase << " bytes"<< endl;

  /** Leer el primer bloque del archivo */
  leerBloque(archivoOrigen, 0, desfase, archivo);

  /** Llenar el buffer con ceros */
  memset(textoClaro, 0x00, TAM_BLOQUE);
    
  /** Escribir la longitud y los datos leídos y cifrar el bloque */
  memcpy(textoClaro, &tamArchivo, tamLongLongInt);
  memcpy(textoClaro+tamLongLongInt, archivo, desfase);
  cifrarBloque(textoClaro, textoCifrado, vectorLlave, tamLlave);
  
  /** CBC-MAC para más de un bloque */
  if(numBloques > 1){
    /** Obtener tamaño del resto */
    long long int resto;
    resto = (TAM_BLOQUE * numBloques) - (tamArchivo + tamLongLongInt);

    /** Obtener tamaño del primer bloque */
    cout  << "Bloques necesarios: " << numBloques << endl
          << "Tamaño del faltante: " << resto << endl;

    /** Cifrar todos los bloques intermedios*/
    for(int i=0; i<numBloques-2; i++)
    {
      /** Leer y cifrar el bloque en turno */
      leerBloque(archivoOrigen, (TAM_BLOQUE*i)+desfase, TAM_BLOQUE, archivo);
      xorSimple(textoClaro, textoCifrado, archivo);
      cifrarBloque(textoClaro, textoCifrado, vectorLlave, tamLlave);
    }
    /** Obtener el CBC residual (último bloque) */

    /** Llenar los buffers con ceros */
    memset(archivo, 0x00, TAM_BLOQUE);
    memset(textoClaro, 0x00, TAM_BLOQUE);

    /** Leer y cifrar el último bloque */
    leerBloque(archivoOrigen, (TAM_BLOQUE*(numBloques-2))+desfase, 
      TAM_BLOQUE - resto, archivo);
    xorSimple(textoClaro, textoCifrado, archivo);
    cifrarBloque(textoClaro, textoCifrado, vectorLlave, tamLlave);
  }

  /** Liberar memoria */
  delete [] archivo;
  delete [] textoClaro;

  /** Regresar CBC residual*/
  return textoCifrado;
}
