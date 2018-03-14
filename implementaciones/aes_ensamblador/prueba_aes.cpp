#include "cabeceras/aes.hh"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{
  unsigned char mensaje[TAM_BLOQUE];
  unsigned char *bloqueCifrado;
  unsigned char *bloqueClaro;

  unsigned char llave128[16] = { 0x10,0xa5,0x88,0x69,0xd7,0x4b,0xe5,0xa3,0x74,
                      0xcf,0x86,0x7c,0xfb,0x47,0x38,0x59};

  unsigned char textoCifrado128[16] = { 0x6d,0x25,0x1e,0x69,0x44,0xb0,0x51,
                      0xe0,0x4e,0xaa,0x6f,0xb4,0xdb,0xf7,0x84,0x65};

  unsigned char llave192[24] = { 0xe9,0xf0,0x65,0xd7,0xc1,0x35,0x73,0x58,0x7f,
                      0x78,0x75,0x35,0x7d,0xfb,0xb1,0x6c,0x53,0x48,0x9f,0x6a,
                      0x4b,0xd0,0xf7,0xcd};

  unsigned char textoCifrado192[16] = { 0x09,0x56,0x25,0x9c,0x9c,0xd5,0xcf,
                      0xd0,0x18,0x1c,0xca,0x53,0x38,0x0c,0xde,0x06};

  unsigned char llave256[32] = { 0xc4,0x7b,0x02,0x94,0xdb,0xbb,0xee,0x0f,
                      0xec,0x47,0x57,0xf2,0x2f,0xfe,0xee,0x35,0x87,0xca,0x47,
                      0x30,0xc3,0xd3,0x3b,0x69,0x1d,0xf3,0x8b,0xab,0x07,0x6b,
                      0xc5,0x58};

  unsigned char textoCifrado256[16] = { 0x46,0xf2,0xfb,0x34,0x2d,0x6f,0x0a,
                      0xb4,0x77,0x47,0x6f,0xc5,0x01,0x24,0x2c,0x5f};

  memset(mensaje, 0x00, 16);
  AES cifrador = AES(AES_128);

  /* Prueba con llave de 128*/
  cifrador.ponerLlave(llave128);
  cifrador.cifrarBloque(mensaje);
  bloqueCifrado = cifrador.obtenerBloqueTCifrado();
  for(int i=0; i<TAM_BLOQUE; i++)
  {
    if(bloqueCifrado[i] != textoCifrado128[i]){
      cout << "Error en el cifrado de 128 bits." << endl;
      exit(EXIT_FAILURE);
    }
  }
  cifrador.descifrarBloque(bloqueCifrado);
  bloqueClaro = cifrador.obtenerBloqueTClaro();
  for(int i=0; i<TAM_BLOQUE; i++)
  {
    if(bloqueClaro[i] != mensaje[i]){
      cout << "Error en el descifrado de 128 bits." << endl;
      exit(EXIT_FAILURE);
    }
  }
  cout << "Cifrado y descifrado con 128 bits exitoso." << endl;

  /* Prueba con llave de 192*/
  cifrador.ponerTamanioLlave(LLAVE_AES_192);
  cifrador.ponerLlave(llave192);
  cifrador.cifrarBloque(mensaje);
  bloqueCifrado = cifrador.obtenerBloqueTCifrado();
  for(int i=0; i<TAM_BLOQUE; i++)
  {
    if(bloqueCifrado[i] != textoCifrado192[i]){
      cout << "Error en el cifrado de 192 bits." << endl;
      exit(EXIT_FAILURE);
    }
  }
  cifrador.descifrarBloque(bloqueCifrado);
  bloqueClaro = cifrador.obtenerBloqueTClaro();
  for(int i=0; i<TAM_BLOQUE; i++)
  {
    if(bloqueClaro[i] != mensaje[i]){
      cout << "Error en el descifrado de 192 bits." << endl;
      exit(EXIT_FAILURE);
    }
  }
  cout << "Cifrado y descifrado con 192 bits exitoso." << endl;

  /* Prueba con llave de 256*/
  cifrador.ponerTamanioLlave(LLAVE_AES_256);
  cifrador.ponerLlave(llave256);
  cifrador.cifrarBloque(mensaje);
  bloqueCifrado = cifrador.obtenerBloqueTCifrado();
  for(int i=0; i<TAM_BLOQUE; i++)
  {
    if(bloqueCifrado[i] != textoCifrado256[i]){
      cout << "Error en el cifrado de 256 bits." << endl;
      exit(EXIT_FAILURE);
    }
  }
  cifrador.descifrarBloque(bloqueCifrado);
  bloqueClaro = cifrador.obtenerBloqueTClaro();
  for(int i=0; i<TAM_BLOQUE; i++)
  {
    if(bloqueClaro[i] != mensaje[i]){
      cout << "Error en el descifrado de 256 bits." << endl;
      exit(EXIT_FAILURE);
    }
  }
  cout << "Cifrado y descifrado con 256 bits exitoso." << endl;

  AES cifrador2 = AES(cifrador);
  cifrador2.cifrarBloque(mensaje);
  bloqueCifrado = cifrador2.obtenerBloqueTCifrado();
  for(int i=0; i<TAM_BLOQUE; i++)
  {
    if(bloqueCifrado[i] != textoCifrado256[i]){
      cout << "Error en el cifrado de 256 bits." << endl;
      exit(EXIT_FAILURE);
    }
  }
  cifrador2.descifrarBloque(bloqueCifrado);
  bloqueClaro = cifrador2.obtenerBloqueTClaro();
  for(int i=0; i<TAM_BLOQUE; i++)
  {
    if(bloqueClaro[i] != mensaje[i]){
      cout << "Error en el descifrado de 256 bits." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Constructor por copia funcionando correctamente." << endl;


  return 1;
}
