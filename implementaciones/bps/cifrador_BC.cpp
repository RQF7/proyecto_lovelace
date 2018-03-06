/* ========================================================================= */
/* ============================== Cifrador BC ============================== */
/* ======================================================================daz */

/**
 * Proyecto Lovelace.
 * 
 * \file
 * \brief Implementación de la clase del cifrador BC.
 * 
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
    m_ALFABETO.push_back('0' + i);
  
  m_CARDINALIDAD = m_ALFABETO.size();
  m_TAM_BLOQUE = 8;
  m_NUM_RONDAS = 8;

  m_codificador.setAlfabeto(m_ALFABETO);
}

/* ========================================================================= */

CifradorBC::CifradorBC(vector<char> alfabeto, unsigned int tam_bloque, 
                                              unsigned int num_rondas)
{
  m_ALFABETO     = alfabeto;
  m_CARDINALIDAD = alfabeto.size();
  m_TAM_BLOQUE   = tam_bloque;
  m_NUM_RONDAS   = num_rondas;
  m_codificador.setAlfabeto(m_ALFABETO);
}

/* ========================================================================= */
/**
 * Este método retorna el valor x de la cadena, donde x se define como:
 * La sumatoria desde 0 hasta la longitud de la cadena dada, de la 
 * codificación de i-esimo carácter por la cardinalidad s elevada a la i. 
 */
mpz_class CifradorBC::componer(string mensaje)
{
  mpz_class res = 0, aux = 0;

  for(unsigned int i=0; i<mensaje.size(); i++)
  {
    mpz_ui_pow_ui(aux.get_mpz_t(), m_CARDINALIDAD,i);
    res = res + (m_codificador.codificar(mensaje[i]) * aux);
  }

  return res;
}

/* ========================================================================= */
/**
 * Este método retorna la cadena original del numero compuesto dado. Es el
 * método inverso a componer(string).
 */
string CifradorBC::descomponer(mpz_class num_mensaje, unsigned int longitud)
{
  string res{""};
  mpz_class aux = 0;
  
  for(unsigned int i=0; i<longitud; i++)
  {
    aux = num_mensaje % m_CARDINALIDAD;
    res += m_codificador.decodificar((char)mpz_get_ui(aux.get_mpz_t()));
    num_mensaje = (num_mensaje - (num_mensaje % m_CARDINALIDAD));
    num_mensaje = num_mensaje / m_CARDINALIDAD;
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
  if(mensaje.size() != m_TAM_BLOQUE)
  {
    cout << "ERROR, cadena de longitud distinta a la establecida.";
    cout << endl;
    exit(-1);   
  }

  Utilidades util;
  unsigned int l, r;
  string mensaje_izq{""};
  string mensaje_der{""};
  
  /* Obtención de las longitudes de la parte izquierda (l) y derecha (r) 
  de la cadena dada para cifrar */
  l = (m_TAM_BLOQUE%2 == 0) ? m_TAM_BLOQUE/2 : (m_TAM_BLOQUE+1)/2;
  r = (m_TAM_BLOQUE%2 == 0) ? m_TAM_BLOQUE/2 : (m_TAM_BLOQUE-1)/2;
  
  /* Construcción de la parte izquierda y derecha del la cadena dada */
  for(unsigned int i=0; i<m_TAM_BLOQUE; i++)
    if(i<l) mensaje_izq += mensaje[i];
    else    mensaje_der += mensaje[i];
  
  /* Obtención de los valores de composición de la parte izquierda y derecha */
  mpz_class lado_izq = componer(mensaje_izq);
  mpz_class lado_der = componer(mensaje_der);

  /* Obtención los subtweaks izquierdo y derecho */
  mpz_class tweak_der = tweak & (0xFFFFFFFF);
  mpz_class tweak_izq = (tweak >> 32) & (0xFFFFFFFF);

  mpz_class tweak_der_aux = 0;
  mpz_class tweak_izq_aux = 0;
  mpz_class entrada_cr    = 0;
  mpz_class salida_cr     = 0;
  mpz_class max_sl        = 0;
  mpz_class max_sr        = 0;
  string entrada_cr_str   {""};
  string salida_cr_str    {""};

  /* Asignación de s^l y s^r en las variables max_sl y max_sr */
  mpz_ui_pow_ui(max_sl.get_mpz_t(), m_CARDINALIDAD, l);
  mpz_ui_pow_ui(max_sr.get_mpz_t(), m_CARDINALIDAD, r);
  int tam_cifrador_de_ronda = m_CIFRADOR_DE_RONDA.getTamBloque();

  /* Ciclo de la red Feistel */
  for(unsigned int i=0; i<m_NUM_RONDAS; i++)
  {
    if(i%2 == 0)
    {
      /* Corrimiento a la izquierda de f-32 bits del subtweak derecho 
      xor con el contador, donde f es el tamaño de bloque del cifrador 
      de ronda */
      tweak_der_aux = (tweak_der ^ i) << (tam_cifrador_de_ronda-32);
      
      /* Suma del subtweak recorrido con el lado derecho */
      entrada_cr = tweak_der_aux + lado_der;
      entrada_cr_str = util.numToString(entrada_cr);
  
      /* Cifrado de la suma anterior */
      salida_cr_str = m_CIFRADOR_DE_RONDA.cifrar(entrada_cr_str,llave); 
      salida_cr = util.stringToNum(salida_cr_str);

      /* Suma modular del lado izquierdo con el resultado del 
      cifrado anterior */
      lado_izq = util.mod(lado_izq,max_sl) + util.mod(salida_cr,max_sl); 
      lado_izq = util.mod(lado_izq, max_sl); 

    }
    else
    {
      /* Corrimiento a la izquierda de f-32 bits del subtweak izquierdo 
      xor con el contador, donde f es el tamaño de bloque del cifrador 
      de ronda */
      tweak_izq_aux = (tweak_izq ^ i) << (tam_cifrador_de_ronda-32);
      
      /* Suma del subtweak recorrido con el lado izquierdo */
      entrada_cr = tweak_izq_aux + lado_izq;
      entrada_cr_str = util.numToString(entrada_cr);
      
      /* Cifrado de la suma anterior */
      salida_cr_str = m_CIFRADOR_DE_RONDA.cifrar(entrada_cr_str,llave); 
      salida_cr = util.stringToNum(salida_cr_str);
      
      /* Suma modular del lado derecho con el resultado del 
      cifrado anterior */
      lado_der = util.mod(lado_der,max_sr) + util.mod(salida_cr,max_sr); 
      lado_der = util.mod(lado_der, max_sr); 

    }
  }

  /* Descomposición del lado izquierdo y derecho para concatenarlas y 
  obtener la cadena cifrada */
  string mensaje_cifrado;
  mensaje_cifrado += descomponer(lado_izq,l);
  mensaje_cifrado += descomponer(lado_der,r);
  return mensaje_cifrado;
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
  if(mensaje.size() != m_TAM_BLOQUE)
  {
    cout << "ERROR, cadena de longitud distinta a la establecida.";
    cout << endl;
    exit(-1);   
  }

  Utilidades util;
  unsigned int l, r;
  string mensaje_izq{""};
  string mensaje_der{""};

  /* Obtención de las longitudes de la parte izquierda (l) y derecha (r) 
  de la cadena dada para descifrar */
  l = (m_TAM_BLOQUE%2 == 0) ? m_TAM_BLOQUE/2 : (m_TAM_BLOQUE+1)/2; 
  r = (m_TAM_BLOQUE%2 == 0) ? m_TAM_BLOQUE/2 : (m_TAM_BLOQUE-1)/2;
  
  /* Construcción de la parte izquierda y derecha del la cadena dada */
  for(unsigned int i=0; i<m_TAM_BLOQUE; i++)
    if(i<l) mensaje_izq += mensaje[i];
    else    mensaje_der += mensaje[i];
  
  /* Obtención de los valores de composición de la parte izquierda y derecha */
  mpz_class lado_izq = componer(mensaje_izq);
  mpz_class lado_der = componer(mensaje_der);

  /* Obtención los subtweaks izquierdo y derecho */
  mpz_class tweak_der = tweak & (0xFFFFFFFF);
  mpz_class tweak_izq = (tweak >> 32) & (0xFFFFFFFF);

  mpz_class tweak_der_aux = 0;
  mpz_class tweak_izq_aux = 0;
  mpz_class entrada_cr    = 0;
  mpz_class salida_cr     = 0;
  mpz_class max_sl        = 0;
  mpz_class max_sr        = 0;
  string entrada_cr_str  {""};
  string salida_cr_str   {""};

  /* Asignación de s^l y s^r en las variables max_sl y max_sr */
  mpz_ui_pow_ui(max_sl.get_mpz_t(), m_CARDINALIDAD, l);
  mpz_ui_pow_ui(max_sr.get_mpz_t(), m_CARDINALIDAD, r);
  int tam_cifrador_de_ronda = m_CIFRADOR_DE_RONDA.getTamBloque();

  /* Ciclo de la red Feistel */
  for(int i=m_NUM_RONDAS-1; i>=0; i--)
  {
    if(i%2 == 0)
    {
      /* Corrimiento a la izquierda de f-32 bits del subtweak derecho 
      xor con el contador, donde f es el tamaño de bloque del cifrador 
      de ronda */
      tweak_der_aux = (tweak_der ^ i) << (tam_cifrador_de_ronda-32);
    
      /* Suma del subtweak recorrido con el lado derecho */
      entrada_cr = tweak_der_aux + lado_der;
      entrada_cr_str = util.numToString(entrada_cr);
  
      /* Cifrado de la suma anterior */
      salida_cr_str = m_CIFRADOR_DE_RONDA.cifrar(entrada_cr_str,llave); 
      salida_cr = util.stringToNum(salida_cr_str);

      /* Resta modular del lado izquierdo con el resultado del 
      cifrado anterior */
      lado_izq = util.mod(lado_izq,max_sl) - util.mod(salida_cr,max_sl); 
      lado_izq = util.mod(lado_izq, max_sl); 
  
    }
    else
    {
      /* Corrimiento a la izquierda de f-32 bits del subtweak izquierdo 
      xor con el contador, donde f es el tamaño de bloque del cifrador 
      de ronda */
      tweak_izq_aux = (tweak_izq ^ i) << (tam_cifrador_de_ronda-32);

      /* Suma del subtweak recorrido con el lado izquierdo */
      entrada_cr = tweak_izq_aux + lado_izq;
      entrada_cr_str = util.numToString(entrada_cr);
  
      /* Cifrado de la suma anterior */
      salida_cr_str = m_CIFRADOR_DE_RONDA.cifrar(entrada_cr_str,llave); 
      salida_cr = util.stringToNum(salida_cr_str);

      /* Resta modular del lado derecho con el resultado del 
      cifrado anterior */
      lado_der = util.mod(lado_der,max_sr) - util.mod(salida_cr,max_sr); 
      lado_der = util.mod(lado_der, max_sr); 

    }
  }

  /* Descomposición del lado izquierdo y derecho para concatenarlas y 
  obtener la cadena descifrada */
  string mensaje_descifrado{""};
  mensaje_descifrado += descomponer(lado_izq,l);
  mensaje_descifrado += descomponer(lado_der,r);
  return mensaje_descifrado;
}

/* ========================================================================= */

vector<char> CifradorBC::getAlfabeto(){
  return m_ALFABETO;
}

/* ========================================================================= */

unsigned int CifradorBC::getTamBloque(){
  return m_TAM_BLOQUE;
}

/* ========================================================================= */

unsigned int CifradorBC::getNumRondas(){
  return m_NUM_RONDAS;
}

/* ========================================================================= */

CifradorDeRonda CifradorBC::getCifradorDeRonda(){
  return m_CIFRADOR_DE_RONDA;
}

/* ========================================================================= */

void CifradorBC::setAlfabeto(vector<char> alfabeto){
  m_ALFABETO = alfabeto;
  m_CARDINALIDAD = m_ALFABETO.size();
  m_codificador.setAlfabeto(m_ALFABETO);
}

/* ========================================================================= */

void CifradorBC::setTamBloque(unsigned int tam_bloque){
  m_TAM_BLOQUE = tam_bloque;
}

/* ========================================================================= */

void CifradorBC::setNumRondas(unsigned int num_rondas){
  m_NUM_RONDAS = num_rondas;
}

/* ========================================================================= */
