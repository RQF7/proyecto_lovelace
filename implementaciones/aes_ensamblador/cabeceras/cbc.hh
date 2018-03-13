/**
 * \file
 * \brief Implementación de CBC utilizando AES
 *
 * Utilizando el paradigma orientado a objetos, esta clase inicializa
 * un cifrador de AES y se encarga de cifrar un archivo y obtener el
 * CBC-MAC o CBC residual de un archivo dado.
 *
 * Proyecto Lovelace.
 */

#ifndef __CBC_HH__
#define __CBC_HH__

#include <fstream>
#include "aes.hh"

class CBC{
private:
  unsigned char *bloqueClaro = new unsigned char[TAM_BLOQUE];
  unsigned char *bloqueCifrado = new unsigned char[TAM_BLOQUE];
  unsigned char *bloqueLeido = new unsigned char[TAM_BLOQUE];
  unsigned char *vectorIni = new unsigned char[TAM_BLOQUE];
  unsigned char *cbcResidual = new unsigned char[TAM_BLOQUE];

  long long int numBloques, tamArchivo,
                desfase, resto;
  
  AES cifrador;

  int tamLongLongInt;
  

public:
  /** Constructor que recibe como parámetro el tamaño que se usará para AES */
  CBC(int);

  /** Lector de bloque que recibe el flujo, el desplazamiento inicial y el total
  de bytes a ser leídos. */
  void leerBloque(std::ifstream &, long long int, int);
  
  /** Realiza una operación XOR entre los últimos arreglos dados y los guarda en
  el primero. */
  void xorSimple(unsigned char*, unsigned char*, unsigned char*);
  
  /** Recibe el flujo del archivo de llave, pone el tamaño de llave en el
  cifrador y carga la llave. */
  void leerLlave(std::ifstream &);

  /** Recibe el flujo del archivo del vector de inicialización, comprueba que
  tenga el mismo tamaño que el tamaño de bloque y lo carga. */
  void leerVectorIni(std::ifstream &);
  
  /** Regresa el tamaño del archivo dado*/
  void obtenerTamanioArchivo(std::ifstream &);
  
  /** Calcula el número de bloques necesarios para su cifrado mediante AES-CBC*/
  void calcularNumBloques();
  
  /** Calcula el CBC-MAC del archivo dado. */
  unsigned char*  calcularCBCResidual(std::ifstream &);
  
  /** Función que permite probar el funcionamiento del cifrado CBC, pues toma
  tal cual la entrada y no agrega ni padding ni la longitud. La entrada debe ser
  exacta. */
  int cifrarArchivoExacto(std::ifstream &, char*);

  /** Función que permite probar el funcionamiento del descifrado CBC, pues toma
  tal cual la entrada y no agrega ni padding ni la longitud. La entrada debe ser
  exacta. */
  int descifrarArchivoExacto(std::ifstream &, char*);

  /** Función que regresa el último bloque cifrado mediante CBC. Úsese solo
  después de calcular el CBC residual o de haber cifrado un archivo exacto. */
  unsigned char* obtenerBloqueCifrado();

};

#endif
