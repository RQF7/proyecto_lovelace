#include "cabeceras/aes.hh"
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
  AES cifrador = AES(AES_128);
  unsigned char mensaje[16];
  unsigned char* bloqueCifrado;
  unsigned char* bloqueClaro;

  unsigned char llave128[16] = { 0x10,0xa5,0x88,0x69,0xd7,0x4b,0xe5,0xa3,0x74,
                      0xcf,0x86,0x7c,0xfb,0x47,0x38,0x59}; 

  /*
   * Texto cifrado: 6d251e6944b051e04eaa6fb4dbf78465
   */ 

  unsigned char llave192[24] = { 0xe9,0xf0,0x65,0xd7,0xc1,0x35,0x73,0x58,0x7f,
                      0x78,0x75,0x35,0x7d,0xfb,0xb1,0x6c,0x53,0x48,0x9f,0x6a,
                      0x4b,0xd0,0xf7,0xcd};
  /*
   * Texto cifrado: 0956259c9cd5cfd0181cca53380cde06
   */ 

  unsigned char llave256[32] = { 0xc4,0x7b,0x02,0x94,0xdb,0xbb,0xee,0x0f,
                      0xec,0x47,0x57,0xf2,0x2f,0xfe,0xee,0x35,0x87,0xca,0x47,
                      0x30,0xc3,0xd3,0x3b,0x69,0x1d,0xf3,0x8b,0xab,0x07,0x6b,
                      0xc5,0x58};
  /*
   * Texto cifrado: 46f2fb342d6f0ab477476fc501242c5f
   */                       
  
  memset(mensaje, 0x00, 16);

  /* Prueba con llave de 128*/
  cifrador.ponerLlave(llave128);
  cifrador.cifrarBloque(mensaje);
  bloqueCifrado = cifrador.obtenerBloqueTCifrado();
  cout << bloqueCifrado;

  /* Prueba con llave de 192*/
  cifrador.ponerTamanioLlave(LLAVE_AES_192);
  cifrador.ponerLlave(llave192);
  cifrador.cifrarBloque(mensaje);
  bloqueCifrado = cifrador.obtenerBloqueTCifrado();
  cout << bloqueCifrado;

  /* Prueba con llave de 256*/
  cifrador.ponerTamanioLlave(LLAVE_AES_256);
  cifrador.ponerLlave(llave256);
  cifrador.cifrarBloque(mensaje);
  bloqueCifrado = cifrador.obtenerBloqueTCifrado();
  cout << bloqueCifrado ;

  return 1;
}