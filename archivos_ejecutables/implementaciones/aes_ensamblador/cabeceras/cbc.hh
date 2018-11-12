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

namespace Implementaciones
{
  class CBC
  {
    private:
      /** \brief Arreglo donde se guarda el bloque de texto en claro. */
      unsigned char *bloqueClaro = new unsigned char[TAM_BLOQUE];

      /** \brief Arreglo donde se guarda el bloque de texto cifrado. */
      unsigned char *bloqueCifrado = new unsigned char[TAM_BLOQUE];

      /** \brief Arreglo donde se guarda el bloque de texto leído. */
      unsigned char *bloqueLeido = new unsigned char[TAM_BLOQUE];

      /** \brief Arreglo donde se guarda el vector de inicialización. */
      unsigned char *vectorIni = new unsigned char[TAM_BLOQUE];

      /** \brief Arreglo donde se guarda el cbc residual. */
      unsigned char *cbcResidual = new unsigned char[TAM_BLOQUE];

      /** \brief Entero que contiene el número de bloques necesarios para la
        operación de cifrado o descifrado. */
      long long int numBloques;

      /** \brief Entero que contiene el tamaño del archivo que se va a cifrar
        o descifrar. */
      long long int tamArchivo;

      /** \brief Entero que contiene el desfase del primer bloque por agregar
        la longitud del archivo al principio. */
      long long int desfase;

      /** \brief Entero que contiene el resto: el sobrante entre el tamaño de
        bloques y el tamaño del archivo y la longitud del archivo: resto =
        (TAM_BLOQUE * numBloques) - (tamArchivo + 8). */
      long long int resto;

      /** \brief Cifrador por bloques que está detrás del modo de operación. */
      AES cifrador;

      /** \brief Tamaño del long long int. */
      int tamLongLongInt;


    public:
      /** \brief Constructor que recibe como parámetro el tamaño que se usará
        para AES. */
      CBC(int);

      /** \brief Lector de bloque que recibe el flujo, el desplazamiento
        inicial y el total de bytes a ser leídos. */
      void leerBloque(std::ifstream &, long long int, int);

      /** \brief  Realiza una operación XOR entre los últimos arreglos dados y
        los guarda en el primero. */
      void xorSimple(unsigned char*, unsigned char*, unsigned char*);

      /** \brief Recibe el flujo del archivo de llave, pone el tamaño de llave
        en el cifrador y carga la llave. */
      void leerLlave(std::ifstream &);

      /** \brief Recibe el flujo del archivo del vector de inicialización,
        comprueba que tenga el mismo tamaño que el tamaño de bloque y lo carga. */
      void leerVectorIni(std::ifstream &);

      /** \brief Regresa el tamaño del archivo dado*/
      void obtenerTamanioArchivo(std::ifstream &);

      /** \brief Calcula el número de bloques necesarios para su cifrado
        mediante. */
      void calcularNumBloques();

      /** \brief Calcula el CBC-MAC del archivo dado. */
      unsigned char*  calcularCBCResidual(std::ifstream &);

      /** \brief Permite probar el funcionamiento del cifrado CBC, pues
        toma tal cual la entrada y no agrega ni padding ni la longitud. La
        entrada debe ser exacta. */
      int cifrarArchivoExacto(std::ifstream &, char*);

      /** \brief Permite probar el funcionamiento del descifrado CBC, pues
        toma tal cual la entrada y no agrega ni padding ni la longitud. La
        entrada debe ser exacta. */
      int descifrarArchivoExacto(std::ifstream &, char*);

      /** \brief Regresa el último bloque cifrado mediante CBC. Úsese solo
        después de calcular el CBC residual o de haber cifrado un archivo
        exacto. */
      unsigned char* obtenerBloqueCifrado();
  };
}
#endif
