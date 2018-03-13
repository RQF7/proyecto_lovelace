#include "cabeceras/aes.hh"
#include <fstream>
#include <math.h>
#include <string.h>
#include "libaesni/iaesni.h" 

using namespace std;


AES::AES()
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

void AES::ponerLlave(unsigned char* vectorLlaveExterior)
{
  memcpy(vectorLlave, vectorLlaveExterior, tamLlave);
  return;
}

unsigned char* AES::obtenerLlave()
{
  unsigned char *llave = new unsigned char[tamLlave];
  memcpy(llave, vectorLlave, tamLlave);
  return llave;
}

unsigned char* AES::obtenerBloqueTClaro()
{
  unsigned char *bloqueTClaroExterior = new unsigned char[TAM_BLOQUE];
  memcpy(bloqueTClaroExterior, bloqueTClaro, TAM_BLOQUE);
  return bloqueTClaro;
}

unsigned char* AES::obtenerBloqueTCifrado()
{
  unsigned char *bloqueTCifradoExterior = new unsigned char[TAM_BLOQUE];
  memcpy(bloqueTCifradoExterior, bloqueTCifrado, TAM_BLOQUE);
  return bloqueTCifrado;
}

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
