/**
 * \file
 * \brief Prueba de SHA256, implementación, crypto++
 * Proyecto Lovelace
 */

#include "cabeceras/prueba_SHA256.hh"
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>

using namespace std;
using namespace CryptoPP;
using namespace PruebasCryptopp;

/**
 * Registra las funciones de prueba de SHA256 en la lista de funciones a probar
 * que mantiene la clase base.
 */

PruebaSHA256::PruebaSHA256()
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Obtener la digestión del mensaje",
    PruebaSHA256::probarDigestion
  });
}

/**
 * Primero, en entrada se define la cadena a la que se le va a sacar el SHA.
 * Luego, se define el vector de prueba para la cadena de entrada y poder
 * comprobar que da el valor correcto.
 * Luego, se define un arreglo de bytes donde se va a guardar la salida de
 * la función y el codificador que permite ver los datos en base hexadecimal:
 * la salida del codificador va a dar a la cadena <<salidaClara>>.
 * Luego, mediante la función Update, se le dan los datos de entrada a la
 * función SHA256 (sus argumentos son la cadena visto como un arreglo de bytes
 * y la longitud de la cadena); si la entrada está fragmentada o se le quiere
 * dar fragmentada, se utiliza la función Update varias veces y es equivalente
 * a ir concatenando la entrada. Una vez que se termina de dar la entrada,
 * se llama a la función Final y se le indica, mediante el argumento, dónde
 * se desea poner el valor hash. Al final se muestra la entrada y salida
 * obtenida en hexadecimal y se compara la salida con el vector de prueba:
 * regresa verdadero si coinciden o falso si la cadena del vector de prueba
 * es distinta a la que hay en la salida clara.
 */

bool PruebaSHA256::probarDigestion()
{
  string entrada {"abc"},
    vectorPrueba {"BA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD"},
    salidaClara;

  byte salida[SHA256::DIGESTSIZE];

  SHA256 sha256;
  HexEncoder hex(new StringSink(salidaClara));

  /* Obtener valor SHA256 de la cadena entrada**/
  sha256.Update(
    reinterpret_cast<const unsigned char*>(entrada.c_str()),
    entrada.length()
  );
  sha256.Final(salida);

  /* Mostrar entrada */
  cout << "Entrada: " << entrada << endl;

  /* Mostrar salida en base hexadecimal */
  hex.Put(salida, sizeof(salida));
  hex.MessageEnd();
  cout << "Salida: " << salidaClara << endl;

  return !vectorPrueba.compare(salidaClara);
}
