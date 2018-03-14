/**
 * Proyecto Lovelace.
 *
 * \file
 * \brief Implementación de AES mediante las instrucciones de Intel.
 *
 */
#include "cabeceras/aes.hh"
#include <fstream>
#include <math.h>
#include <string.h>
#include "libaesni/iaesni.h"

using namespace std;

/**
 * El constructor sin parámetros inicia a los arreglos de bloques en claro
 * y cifrado; además, el AES con un tamaño de llave de 192 bits y  reserva
 * el espacio para la llave.
 */
AES::AES()
{
  bloqueTClaro = new unsigned char [TAM_BLOQUE];
  bloqueTCifrado = new unsigned char [TAM_BLOQUE];

  this->tamLlave = LLAVE_AES_192;
  vectorLlave = new unsigned char[LLAVE_AES_192];
}

/**
 * El constructor primero inicia a los arreglos de bloques en claro
 * y cifrado; luego, según el tamaño de llave indicado en el parámetro,
 * inicia el espacio para la llave y actualiza el tamaño de llave.
 */
AES::AES(int tamLlave)
{
  bloqueTClaro = new unsigned char [TAM_BLOQUE];
  bloqueTCifrado = new unsigned char [TAM_BLOQUE];

  switch(tamLlave)
  {
    case AES_128:
      this->tamLlave = LLAVE_AES_128;
      vectorLlave = new unsigned char[LLAVE_AES_128];
      break;
    case AES_192:
      this->tamLlave = LLAVE_AES_192;
      vectorLlave = new unsigned char[LLAVE_AES_192];
      break;
    case AES_256:
      this->tamLlave = LLAVE_AES_256;
      vectorLlave = new unsigned char[LLAVE_AES_256];
      break;
  }
}

/**
 * El constructor recibe un objeto de tipo AES y crea una copia
 */
AES::AES(AES const& copia)
{
  bloqueTClaro = new unsigned char [TAM_BLOQUE];
  bloqueTCifrado = new unsigned char [TAM_BLOQUE];

  tamLlave = copia.tamLlave;
  vectorLlave = new unsigned char[copia.tamLlave];

  memcpy(vectorLlave, copia.vectorLlave, copia.tamLlave);
}

/**
 * El destructor libera el espacio que se había reservado para los bloques
 * de texto claro y cifrado, además del vector donde se almacena la llave.
 */
AES::~AES()
{
  //delete [] bloqueTClaro;
  //delete [] bloqueTCifrado;
  //delete [] vectorLlave;
}

/**
 * Libera el espaci para la llave que se tenía anteriormente y, dependiendo
 * del tamaño especificado, se encarga de reservar el espacio para la llave
 * y actualiza el tamaño de la llave. Si el tamaño de llave no corresponde
 * a uno válido (128, 192 o 256), se indica que el tamaño de la llave dado
 * no es válido.
 */
void AES::ponerTamanioLlave(int tamLlave)
{
  delete [] vectorLlave;

  switch(tamLlave)
  {
    case LLAVE_AES_128:
      this->tamLlave = LLAVE_AES_128;
      vectorLlave = new unsigned char[LLAVE_AES_128];
      break;
    case LLAVE_AES_192:
      this->tamLlave = LLAVE_AES_192;
      vectorLlave = new unsigned char[LLAVE_AES_192];
      break;
    case LLAVE_AES_256:
      this->tamLlave = LLAVE_AES_256;
      vectorLlave = new unsigned char[LLAVE_AES_256];
      break;
    default:
      cout << "Tamaño de llave incorrecto (" << tamLlave * 8 << ")." << endl;
  }
  return;
}

int AES::obtenerTamanioLlave()
{
  return tamLlave;
}

/**
 * Copia al vector llave la llave que se provee en el parámetro. No se
 * verifica que el tamaño de la llave provista concuerde con el tamaño de llave
 * guardado actualmente, así que hay que actualizar primero el tamaño de la
 * llave y después poner la llave.
 */
void AES::ponerLlave(unsigned char* vectorLlaveExterior)
{
  memcpy(vectorLlave, vectorLlaveExterior, tamLlave);
  return;
}

/**
 * Regresa un apuntador que contiene la llave que se está utilizando.
 */
unsigned char* AES::obtenerLlave()
{
  unsigned char *llave = new unsigned char[tamLlave];
  memcpy(llave, vectorLlave, tamLlave);
  return llave;
}


/**
 * Regresa un apuntador que contiene el bloque de texto en claro con el que
 * se está trabajando actualmente.
 */
unsigned char* AES::obtenerBloqueTClaro()
{
  unsigned char *bloqueTClaroExterior = new unsigned char[TAM_BLOQUE];
  memcpy(bloqueTClaroExterior, bloqueTClaro, TAM_BLOQUE);
  return bloqueTClaroExterior;
}


/**
 * Regresa un apuntador que contiene el bloque de texto cifrado con el que
 * se está trabajando actualmente.
 */
unsigned char* AES::obtenerBloqueTCifrado()
{
  unsigned char *bloqueTCifradoExterior = new unsigned char[TAM_BLOQUE];
  memcpy(bloqueTCifradoExterior, bloqueTCifrado, TAM_BLOQUE);
  return bloqueTCifradoExterior;
}


/**
 * Se encarga de cifrar con la llave actual, el bloque de texto claro que
 * se provee mediante los parámetros. Dependiendo del tamaño de llave, se
 * llama a la función correspondiente. El resultado es guardado en el bloque
 * de texto cifrado (bloqueTCifrado).
 */
int AES::cifrarBloque(unsigned char* bloqueTClaroExterior)
{
  bloqueTClaro = bloqueTClaroExterior;
//  memcpy(bloqueTClaro, bloqueTClaroExterior, TAM_BLOQUE);
  switch(tamLlave)
  {
    case LLAVE_AES_128:
      intel_AES_enc128(bloqueTClaro, bloqueTCifrado, vectorLlave, 1);
      break;
    case LLAVE_AES_192:
      intel_AES_enc192(bloqueTClaro, bloqueTCifrado, vectorLlave, 1);
      break;
    case LLAVE_AES_256:
      intel_AES_enc256(bloqueTClaro, bloqueTCifrado, vectorLlave, 1);
      break;
    default:
      cout << "Tamaño de llave inválido." << endl;
      return 0;
  }
  return 1;
}

/**
 * Se encarga de descifrar con la llave actual, el bloque de texto cifrado que
 * se provee mediante los parámetros. Dependiendo del tamaño de llave, se
 * llama a la función correspondiente. El resultado es guardado en el bloque
 * de texto claro (bloqueTClaro).
 */
int AES::descifrarBloque(unsigned char* bloqueTCifradoExterior)
{
  bloqueTCifrado = bloqueTCifradoExterior;
//  memcpy(bloqueTCifrado, bloqueTCifradoExterior, TAM_BLOQUE);
  switch(tamLlave)
  {
    case LLAVE_AES_128:
      intel_AES_dec128(bloqueTCifrado, bloqueTClaro, vectorLlave, 1);
      break;
    case LLAVE_AES_192:
      intel_AES_dec192(bloqueTCifrado, bloqueTClaro, vectorLlave, 1);
      break;
    case LLAVE_AES_256:
      intel_AES_dec256(bloqueTCifrado, bloqueTClaro, vectorLlave, 1);
      break;
    default:
      cout << "Tamaño de llave inválido." << endl;
      return 0;
  }
  return 1;
}
