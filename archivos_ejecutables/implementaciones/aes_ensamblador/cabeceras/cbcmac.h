#ifndef __CBCMAC_H__
#define __CBCMAC_H__

#define TAM_BLOQUE 16

#define AES_128 1
#define AES_192 2
#define AES_256 3

#include <fstream>
using namespace std;

char* obtenerNombreSalida(char*);

void leerBloque(ifstream&, long long int, int, unsigned char*);

void cifrarBloque(unsigned char*, unsigned char*, unsigned char*, int);

void xorSimple(unsigned char*, unsigned char*, unsigned char*);

unsigned char* leerLlave(ifstream&);

int determinarTamanioLlave(int);

unsigned char* cbcMac(ifstream&, unsigned char*, int);

#endif
