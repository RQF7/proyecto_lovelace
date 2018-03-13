#include "cabeceras/cbc.hh"
#include <iostream>
#include <math.h> 
#include <string.h> 
#include "libaesni/iaesni.h"

using namespace std;


CBC::CBC(int tamLlave){
  cifrador = AES(tamLlave);
  tamLongLongInt = sizeof(long long int);
  memset(vectorIni, 0x00, TAM_BLOQUE);
}

void CBC::leerBloque(ifstream &archivoOrigen, long long int inicio, 
                      int tamBloque)
{
  /* Leer el archivo */
  archivoOrigen.seekg(inicio, ios::beg);
  archivoOrigen.read((char*)bloqueLeido, tamBloque);
  return;
}

void CBC::xorSimple(unsigned char* resultado, unsigned char* bloqueUno,
                    unsigned char* bloqueDos)
{
  /* Hacer XOR entre el bloque leído y el bloque cifrado anterior */
  for(int j=0; j<TAM_BLOQUE; j++)
  {
    resultado[j] = bloqueUno[j] ^ bloqueDos[j];
  }
  return;
}

void CBC::leerLlave(ifstream &archivoLlave)
{
  streampos inicioArchivo, finArchivo;

  inicioArchivo = archivoLlave.tellg();
  archivoLlave.seekg(0, ios::end);
  finArchivo = archivoLlave.tellg();
  int tamLlaveL = finArchivo - inicioArchivo;

  unsigned char *llave = new unsigned char [tamLlaveL];
  archivoLlave.seekg(0, ios::beg);
  archivoLlave.read((char*)llave, tamLlaveL);

  cifrador.ponerTamanioLlave(tamLlaveL);
  cifrador.ponerLlave(llave);

  delete [] llave;

  return;
}

void CBC::leerVectorIni(ifstream &archivoVI)
{
  streampos inicioArchivo, finArchivo;

  inicioArchivo = archivoVI.tellg();
  archivoVI.seekg(0, ios::end);
  finArchivo = archivoVI.tellg();
  int tamVI = finArchivo - inicioArchivo;

  if(tamVI != TAM_BLOQUE)
  {
    cout << "Tamaño de vector de inicialización inválido ("  << tamVI << ")."  << endl;
    exit(0);
  }

  archivoVI.seekg(0, ios::beg);
  archivoVI.read((char*)vectorIni, tamVI);

  return;
}

void CBC::obtenerTamanioArchivo(ifstream &archivoOrigen)
{
  /* Obtener el tamaño del archivo origen */
  streampos inicioArchivo, finArchivo;

  inicioArchivo = archivoOrigen.tellg();
  archivoOrigen.seekg(0, ios::end);
  finArchivo = archivoOrigen.tellg();
  tamArchivo = finArchivo - inicioArchivo;
}

void CBC::calcularNumBloques()
{
  /* Calcular número de bloques */
  numBloques = ceil((tamArchivo + sizeof(long long int)) / (double) TAM_BLOQUE);
  
  /* Determinar tamaño del primer bloque */
  desfase = tamArchivo;
  resto = 0;
  if(numBloques > 1){
     desfase = TAM_BLOQUE - tamLongLongInt;
     resto = (TAM_BLOQUE * numBloques) - (tamArchivo + tamLongLongInt);
  }
}

unsigned char* CBC::calcularCBCResidual(ifstream &archivoOrigen)
{

  obtenerTamanioArchivo(archivoOrigen);
  calcularNumBloques();

  /* CBC-MAC para primer bloque*/

  /* Leer el primer bloque del archivo */
  leerBloque(archivoOrigen, 0, desfase);

  /* Llenar el buffer con ceros */
  memset(bloqueClaro, 0x00, TAM_BLOQUE);

  /* Escribir la longitud y los datos leídos y cifrar el bloque */
  memcpy(bloqueClaro, &tamArchivo, tamLongLongInt);
  memcpy(bloqueClaro+tamLongLongInt, bloqueLeido, desfase);
  cifrador.cifrarBloque(bloqueClaro);

  if(numBloques > 1)
  {
    /* Cifrar todos los bloques intermedios*/
    for(int i=0; i<numBloques-2; i++)
    {
      /* Leer y cifrar el bloque en turno */
      leerBloque(archivoOrigen, (TAM_BLOQUE*i)+desfase, TAM_BLOQUE);
      xorSimple(bloqueClaro, bloqueLeido, bloqueCifrado);
      cifrador.cifrarBloque(bloqueClaro);
    }
    /* Obtener el CBC residual (último bloque) */

    /** Llenar los buffers con ceros */
    memset(bloqueLeido, 0x00, TAM_BLOQUE);
    memset(bloqueClaro, 0x00, TAM_BLOQUE);

    /* Leer y cifrar el último bloque */
    leerBloque(archivoOrigen, (TAM_BLOQUE*(numBloques-2))+desfase, 
      TAM_BLOQUE - resto);
    xorSimple(bloqueClaro, bloqueLeido, bloqueCifrado);
    cifrador.cifrarBloque(bloqueClaro);
  }

  return cifrador.obtenerBloqueTCifrado();
}

int CBC::cifrarArchivoExacto(ifstream &archivoOrigen, char* nombreDestino)
{

  /* Configurar archivo de salida */
  fstream archivoDestino;
  archivoDestino.open(nombreDestino, ios::binary | ios::out);
  if(!archivoDestino.is_open())
  {
    cout << "Error al abrir el archivo destino." << endl;
    return 0;
  }

  obtenerTamanioArchivo(archivoOrigen);
  
  /* Calcular número de bloques */
  numBloques = ceil(tamArchivo / (double) TAM_BLOQUE);
  
  
  /* Leer el primer bloque del archivo */
  leerBloque(archivoOrigen, 0, TAM_BLOQUE);

  memcpy(bloqueClaro, bloqueLeido, TAM_BLOQUE);
  xorSimple(bloqueClaro, bloqueLeido, vectorIni);
  cifrador.cifrarBloque(bloqueClaro);
  archivoDestino.write((char*)cifrador.obtenerBloqueTCifrado(), TAM_BLOQUE);

  if(numBloques > 1)
  {
    /* Cifrar todos los bloques intermedios*/
    for(int i=1; i<numBloques; i++)
    {
      /** Leer y cifrar el bloque en turno */
      leerBloque(archivoOrigen, (TAM_BLOQUE*i), TAM_BLOQUE);
      xorSimple(bloqueClaro, bloqueLeido, bloqueCifrado);
      cifrador.cifrarBloque(bloqueClaro);
      archivoDestino.write((char*)cifrador.obtenerBloqueTCifrado(), TAM_BLOQUE);
    }
  }
  cbcResidual = cifrador.obtenerBloqueTCifrado();

  /* Cerrar archivo de destino */
  archivoDestino.close();

  return 1;
}

int CBC::descifrarArchivoExacto(ifstream &archivoOrigen, char* nombreDestino)
{

  /* Configurar archivo de salida */
  fstream archivoDestino;
  archivoDestino.open(nombreDestino, ios::binary | ios::out);
  if(!archivoDestino.is_open())
  {
    cout << "Error al abrir el archivo destino." << endl;
    return 0;
  }

  unsigned char *bloqueLeidoAnterior = new unsigned char[TAM_BLOQUE];

  obtenerTamanioArchivo(archivoOrigen);
  
  /* Calcular número de bloques */
  numBloques = ceil(tamArchivo / (double) TAM_BLOQUE);
  
  
  /* Leer el primer bloque del archivo */
  leerBloque(archivoOrigen, 0, TAM_BLOQUE);

  memcpy(bloqueCifrado, bloqueLeido, TAM_BLOQUE);
  cifrador.descifrarBloque(bloqueCifrado);
  xorSimple(bloqueClaro, cifrador.obtenerBloqueTClaro(), vectorIni);
  
  archivoDestino.write((char*)bloqueClaro, TAM_BLOQUE);
  memcpy(bloqueLeidoAnterior, bloqueLeido, TAM_BLOQUE);

  if(numBloques > 1)
  {
    /* Cifrar todos los bloques intermedios*/
    for(int i=1; i<numBloques; i++)
    {
      /* Leer y cifrar el bloque en turno */
      leerBloque(archivoOrigen, (TAM_BLOQUE*i), TAM_BLOQUE);
      memcpy(bloqueCifrado, bloqueLeido, TAM_BLOQUE);
      cifrador.descifrarBloque(bloqueCifrado);
      //xorSimple(bloqueClaro, cifrador.obtenerBloqueTClaro(), bloqueLeidoAnterior);
      archivoDestino.write((char*)bloqueClaro, TAM_BLOQUE);
      memcpy(bloqueLeidoAnterior, bloqueLeido, TAM_BLOQUE);
    }
  }

  /* Cerrar archivo de destino */
  archivoDestino.close();

  return 1;
}

unsigned char* CBC::obtenerBloqueCifrado()
{
  unsigned char *bloqueTCifradoExterior = new unsigned char[TAM_BLOQUE];
  memcpy(bloqueTCifradoExterior, cbcResidual, TAM_BLOQUE);
  return cbcResidual;
}

