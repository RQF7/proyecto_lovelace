/* ========================================================================= */
/* ============================== Cifrador BPS ============================= */
/* ======================================================================daz */

/**
 * Proyecto Lovelace.
 * 
 * \file
 * \brief Implementación de la clase del cifrador BPS.
 * 
 */

#include "cabeceras/cifrador_BPS.hh"

#include "cabeceras/utilidades.hh"
#include "cabeceras/codificador.hh"
#include "cabeceras/cifrador_BC.hh"
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <gmpxx.h>
#include <gmp.h>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

/* ========================================================================= */

CifradorBPS::CifradorBPS(vector<char> alfabeto, unsigned int num_rondas)
{
  m_ALFABETO    = alfabeto;
  m_NUM_RONDAS  = num_rondas;
  m_codificador.setAlfabeto(m_ALFABETO);
}

/* ========================================================================= */
/**
 * Este método sirve para cifrar la cadena dada con la llave y el tweak dados.
 * El funcionamiento de este método es el del modo de operación del algoritmo
 * de cifrado que preserva el formato BPS.
 */
string CifradorBPS::cifrar(string mensaje, byte llave[], mpz_class tweak)
{
  CifradorBC BC;
  int tam_cifrador_de_ronda = BC.getCifradorDeRonda().getTamBloque();

  /* Obtención del tamaño máximo de bloque del cifrador interno BC */
  unsigned int tam_total, tam_max;
  tam_total  = mensaje.size();
  tam_max = 2 * ((tam_cifrador_de_ronda-32)*log(2))/log(m_ALFABETO.size());

  /* Configuración del cifrador interno BC */
  BC.setAlfabeto(m_ALFABETO);
  BC.setTamBloque(tam_max);
  BC.setNumRondas(m_NUM_RONDAS);  

  /* En caso de que la cadena dada tenga una longitud menor al tamaño máximo 
  del cifrador BC, simplemente se cifra la cadena con BC */
  if(tam_total <= tam_max)
  {
    BC.setTamBloque(tam_total);
    return BC.cifrar(mensaje,llave,tweak);
  }

  string bloque_a     {""};
  string salida       {""};
  string salida_final {""};

  unsigned int num_bloques = tam_total / tam_max;
  unsigned int tam_ultimo_bloque = tam_total % tam_max;
  mpz_class contador_u = 0;
  mpz_class tweak_u = 0;
  
  /* En caso de que la cadena dada tenga una longitud mayor al tamaño máximo 
  del cifrador BC, se van cifrando bloques x de longitud igual a la longitud 
  máxima de BC, donde x es igual a la suma modular de un bloque i con un 
  bloque i-1 */
  BC.setTamBloque(tam_max);
  for(unsigned int i=0; i<num_bloques; i++)
  {
    /* Xor del contador u = 2^16 + 2^48 con el tweak que entrara 
    al cifrador BC */
    contador_u = i;
    contador_u = (contador_u << 16) + (contador_u << 48);
    tweak_u = tweak^contador_u;
    
    /* Cifrado de la suma modular del bloque i con el bloque i-1 */
    bloque_a = mensaje.substr(i*tam_max,tam_max);
    salida = BC.cifrar(m_codificador.sumaMod(bloque_a,salida),llave,tweak_u);
    salida_final += salida;
  }

  /* En caso de que la cadena dada tenga una longitud que no es múltiplo 
  del tamaño máximo de BC, el ultimo bloque se cifra configurando BC 
  a su longitud */
  if(tam_ultimo_bloque != 0)
  {
    /* Xor del contador u = 2^16 + 2^48 con el tweak que entrara 
    al cifrador BC */
    BC.setTamBloque(tam_ultimo_bloque);
    contador_u = num_bloques;
    contador_u = (contador_u << 16) + (contador_u << 48);
    tweak_u = tweak^contador_u;
    
    /* Cifrado de la suma modular del bloque i con el bloque i-1 */
    bloque_a = mensaje.substr(tam_total-tam_ultimo_bloque,tam_ultimo_bloque);
    salida = BC.cifrar(m_codificador.sumaMod(bloque_a,salida),llave,tweak_u);
    salida_final += salida;
  }
  
  return salida_final;
}

/* ========================================================================= */
/**
 * Este método sirve para descifrar la cadena dada con la llave y tweak dados.
 * El funcionamiento de este método es el del modo de operación del algoritmo
 * de cifrado que preserva el formato BPS.
 */
string CifradorBPS::descifrar(string mensaje, byte llave[], mpz_class tweak)
{
  CifradorBC BC;
  int tam_cifrador_de_ronda = BC.getCifradorDeRonda().getTamBloque();

  /* Obtención del tamaño máximo de bloque del cifrador interno BC */
  unsigned int tam_total, tam_max;
  tam_total  = mensaje.size();
  tam_max = 2 * ((tam_cifrador_de_ronda-32)*log(2))/log(m_ALFABETO.size());

  /* Configuración del cifrador interno BC */
  BC.setAlfabeto(m_ALFABETO);
  BC.setTamBloque(tam_max);
  BC.setNumRondas(m_NUM_RONDAS);  

  /* En caso de que la cadena dada tenga una longitud menor al tamaño máximo 
  del cifrador BC, simplemente se descifra la cadena con BC */
  if(tam_total <= tam_max)
  {
    BC.setTamBloque(tam_total);
    return BC.descifrar(mensaje,llave,tweak);
  }

  string bloque_a     {""};
  string bloque_b     {""};
  string salida       {""};
  string salida_final {""};

  unsigned int num_bloques = tam_total / tam_max;
  unsigned int tam_ultimo_bloque = tam_total % tam_max;
  mpz_class contador_u = 0;
  mpz_class tweak_u = 0;
  
  /* En caso de que la cadena dada tenga una longitud que no es múltiplo 
  del tamaño máximo de BC, el ultimo bloque se descifra configurando BC 
  a su longitud */
  if(tam_ultimo_bloque != 0)
  {
    /* Xor del contador u = 2^16 + 2^48 con el tweak que entrara 
    al cifrador BC */
    BC.setTamBloque(tam_ultimo_bloque);
    contador_u = num_bloques;
    contador_u = (contador_u << 16) + (contador_u << 48);
    tweak_u = tweak^contador_u;
    
    /* Obtención del bloque i e i-1 */
    bloque_b = mensaje.substr(tam_total-tam_ultimo_bloque,tam_ultimo_bloque);
    bloque_a = mensaje.substr((num_bloques-1)*tam_max,tam_max);
    
    /* Resta modular del resultado de decifrar el bloque i, menor el bloque i-1 */
    salida = m_codificador.restaMod(BC.descifrar(bloque_b,llave,tweak_u),bloque_a);
    salida_final = salida + salida_final;
  }
  
  /* En caso de que la cadena dada tenga una longitud mayor al tamaño máximo 
  del cifrador BC, se van obteniendo bloques descifrados x de longitud igual 
  a la longitud máxima de BC, donde x es igual a la resta modular del 
  resultado de descifrar un bloque un bloque i con un bloque i-1 */
  BC.setTamBloque(tam_max);
  for(int i=num_bloques-1; i>0; i--)
  {
    /* Xor del contador u = 2^16 + 2^48 con el tweak que entrara 
    al cifrador BC */
    contador_u = i;
    contador_u = (contador_u << 16) + (contador_u << 48);
    tweak_u = tweak^contador_u;
    
    /* Obtención del bloque i e i-1 */
    bloque_b = mensaje.substr(i*tam_max,tam_max);
    bloque_a = mensaje.substr((i-1)*tam_max,tam_max);
    
    /* Resta modular del resultado de decifrar el bloque i, menor el bloque i-1 */
    salida = m_codificador.restaMod(BC.descifrar(bloque_b,llave,tweak_u),bloque_a);
    salida_final = salida + salida_final;
  }

  /* Descifrado del primer bloque en caso de que la cadena dada fuese de una 
  longitud mayor al tamaño máximo del cifrador BC */
  bloque_a = mensaje.substr(0,tam_max);
  salida = BC.descifrar(bloque_a,llave,tweak);
  salida_final = salida + salida_final;

  return salida_final;
}

/* ========================================================================= */

vector<char> CifradorBPS::getAlfabeto(){
  return m_ALFABETO;
}

/* ========================================================================= */

unsigned int CifradorBPS::getNumRondas(){
  return m_NUM_RONDAS;
}

/* ========================================================================= */

void CifradorBPS::setAlfabeto(vector<char> alfabeto){
  m_ALFABETO = alfabeto;
  m_codificador.setAlfabeto(m_ALFABETO);
}

/* ========================================================================= */

void CifradorBPS::setNumRondas(unsigned int num_rondas){
  m_NUM_RONDAS = num_rondas;
}

/* ========================================================================= */
