#include "cabeceras/cbc.hh"
#include <iostream>
#include <math.h>
#include <string.h>
#include "libaesni/iaesni.h"

using namespace std;

/** \brief El constructor inicia al cifrador de bloque con el tamaño de
llave a utilizar y reserva la memoria necesaria para el vector de
inicialización. */
CBC::CBC(int tamLlave){
  cifrador = AES(tamLlave);
  tamLongLongInt = sizeof(long long int);
  memset(vectorIni, 0x00, TAM_BLOQUE);
}

/** \brief  Dado el flujo de entrada, el desfase mediante el parámetro en
  inicio y el tamaño de bloque que se va a leer dado en el tercer
  parámetro, desplaza el cursor al desfase indicado y lee el número de
  bytes indicados anteriormente. Guarda los datos leídos en bloqueLeido. */
void CBC::leerBloque(ifstream &archivoOrigen, long long int inicio,
                      int tamBloque)
{
  archivoOrigen.seekg(inicio, ios::beg);
  archivoOrigen.read((char*)bloqueLeido, tamBloque);
  return;
}
/** \brief Realiza la operación lógica XOR entre bloqueUno y bloqueDos,
  elemento a elemento y almacena el resultado en resultado. Es importante
  resaltar que la operación da por sentado que los tres bloques provistos
  en los parámetros tiene longitud TAM_BLOQUE. */
void CBC::xorSimple(unsigned char* resultado, unsigned char* bloqueUno,
                    unsigned char* bloqueDos)
{
  for(int j=0; j<TAM_BLOQUE; j++)
  {
    resultado[j] = bloqueUno[j] ^ bloqueDos[j];
  }
  return;
}

/** \brief  Al inicio, calcula el tamaño de la llave (se asume que en el
  archivo no hay nada más que la llave), reserva el espacio de memoria
  suficiente para leerla y pone el tamaño de la llave en el cifrador AES.
  Posteriormente, inicializa la llave en el cifrador y libera el espacio
  que había reservado para leer la llave, pues ya no es necesario. */
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

/** \brief  Al inicio, calcula el tamaño del vector de inicialización (se
  asume que en el archivo no hay nada más que el vector de inicialización).
  Luego, comprueba que el tamaño del vector sea el mismo que el tamaño del
  bloque (y manda un error si no concuerda). Posteriormente lee al vector
  y lo almacena en el bloque vectorIni. */
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

/** \brief  Se encarga de obtener el tamaño del archivo que le es dado
  en el parámetro. */
void CBC::obtenerTamanioArchivo(ifstream &archivoOrigen)
{
  /* Obtener el tamaño del archivo origen */
  streampos inicioArchivo, finArchivo;

  inicioArchivo = archivoOrigen.tellg();
  archivoOrigen.seekg(0, ios::end);
  finArchivo = archivoOrigen.tellg();
  tamArchivo = finArchivo - inicioArchivo;
}

/** \brief  Como se recomienda agregar la longitud de los datos en el
  bloque inicial, se suma al tamaño del archivo el tamaño de un long long
  int (tipo de la variable que almacena el tamaño del archivo) y se divide
  entre el tamaño de bloque. La función ceil se encarga de redondear hacia
  arriba siempre para no perder información. Si se requiere más de un
  bloque, se calcula el resto (el número de bytes que faltan para completar
  el bloque) y el desfase ocasionado por agregar la longitud al inicio,
  pues no se lee un bloque de tamaño TAM_BLOQUE la primera vez cuando se
  requiere más de un bloque. */
void CBC::calcularNumBloques()
{
  /* Calcular número de bloques */
  numBloques = ceil((tamArchivo + sizeof(long long int)) / (double) TAM_BLOQUE);

  /* Determinar tamaño del primer bloque */
  desfase = tamArchivo;
  resto = TAM_BLOQUE - (tamArchivo + tamLongLongInt);
  if(numBloques > 1){
     desfase = TAM_BLOQUE - tamLongLongInt;
     resto = (TAM_BLOQUE * numBloques) - (tamArchivo + tamLongLongInt);
  }
}

/** \brief  El CBC residual o CBC MAC se calcula cifrando el archivo
  con un vector de inicialización en ceros; el resultado es el último
  bloque cifrado. La función cifra el primer bloque (habiendo agregado
  la longitud de los datos) y, si es necesario más de un bloque, entra
  en un ciclo para cifrar los bloques intermedios. */
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

/** \brief  Crea un archivo con el nombre de destino y escribe en ese flujo
  el archivo cifrado mediante CBC. Dado que esta es una función para probar
  el funcionamiento del CBC, se da por sentado que la entrada es múltiplo
  del tamaño de bloque y no es necesario agregar nada. Primero calcula el
  tamaño de archivo y luego el número de bloques necesarios. Posteriormente
  cifra el archivo mediante CBC. Cada que tiene una salida, la escribe en
  el archivo de salida. Al final, hace que el apuntador cbcResidual apunte
  al último bloque del cifrado, así no se debe cifrar de nuevo para obtener
  el CBC-MAC del archivo en cuestión. */
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
/** \brief  Crea un archivo con el nombre de destino y escribe en ese flujo
  el archivo descifrado mediante CBC. Dado que esta es una función para probar
  el funcionamiento del CBC, se da por sentado que la entrada es múltiplo
  del tamaño de bloque y no es necesario agregar nada. Primero calcula el
  tamaño de archivo y luego el número de bloques necesarios. Posteriormente
  descifra el archivo mediante CBC. Cada que tiene una salida, la escribe en
  el archivo de salida.  */
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

/** \brief  Regresa en un apuntador el contenido que hay en el bloque de
  cbc residual. */
unsigned char* CBC::obtenerBloqueCifrado()
{
  unsigned char *bloqueTCifradoExterior = new unsigned char[TAM_BLOQUE];
  memcpy(bloqueTCifradoExterior, cbcResidual, TAM_BLOQUE);
  return cbcResidual;
}
