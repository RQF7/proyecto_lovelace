/**
 * \file
 * \brief Definición e implementación de AES mediante hardware
 *
 * Capa que, utilizando el paradigma orientado a objetos,
 * se encarga de cifrar y descifrar bloques mediante las instrucciones
 * que tiene Intel en sus procesadores.
 *
 * Proyecto Lovelace.
 */

#ifndef __AES_HH__
#define __AES_HH__

#include <iostream>

/** \brief Tamaño del bloque: 16 bytes = 128 bits. */
#define TAM_BLOQUE 16 //16 bytes = 128 bits

/** \brief Tamaño de la llave: 16 bytes = 128 bits. */
#define LLAVE_AES_128 16
/** \brief Tamaño de la llave: 24 bytes = 192 bits. */
#define LLAVE_AES_192 24
/** \brief Tamaño de la llave: 32 bytes = 256 bits. */
#define LLAVE_AES_256 32

/** \brief Constante para indicar el tamaño de la llave al constructor */
#define AES_128 1
/** \brief Constante para indicar el tamaño de la llave al constructor */
#define AES_192 2
/** \brief Constante para indicar el tamaño de la llave al constructor */
#define AES_256 3

class AES
{
  private:
    /** \brief Arreglo donde se guarda el bloque en claro. */
    unsigned char *bloqueTClaro;

    /** \brief Arreglo donde se guarda el bloque cifrado. */
    unsigned char *bloqueTCifrado;

    /** \brief Arreglo donde se guarda la llave que se está utilizando. */
    unsigned char *vectorLlave;

    /** \brief Contiene la longitud de la llave que se está utilizando. */
    int tamLlave;

  public:
    /** \brief Constructor que inicia el cifrador AES con una longitud de llave
    de 192 bits. */
    AES();

    /** \brief Constructor que recibe como parámetro el tamaño de llave a
    utilizar */
    AES(int);

    /** \brief Constructor por copia */
    AES(AES const&);

    /** \brief Destructor que libera la memoria utilizada */
    ~AES();

    /** \brief Operación para cambiar el tamaño de la llave a utilizar */
    void ponerTamanioLlave(int);

    /** \brief Operación para obtener el tamaño de llave indicado en bytes */
    int obtenerTamanioLlave();

    /** \brief Operación para poner (o reemplazar) la llave actual */
    void ponerLlave(unsigned char*);

    /** \brief Operación para obtener la llave actual */
    unsigned char* obtenerLlave();

    /** \brief Operación para obtener el bloque de texto claro*/
    unsigned char* obtenerBloqueTClaro();

     /** \brief Operación para obtener el bloque de texto cifrado*/
    unsigned char* obtenerBloqueTCifrado();

    /** \brief Operación que permite cifrar un bloque mediante AES*/
    int cifrarBloque(unsigned char*);

    /** \brief Operación que permite descifrar un bloque mediante AES*/
    int descifrarBloque(unsigned char*);
};

#endif
