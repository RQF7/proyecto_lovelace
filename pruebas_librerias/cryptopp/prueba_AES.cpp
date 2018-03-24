/**
 * \file
 * \brief Prueba de AES, implementación, crypto++
 * Proyecto Lovelace.
 */

#include "cabeceras/prueba_AES.hh"
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <iostream>

using namespace std;
using namespace CryptoPP;
using namespace PruebasCryptopp;

/**/builds/69077700
 * Registra las funciones de prueba de AES en la lista de funciones a probar
 * que mantiene la clase de Prueba.
 */

PruebaAES::PruebaAES()
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Uso de constantes",
    PruebaAES::probarConstantes
  });
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Proceso de cifrado y descifrado",
    PruebaAES::probarCifradoDescifrado
  });
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "Comparación entre AES CBC y AES ECB para un solo bloque",
    PruebaAES::probarAESCBC
  });
}

/**
 * No es algo específico de AES, sino de todas las constantes de toda
 * la biblioteca. Las constantes siempre se especifícan con mayúsculas, y
 * son valores o enums estáticos de cada algoritmo; tiene sentido, dado que
 * no son valores que se espera que cambien mucho.
 *
 * En particular para las constantes de AES, solamente está implementado para
 * un solo tamaño de bloque (como el propio AES, no como Rijandael). Para
 * los tamaños de llave, en los que sí hay variaciones, se especifíca un
 * mínimo, un máximo, un valor por defecto y el tamaño del múltiplo (i. e.
 * el tamaño del intervalo entre un tamaño y el siguiente). Este formato
 * se utiliza para todas las demás constantes con variaciones en los demás
 * algoritmos.
 */

bool PruebaAES::probarConstantes()
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

/**
 * Genera una llave y un vector de inicialización de prueba (vacíos) y los
 * utiliza para cifrar y descifrar una cadena de prueba. Se utiliza el
 * modo de operación CBC.
 *
 * La construcción de una maquinaria de cifrado se realiza envolviendo
 * primitivas de bajo nivel en primitivas de alto nivel. Por ejemplo, para
 * construir el cifrador, primero se crea una instancia de AES::Encryption
 * que recibe la llave; esta instancia se le pasa al constructor de un
 * CBC_Mode_ExternalCipher, que también recibe el vector de inicialización.
 * Por último, el modo de operación se le pasa al constructor de un
 * StreamTransformationFilter que también recibe la cadena destino.
 * El proceso para el descifrado es análogo.
 */

bool PruebaAES::probarCifradoDescifrado()
{
  /* Obtener arreglos limpios para la llave y el vector de incialización. */
  byte llave[AES::DEFAULT_KEYLENGTH],
       vi[AES::BLOCKSIZE];
  memset(llave, 0, AES::DEFAULT_KEYLENGTH);
  memset(vi, 0, AES::BLOCKSIZE);

  /* Registro previo. */
  string textoEnClaro {"Esta es un prueba de cifrado con AES"},
         textoCifrado, textoDescifrado;
  cout << "Texto en claro (" << textoEnClaro.size() << " bytes):" << endl
       << "  " << textoEnClaro << endl;

  /* Proceso de cifrado. */
  AES::Encryption cifradoAES{llave, AES::DEFAULT_KEYLENGTH};
  CBC_Mode_ExternalCipher::Encryption cifradoCBC{cifradoAES, vi};
  StreamTransformationFilter cifradoFiltro{
    cifradoCBC,
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
  cout << "Llave:" << endl;
  for (auto caracter : llave)
    cout << "0x" << hex << (0xFF & caracter) << " ";
  cout << endl;
  cout << "Vector de inicialización:" << endl;
  for (auto caracter : vi)
    cout << "0x" << hex << (0xFF & caracter) << " ";
  cout << endl;

  /* Proceso de descifrado. */
  AES::Decryption descifradoAES{llave, AES::DEFAULT_KEYLENGTH};
  CBC_Mode_ExternalCipher::Decryption descifradoCBC{descifradoAES, vi};
  StreamTransformationFilter descifradoFiltro{
    descifradoCBC,
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
}

/**
 * Compara la salida de AES con CBC con la salida de AES con ECB.
 *
 * ECB (electronic codebook) es el equivalente más cercano a no usar ningún
 * modo de operación: dado que el vector de inicialización de CBC es 0,
 * el primer bloque de ambos textos cifrados debería ser igual.
 *
 * \note No importa que tan chico sea el mensaje a cifrar, las implementaciones
 * de los modos de operación siempre regresan un mensaje de al menos dos
 * bloques.
 *
 * \test Estado de la prueba.
 */

bool PruebaAES::probarAESCBC()
{
  /* Reservación de memoria. */
  byte llave[AES::DEFAULT_KEYLENGTH],
       vi[AES::BLOCKSIZE],
       textoEnClaro[2];
  memset(llave, 0, AES::DEFAULT_KEYLENGTH);
  memset(vi, 0, AES::BLOCKSIZE);
  memset(textoEnClaro, 50, 2);
  string textoCifradoECB, textoCifradoCBC;

  /* Cifrado con CBC. */
  AES::Encryption cifradoAESUno{llave, AES::DEFAULT_KEYLENGTH};
  CBC_Mode_ExternalCipher::Encryption cifradoCBC{cifradoAESUno, vi};
  StreamTransformationFilter cifradoFiltroUno{
    cifradoCBC,
    new StringSink(textoCifradoCBC)
  };
  cifradoFiltroUno.Put(
    reinterpret_cast<const unsigned char*>(textoEnClaro),
    AES::BLOCKSIZE
  );
  cifradoFiltroUno.MessageEnd();

  cout << "Texto cifrado con CBC (" << dec << textoCifradoCBC.size()
       << " bytes):" << endl;
  for (auto caracter : textoCifradoCBC)
    cout << "0x" << hex << (0xFF & static_cast<byte>(caracter)) << " ";
  cout << endl;

  /* Cifrado solo con AES. */
  AES::Encryption cifradoAESDos{llave, AES::DEFAULT_KEYLENGTH};
  ECB_Mode_ExternalCipher::Encryption cifradoECB{cifradoAESUno};
  StreamTransformationFilter cifradoFiltroDos {
    cifradoECB,
    new StringSink(textoCifradoECB)
  };
  cifradoFiltroDos.Put(
    reinterpret_cast<const unsigned char*>(textoEnClaro),
    AES::BLOCKSIZE
  );
  cifradoFiltroDos.MessageEnd();

  cout << "Texto cifrado con ECB (" << dec << textoCifradoECB.size()
       << " bytes):" << endl;
  for (auto caracter : textoCifradoECB)
    cout << "0x" << hex << (0xFF & static_cast<byte>(caracter)) << " ";
  cout << endl;

  if (textoCifradoECB.substr(0, 16) != textoCifradoCBC.substr(0, 16))
    return false;

  return true;
}
