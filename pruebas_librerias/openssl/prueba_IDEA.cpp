/*
 * Prueba de AES, implementacón, openssl
 * Proyecto Lovelace.
 */

#include "cabeceras/prueba_IDEA.hh"
#include <openssl/evp.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;
using namespace PruebasOpenssl;

/**
 * Registra las funciones de prueba de IDEA en la lista de funciones a probar
 * que mantiene la clase de Prueba.
 */

PruebaIDEA::PruebaIDEA()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "Proceso de cifrado y descifrado",
    PruebaIDEA::probarCifradoDescifrado
  });
}

/**
 * Genea una llave y un vextor de inicialización para cifrar con IDEA en modo
 * CBC. Todo se hace a través de la (supuestamente de alto nivel) interfaz
 * «ENV». Supongo que para tratarse de código de C, sí se puede considerar
 * como «alto nivel»: todo el código de esta función es prácticamente el
 * mismo para cualquier tipo de cifrado por bloques que se quiera usar.
 *
 * La documentación es muy pobre: la gran mayoría son man pages con títulos
 * raros. Gran parte de este ejemplo salió de las *man pages* de openssl
 * (la entrada de EVP_aes).
 *
 * PD: el descifrado no tubo la amabilidad de quitar los bytes que puso
 * de padding el cifrado (cryptopp sí los quita).
 */

bool PruebaIDEA::probarCifradoDescifrado()
{
  /* Configuración de llave e VI. */
  unsigned char bufferSalida[1024];
  int longitudFinal, longitudTemporal;
  unsigned char llave[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  unsigned char vi[] = {1,2,3,4,5,6,7,8};
  string textoEnClaro{"Prueba de cifrado con IDEA"};

  /* Proceso de cifrado. */
  EVP_CIPHER_CTX *contextoCifrado;
  contextoCifrado = EVP_CIPHER_CTX_new();
  EVP_EncryptInit_ex(contextoCifrado, EVP_idea_cbc(), NULL, llave, vi);
  /* Para longitudes arbitrarias, esto tendría que ir en un ciclo. */
  EVP_EncryptUpdate(contextoCifrado, bufferSalida, &longitudFinal,
    reinterpret_cast<const unsigned char*>(textoEnClaro.c_str()),
    strlen(textoEnClaro.c_str()));
  /* :O Aritmética de apuntadores. Con esto se hacen virus. */
  EVP_EncryptFinal_ex(contextoCifrado, bufferSalida + longitudFinal,
    &longitudTemporal);
  longitudFinal += longitudTemporal;
  EVP_CIPHER_CTX_free(contextoCifrado);

  /* Registro inicial. */
  cout << "Texto en claro:" << endl << textoEnClaro << endl;
  cout << "Texto cifrado:" << endl;
  for (int i = 0; i < longitudFinal; i++)
    cout << "0x" << hex << (0xFF & bufferSalida[i]) << " ";
  cout << endl;

  unsigned char bufferRegreso[1024];
  int longitudFinalDec, longitudTemporalDec;

  /* Proceso de descifrado. */
  EVP_CIPHER_CTX *contextoDescifrado;
  contextoDescifrado = EVP_CIPHER_CTX_new();
  EVP_DecryptInit_ex(contextoDescifrado, EVP_idea_cbc(), NULL, llave, vi);
  EVP_DecryptUpdate(contextoDescifrado, bufferRegreso, &longitudFinalDec,
    bufferSalida, longitudFinal);
  EVP_DecryptFinal_ex(contextoDescifrado, bufferRegreso + longitudFinalDec,
    &longitudTemporalDec);
  longitudFinalDec += longitudTemporalDec;
  EVP_CIPHER_CTX_free(contextoDescifrado);

  /* Registro final. */
  string textoDescifrado{reinterpret_cast<const char*>(bufferRegreso)};
  cout << "Texto descifrado:" << endl << textoDescifrado << endl;
  /*for (int i = 0; i < longitudFinalDec; i++)
    cout << "0x" << hex << (0xFF & bufferRegreso[i]) << " ";
  cout << endl;*/

  return true;
}
