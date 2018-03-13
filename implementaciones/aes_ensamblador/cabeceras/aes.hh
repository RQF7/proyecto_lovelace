/**
 * \file
 * \brief Definición e implementación de AES mediante hardware
 *
 * Esta es una capa que, utilizando el paradigma orientado a objetos,
 * se encarga de cifrar y descifrar bloques mediante las instrucciones
 * que tiene Intel en sus procesadores. 
 *
 * Proyecto Lovelace.
 */

#ifndef __AES_HH__
#define __AES_HH__

#include <iostream>

#define TAM_BLOQUE 16 //16 bytes = 128 bits

#define AES_128 1
#define AES_192 2
#define AES_256 3

#define LLAVE_AES_128 16
#define LLAVE_AES_192 24
#define LLAVE_AES_256 32

class AES
{
  private:
    unsigned char *bloqueTClaro;
    unsigned char *bloqueTCifrado;
    unsigned char *vectorLlave;
    int numBloques;
    int tamLlave;
    long long int resto;
    long long int desfase;

  public:
    /** Constructor que recibe como parámetro el tamaño de llave a utilizar */
    AES();

    /** Constructor que recibe como parámetro el tamaño de llave a utilizar */
    AES(int);

    /** Operación para cambiar el tamaño de la llave a utilizar */
    void ponerTamanioLlave(int);

    /** Operación para obtener el tamaño de llave indicado en bytes */
    int obtenerTamanioLlave();

    /** Operación para poner (o reemplazar) la llave actual */
    void ponerLlave(unsigned char*);

    /** Operación para obtener la llave actual */
    unsigned char* obtenerLlave();

    /** Operación para obtener el bloque de texto claro*/
    unsigned char* obtenerBloqueTClaro();

     /** Operación para obtener el bloque de texto cifrado*/
    unsigned char* obtenerBloqueTCifrado();

    /** Operación que permite cifrar un bloque mediante AES*/
    int cifrarBloque(unsigned char*);

    /** Operación que permite descifrar un bloque mediante AES*/
    int descifrarBloque(unsigned char*);
};

#endif
