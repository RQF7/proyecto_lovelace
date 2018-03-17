/**
 * \file
 * \brief Prueba de Salsa20, implementacón, crypto++
 * Proyecto Lovelace.
 */

#include "cabeceras/prueba_salsa20.hh"
#include <cryptopp/drbg.h>
#include <cryptopp/filters.h>
#include <cryptopp/salsa.h>
#include <cryptopp/sha.h>
#include <iostream>

using namespace std;
using namespace CryptoPP;
using namespace PruebasCryptopp;

/**
 * Registra las funciones de prueba de Salsa20 en la lista de funciones a
 * probar que mantiene la clase de Prueba.
 */

PruebaSalsa20::PruebaSalsa20()
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Proceso de cifrado y descifrado",
    probarCifradoDescifrado
  });
}

/**
 * Implementación de cifrado y descifrado con Salsa20 (cifrador de flujo).
 * El código se parece bastante al cifrado y descifrado con AES, excepto
 * que aquí no se ocupa un modo de operación.
 *
 * Se usa un generador de números pseudoaleatorios: *Hash_DRBG*. Cryptopp
 * tiene otro montón de posibilidades, sin embargo, que estén aprobados por
 * el NIST son solo este y *HMAC_DRBG* (NIST 800-90).
 *
 * **NOTA:** el constructor del generador de bits aleatorios con hash marcó
 * error al compilar si no se le pasaban los argumentos del template, cuando
 * (cuando menos la versión del manual que tengo) indica que esos parámetros
 * tienen un valor por defecto (los mismos que estoy pasando).
 * Posiblemente sea por incompatibilidades de versiones, sin embargo, por lo
 * mientras decidí dejarlo así porque ejemplifica cómo usar los argumentos
 * de los templates.
 */

bool PruebaSalsa20::probarCifradoDescifrado()
{
  /* Configuración de llave y de VI. */
  byte llave[Salsa20::DEFAULT_KEYLENGTH], vi[Salsa20::IV_LENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, Salsa20::DEFAULT_KEYLENGTH);
  generadorAleatorio.GenerateBlock(vi, Salsa20::IV_LENGTH);

  /* Registro previo. */
  string textoEnClaro = "Esta es un prueba de cifrado con salsa roja",
         textoCifrado, textoDescifrado;
  cout << "Texto en claro (" << textoEnClaro.size() << " bytes):" << endl
       << "  " << textoEnClaro << endl;
    cout << "Llave:" << endl;
    for (auto caracter : llave)
      cout << "0x" << hex << (0xFF & caracter) << " ";
    cout << endl;
    cout << "Vector de inicialización:" << endl;
    for (auto caracter : vi)
      cout << "0x" << hex << (0xFF & caracter) << " ";
    cout << endl;

  /* Proceso de cifrado. */
  Salsa20::Encryption cifradoSalsa{llave, Salsa20::DEFAULT_KEYLENGTH, vi};
  StreamTransformationFilter cifradoFiltro{
    cifradoSalsa,
    new StringSink(textoCifrado)
  };
  cifradoFiltro.Put(
    reinterpret_cast<const unsigned char*>(textoEnClaro.c_str()),
    textoEnClaro.length() + 1
  );
  cifradoFiltro.MessageEnd();

  /* Registro medio. */
  cout << "Texto cifrado (" << textoCifrado.size() << " bytes):" << endl;
  for (auto caracter : textoCifrado)
    cout << "0x" << hex << (0xFF & static_cast<byte>(caracter)) << " ";
  cout << endl;

  /* Proceso de descifrado. */
  Salsa20::Decryption descifradoSalsa{llave, Salsa20::DEFAULT_KEYLENGTH, vi};
  StreamTransformationFilter descifradoFiltro{
    descifradoSalsa,
    new CryptoPP::StringSink(textoDescifrado)
  };
  descifradoFiltro.Put(
    reinterpret_cast<const unsigned char*>(textoCifrado.c_str()),
    textoCifrado.size()
  );
  descifradoFiltro.MessageEnd();

  /* Registro posterior. */
  cout << "Texto en claro (" << textoDescifrado.size() << " bytes):" << endl
       << "  " << textoDescifrado << endl;
  return true;

  return true;
}
