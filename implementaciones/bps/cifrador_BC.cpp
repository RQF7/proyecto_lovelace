/**
 * \file
 * \brief Implementación de la clase del cifrador BC.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/cifrador_BC.hh"

#include "cabeceras/utilidades.hh"
#include "cabeceras/codificador.hh"
#include "cabeceras/cifrador_de_ronda.hh"
#include <iostream>
#include <iomanip>
#include <vector>
#include <gmpxx.h>
#include <gmp.h>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

/* ========================================================================= */

CifradorBC::CifradorBC()
{
  for(int i=0; i<10; i++)
    mAlfabeto.push_back('0' + i);

  mCardinalidad = mAlfabeto.size();
  mTamBloque = 8;
  mNumRondas = 8;

  mCodificador.colocarAlfabeto(mAlfabeto);
}

/* ========================================================================= */

CifradorBC::CifradorBC(vector<char> alfabeto, unsigned int tamBloque,
                                              unsigned int numRondas)
{
  mAlfabeto     = alfabeto;
  mCardinalidad = alfabeto.size();
  mTamBloque   = tamBloque;
  mNumRondas   = numRondas;
  mCodificador.colocarAlfabeto(mAlfabeto);
}

/* ========================================================================= */

/**
 * Este método retorna el valor x de la cadena, donde x se define como:
 * la sumatoria desde 0 hasta la longitud de la cadena dada, de la
 * codificación de i-ésimo carácter por la cardinalidad s elevada a la i.
 */

mpz_class CifradorBC::componer(string mensaje)
{
  mpz_class res = 0, aux = 0;

  for(unsigned int i = 0; i < mensaje.size(); i++)
  {
    mpz_ui_pow_ui(aux.get_mpz_t(), mCardinalidad, i);
    res = res + (mCodificador.codificar(mensaje[i]) * aux);
  }

  return res;
}

/* ========================================================================= */

/**
 * Este método retorna la cadena original del número compuesto dado. Es el
 * método inverso a componer(string).
 */

string CifradorBC::descomponer(mpz_class numMensaje, unsigned int longitud)
{
  string res{""};
  mpz_class aux = 0;

  for(unsigned int i = 0; i < longitud; i++)
  {
    aux = numMensaje % mCardinalidad;
    res += mCodificador.decodificar((char)mpz_get_ui(aux.get_mpz_t()));
    numMensaje = (numMensaje - (numMensaje % mCardinalidad));
    numMensaje = numMensaje / mCardinalidad;
  }

  return res;
}

/* ========================================================================= */

/**
 * Este método sirve para cifrar la cadena dada con la llave y el tweak dados.
 * El funcionamiento de este método es el del cifrador interno BC del
 * algoritmo de cifrado que preserva el formato BPS.
 */

string CifradorBC::cifrar(string mensaje, byte llave[], mpz_class tweak)
{
  /* Mensaje de error para cuando la cadena dada es de una longitud
  distinta al tamaño de bloque */
  if(mensaje.size() != mTamBloque)
  {
    cout << "ERROR, cadena de longitud distinta a la establecida.";
    cout << endl;
    exit(-1);
  }

  Utilidades util;
  unsigned int l, r;
  string mensajeIzq{""};
  string mensajeDer{""};

  /* Obtención de las longitudes de la parte izquierda (l) y derecha (r)
  de la cadena dada para cifrar */
  l = (mTamBloque%2 == 0) ? mTamBloque/2 : (mTamBloque+1)/2;
  r = (mTamBloque%2 == 0) ? mTamBloque/2 : (mTamBloque-1)/2;

  /* Construcción de la parte izquierda y derecha del la cadena dada */
  for(unsigned int i=0; i<mTamBloque; i++)
    if(i<l) mensajeIzq += mensaje[i];
    else    mensajeDer += mensaje[i];

  /* Obtención de los valores de composición de la parte izquierda y derecha */
  mpz_class ladoIzq = componer(mensajeIzq);
  mpz_class ladoDer = componer(mensajeDer);

  /* Obtención los subtweaks izquierdo y derecho */
  mpz_class tweakDer = tweak & (0xFFFFFFFF);
  mpz_class tweakIzq = (tweak >> 32) & (0xFFFFFFFF);

  mpz_class tweakDerAux = 0;
  mpz_class tweakIzqAux = 0;
  mpz_class entradaCr   = 0;
  mpz_class salidaCr    = 0;
  mpz_class maxS1       = 0;
  mpz_class maxSR       = 0;
  string entradaCrStr   {""};
  string salidaCrStr    {""};

  /* Asignación de s^l y s^r en las variables maxS1 y maxSR */
  mpz_ui_pow_ui(maxS1.get_mpz_t(), mCardinalidad, l);
  mpz_ui_pow_ui(maxSR.get_mpz_t(), mCardinalidad, r);
  int tamCifradorDeRonda = mCifradorDeRonda.obtenerTamBloque();

  /* Ciclo de la red Feistel */
  for (unsigned int i = 0; i < mNumRondas; i++)
  {
    if (i % 2 == 0)
    {
      /* Corrimiento a la izquierda de f-32 bits del subtweak derecho
      xor con el contador, donde f es el tamaño de bloque del cifrador
      de ronda */
      tweakDerAux = (tweakDer ^ i) << (tamCifradorDeRonda - 32);

      /* Suma del subtweak recorrido con el lado derecho */
      entradaCr = tweakDerAux + ladoDer;
      entradaCrStr = util.numeroACadena(entradaCr);

      /* Cifrado de la suma anterior */
      salidaCrStr = mCifradorDeRonda.cifrar(entradaCrStr,llave);
      salidaCr = util.cadenaANumero(salidaCrStr);

      /* Suma modular del lado izquierdo con el resultado del
      cifrado anterior */
      ladoIzq = util.mod(ladoIzq, maxS1) + util.mod(salidaCr, maxS1);
      ladoIzq = util.mod(ladoIzq, maxS1);
    }
    else
    {
      /* Corrimiento a la izquierda de f-32 bits del subtweak izquierdo
      xor con el contador, donde f es el tamaño de bloque del cifrador
      de ronda */
      tweakIzqAux = (tweakIzq ^ i) << (tamCifradorDeRonda - 32);

      /* Suma del subtweak recorrido con el lado izquierdo */
      entradaCr = tweakIzqAux + ladoIzq;
      entradaCrStr = util.numeroACadena(entradaCr);

      /* Cifrado de la suma anterior */
      salidaCrStr = mCifradorDeRonda.cifrar(entradaCrStr, llave);
      salidaCr = util.cadenaANumero(salidaCrStr);

      /* Suma modular del lado derecho con el resultado del
      cifrado anterior */
      ladoDer = util.mod(ladoDer, maxSR) + util.mod(salidaCr, maxSR);
      ladoDer = util.mod(ladoDer, maxSR);
    }
  }

  /* Descomposición del lado izquierdo y derecho para concatenarlas y
  obtener la cadena cifrada */
  string mensajeCifrado;
  mensajeCifrado += descomponer(ladoIzq,l);
  mensajeCifrado += descomponer(ladoDer,r);
  return mensajeCifrado;
}

/* ========================================================================= */

/**
 * Este método sirve para descifrar la cadena dada con la llave y tweak dados.
 * El funcionamiento de este método es el del cifrador interno BC del
 * algoritmo de cifrado que preserva el formato BPS.
 */

string CifradorBC::descifrar(string mensaje, byte llave[], mpz_class tweak)
{
  /* Mensaje de error para cuando la cadena dada es de una longitud
  distinta al tamaño de bloque */
  if (mensaje.size() != mTamBloque)
  {
    cout << "ERROR, cadena de longitud distinta a la establecida.";
    cout << endl;
    exit(-1);
  }

  Utilidades util;
  unsigned int l, r;
  string mensajeIzq{""};
  string mensajeDer{""};

  /* Obtención de las longitudes de la parte izquierda (l) y derecha (r)
  de la cadena dada para descifrar */
  l = (mTamBloque % 2 == 0) ? mTamBloque / 2 : (mTamBloque + 1) / 2;
  r = (mTamBloque % 2 == 0) ? mTamBloque / 2 : (mTamBloque - 1) / 2;

  /* Construcción de la parte izquierda y derecha del la cadena dada */
  for (unsigned int i = 0; i < mTamBloque; i++)
    if (i < l) mensajeIzq += mensaje[i];
    else       mensajeDer += mensaje[i];

  /* Obtención de los valores de composición de la parte izquierda y derecha */
  mpz_class ladoIzq = componer(mensajeIzq);
  mpz_class ladoDer = componer(mensajeDer);

  /* Obtención los subtweaks izquierdo y derecho */
  mpz_class tweakDer = tweak & (0xFFFFFFFF);
  mpz_class tweakIzq = (tweak >> 32) & (0xFFFFFFFF);

  mpz_class tweakDerAux = 0;
  mpz_class tweakIzqAux = 0;
  mpz_class entradaCr   = 0;
  mpz_class salidaCr    = 0;
  mpz_class maxS1       = 0;
  mpz_class maxSR       = 0;
  string entradaCrStr  {""};
  string salidaCrStr   {""};

  /* Asignación de s^l y s^r en las variables maxS1 y maxSR */
  mpz_ui_pow_ui(maxS1.get_mpz_t(), mCardinalidad, l);
  mpz_ui_pow_ui(maxSR.get_mpz_t(), mCardinalidad, r);
  int tamCifradorDeRonda = mCifradorDeRonda.obtenerTamBloque();

  /* Ciclo de la red Feistel */
  for (int i = mNumRondas - 1; i >= 0; i--)
  {
    if (i % 2 == 0)
    {
      /* Corrimiento a la izquierda de f-32 bits del subtweak derecho
      xor con el contador, donde f es el tamaño de bloque del cifrador
      de ronda */
      tweakDerAux = (tweakDer ^ i) << (tamCifradorDeRonda - 32);

      /* Suma del subtweak recorrido con el lado derecho */
      entradaCr = tweakDerAux + ladoDer;
      entradaCrStr = util.numeroACadena(entradaCr);

      /* Cifrado de la suma anterior */
      salidaCrStr = mCifradorDeRonda.cifrar(entradaCrStr, llave);
      salidaCr = util.cadenaANumero(salidaCrStr);

      /* Resta modular del lado izquierdo con el resultado del
      cifrado anterior */
      ladoIzq = util.mod(ladoIzq, maxS1) - util.mod(salidaCr, maxS1);
      ladoIzq = util.mod(ladoIzq, maxS1);
    }
    else
    {
      /* Corrimiento a la izquierda de f-32 bits del subtweak izquierdo
      xor con el contador, donde f es el tamaño de bloque del cifrador
      de ronda */
      tweakIzqAux = (tweakIzq ^ i) << (tamCifradorDeRonda - 32);

      /* Suma del subtweak recorrido con el lado izquierdo */
      entradaCr = tweakIzqAux + ladoIzq;
      entradaCrStr = util.numeroACadena(entradaCr);

      /* Cifrado de la suma anterior */
      salidaCrStr = mCifradorDeRonda.cifrar(entradaCrStr, llave);
      salidaCr = util.cadenaANumero(salidaCrStr);

      /* Resta modular del lado derecho con el resultado del
      cifrado anterior */
      ladoDer = util.mod(ladoDer, maxSR) - util.mod(salidaCr, maxSR);
      ladoDer = util.mod(ladoDer, maxSR);
    }
  }

  /* Descomposición del lado izquierdo y derecho para concatenarlas y
  obtener la cadena descifrada */
  string mensajeDescifrado{""};
  mensajeDescifrado += descomponer(ladoIzq,l);
  mensajeDescifrado += descomponer(ladoDer,r);
  return mensajeDescifrado;
}

/* ========================================================================= */

vector<char> CifradorBC::obtenerAlfabeto()
{
  return mAlfabeto;
}

/* ========================================================================= */

unsigned int CifradorBC::obtenerTamBloque()
{
  return mTamBloque;
}

/* ========================================================================= */

unsigned int CifradorBC::obtenerNumRondas()
{
  return mNumRondas;
}

/* ========================================================================= */

CifradorDeRonda CifradorBC::obtenerCifradorDeRonda()
{
  return mCifradorDeRonda;
}

/* ========================================================================= */

void CifradorBC::colocarAlfabeto(vector<char> alfabeto)
{
  mAlfabeto = alfabeto;
  mCardinalidad = mAlfabeto.size();
  mCodificador.colocarAlfabeto(mAlfabeto);
}

/* ========================================================================= */

void CifradorBC::colocarTamBloque(unsigned int tamBloque)
{
  mTamBloque = tamBloque;
}

/* ========================================================================= */

void CifradorBC::colocarNumRondas(unsigned int numRondas)
{
  mNumRondas = numRondas;
}
