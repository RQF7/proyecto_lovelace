/*
 * Prueba de AES, implementacón, crypto++
 * Proyecto Lovelace.
 */

#include "cabeceras/prueba_AES.hh"
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <iostream>

using namespace std;
using namespace CryptoPP;

bool probarConstantes()
{
  cout << "Tamaño de bloque: "              << AES::BLOCKSIZE           << endl
       << "Mínimo tamaño de llave: "        << AES::MIN_KEYLENGTH       << endl
       << "Máximo tamaño de llave: "        << AES::MAX_KEYLENGTH       << endl
       << "Tamaño de llave por defecto: "   << AES::DEFAULT_KEYLENGTH   << endl
       << "Múltiplo de longitud de llave: " << AES::KEYLENGTH_MULTIPLE  << endl
       << "Requerimiento de VI: "           << AES::IV_REQUIREMENT      << endl
       << "Longitud de VI: "                << AES::IV_LENGTH           << endl;
  return true;
}

bool probarCifradoDescifrado()
{
  /* Obtener arreglos limpios para la llave y el vector de incialización. */
  byte llave[AES::DEFAULT_KEYLENGTH],
       vi[AES::BLOCKSIZE];
  memset(llave, 0, AES::DEFAULT_KEYLENGTH);
  memset(vi, 0, AES::BLOCKSIZE);

  /* Registro previo. */
  string textoEnClaro = "Esta es un prueba de cifrado con AES",
         textoCifrado, textoDescifrado;
  cout << "Texto en claro (" << textoEnClaro.size() << " bytes):" << endl
       << "  " << textoEnClaro << endl;

  /* Proceso de cifrado. */
  AES::Encryption cifradoAES(llave, AES::DEFAULT_KEYLENGTH);
  CBC_Mode_ExternalCipher::Encryption cifradoCBC(cifradoAES, vi);
  StreamTransformationFilter cifradoFiltro(
    cifradoCBC,
    new StringSink(textoCifrado)
  );
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
  cout << "Llave:" << endl;
  for (auto caracter : llave)
    cout << "0x" << hex << (0xFF & caracter) << " ";
  cout << endl;
  cout << "Vector de inicialización:" << endl;
  for (auto caracter : vi)
    cout << "0x" << hex << (0xFF & caracter) << " ";
  cout << endl;

  /* Proceso de descifrado. */
  AES::Decryption descifradoAES(llave, AES::DEFAULT_KEYLENGTH);
  CBC_Mode_ExternalCipher::Decryption descifradoCBC(descifradoAES, vi);
  StreamTransformationFilter descifradoFiltro(
    descifradoCBC,
    new CryptoPP::StringSink(textoDescifrado)
  );
  descifradoFiltro.Put(
    reinterpret_cast<const unsigned char*>(textoCifrado.c_str()),
    textoCifrado.size()
  );
  descifradoFiltro.MessageEnd();

  /* Registro posterior. */
  cout << "Texto en claro (" << textoDescifrado.size() << " bytes):" << endl
       << "  " << textoDescifrado << endl;
  return true;
}

PruebaAES::PruebaAES()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "Uso de constantes",
    probarConstantes
  });
  mListaDePruebas.push_back(FuncionDePrueba{
    "Proceso de cifrado y descifrado",
    probarCifradoDescifrado
  });
}
