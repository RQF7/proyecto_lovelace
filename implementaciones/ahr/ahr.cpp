#include "cabeceras/ahr.hh"
#include "../aes_ensamblador/cabeceras/aes.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../utilidades/cabeceras/utilidades_tarjetas.hh"
#include "../acceso_a_datos/cabeceras/registro.hh"
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace CryptoPP;
using namespace Implementaciones;
using namespace std;

/**
 * Constructor por defecto. Se encarga de inicializar los bloques bloqueT y
 * bloqueC. El único parámetro que recibe un entero N que indica el Número
 * de bits necesarios para poder almacenar la entradaX.
 */
AHR::AHR(CDV* baseDeDatos)
: accesoADatos{baseDeDatos}
{
  bloqueT = new unsigned char[M];
  bloqueC = new unsigned char[M];
}

/**
 * Se encarga de crear un objeto a partir de
 * otro ya existente. Ambos objetos quedan utilizables.
 */
AHR::AHR(AHR const& otro)
{
  bloqueT = new unsigned char[M];
  memcpy(bloqueT, otro.bloqueT, M);

  bloqueC = new unsigned char[M];
  memcpy(bloqueC, otro.bloqueC, M);

  entradaX = otro.entradaX;
  entradaU = otro.entradaU;

  accesoADatos = otro.accesoADatos;
}

/**
 * Caso especial del operador de asignación donde
 * la fuente y el destino son del mismo tipo. A diferencia del constructor
 * por copia, limpia los miembros antes de asignarlos.
 */
AHR& AHR::operator=(AHR const& otro)
{
  unsigned char *auxiliar1 = new unsigned char[M];
  memcpy(auxiliar1, otro.bloqueT, M);
  delete [] bloqueT;
  bloqueT = auxiliar1;

  unsigned char *auxiliar2 = new unsigned char[M];
  memcpy(auxiliar2, otro.bloqueC, M);
  delete [] bloqueC;
  bloqueC = auxiliar2;

  entradaX = otro.entradaX;
  entradaU = otro.entradaU;

  accesoADatos = otro.accesoADatos;

  return *this;
}

/**
 * Se encarga de liberar la memoria reservada por los constructores.
 */
AHR::~AHR()
{
  delete [] bloqueT;
  delete [] bloqueC;
}

/**
  * Este método se encarga de <<romper>> el PAN y obtener el IIN, el número
  * de cuenta y, tomándolos en cuenta, determina los valores de L y N.
  */
void AHR::separarPAN(char *PAN)
{
  viejoPAN = string(PAN);
  L = strlen(PAN) - 6 - 1;

  char *auxU = new char[6];
  char *auxX = new char[L];

  memcpy(auxU, PAN, 6);
  memcpy(auxX, PAN+6, L);

  entradaU = stoull(auxU);
  entradaX = stoull(auxX);

  N = ceil(ceil(log2(pow(10, L))) / 8.0);

  delete [] auxU;
  delete [] auxX;
}

/**
  * Este método se encarga de completar el PAN una vez que se ha obtenido
  * el token. Al IIN del PAN original le concatena el token obtenido y
  * recalcula el dígito verificador mediante el algoritmo de Luhn desfasado
  * por uno.
  */
void AHR::completarToken()
{
  nuevoPAN =  to_string(entradaU) + to_string(token);
  ArregloDeDigitos temporal = ArregloDeDigitos(nuevoPAN);

  nuevoPAN += to_string(algoritmoDeLuhn(temporal, false));
}

/**
  * Este método se encarga de poner en los últimos N bytes del bloqueT
  * la entradaX en binario. Utiliza una máscara que inicia con un uno en la
  * posición más significativa y va haciendo un corrimiento hacia la derecha,
  * comparando con la entradaX; si encuentra un uno en la posición
  * correspondiente, mascaraByte se encarga de poner un uno en el bit j del
  * byte i correspondiente.
  */
void AHR::obtenerBitsX()
{
  memset(bloqueT, 0x00, M);
  unsigned long long int mascara =
    (unsigned long long int) pow((long double)2, (long double)(8*N)-1);
  unsigned char mascaraByte;

  for(int i = M-N; i < M; i++)
  {
    mascaraByte = 0x80;
    for(int j = 0; j < 8; j++)
    {
      if(mascara & entradaX)
      {
        bloqueT[i] = bloqueT[i]|mascaraByte;
      }
      mascaraByte = mascaraByte >> 1;
      mascara = mascara >> 1;
    }
  }
}

/**
  * Este método se encarga del primer paso del algoritmo: obtener el bloqueT
  * que será utilizado como entrada para el cifrador por bloques. Primero
  * obtiene la salida de la función pública (SHA256 en este caso) de la entrada
  * adicional entradaU. Luego llama a la función obtenerBitsX para llenar los
  * últimos N bloques del bloqueT y, finalmente, le concatena al inicio los
  * bytes más significativos de la salida del SHA para completar el tamaño
  * de bloque del cifrador.
  */
void AHR::crearBloqueT()
{
  string cadenaU  = to_string(entradaU);
  SHA256 funcionF;
  byte salidaFCompleta[SHA256::DIGESTSIZE];

  /* Obtener valor SHA256 de la entrada adicional**/
  funcionF.Update(
    reinterpret_cast<const unsigned char*>(cadenaU.c_str()),
    cadenaU.length()
  );
  funcionF.Final(salidaFCompleta);

  obtenerBitsX();

  int j = 0;
  for(int i=0; i < M - N; i++)
  {
    bloqueT[i] = salidaFCompleta[j];
    j++;
  }
}

/**
 * Se encarga de obtener la representación decimal de los últimos N bits del
 * bloqueC. Guarda el resultado en el entero token.
 */
void AHR::obtenerNumeroC()
{
  unsigned char mascara;
  unsigned long long int auxiliar;
  unsigned long long int auxiliar2 = (8*N)-1;
  token = 0;

  for(int i = M-N; i < M; i++)
  {
    mascara = 0x80;
    for(int j = 8; j > 0; j--)
    {
      if(mascara & bloqueC[i])
      {
        auxiliar =
          (unsigned long long int) pow((long double)2, (long double)auxiliar2);
        token += auxiliar;
      }
      mascara = mascara >> 1;
      auxiliar2 -= 1;
    }
  }
}

/**
 * Se encarga de revisar si el token creado existe en la base de datos.
 */
bool AHR::existeToken()
{
  completarToken();
  ArregloDeDigitos token_arreglo = ArregloDeDigitos(this->nuevoPAN);
  Registro busqueda = accesoADatos->buscarPorToken(token_arreglo);

  if (busqueda.obtenerToken() != Arreglo<int>{})
  {
    /* El token creado ya existe en la base de datos.
     * Se regresa verdadero para que el algoritmo cree un nuevo token.
     */
    return true;
  }
  else
  {
    /* El token creado no existe en la base de datos.
     * Se guarda la relación token - pan en la base de datos.
     */
    ArregloDeDigitos pan_arreglo = ArregloDeDigitos(this->viejoPAN);
    busqueda.colocarToken(token_arreglo);
    busqueda.colocarPAN(pan_arreglo);
    accesoADatos->guardar(busqueda);
    return false;
  }
}

/**
 * Método principal que se encarga de crear el token. Primero inicializa las
 * entradas entradaX y entradaU, y pone la llave a utilizar en el cifrador.
 * Luego comienza con el algoritmo:
 * 1. Crea el bloqueT al concatenar la salida truncada del SHA256 (alimentada
 *    con entradaU) y la representación binaria de entradaX.
 * 2. Realiza al menos una vez los siguientes pasos:
 *  2.1 Cifrar el bloqueT mediante AES256 y lo guarda en el bloqueC.
 *  2.2 Obtiene la representación decimal de los últimos N bits del bloqueC
 *      y los guarda en token.
 *  2.3 Comprueba que el valor en token sea menor a 10^L: en otras palabras,
 *      verifica que tenga L dígitos. En caso de que no lo tenga, usa el método
 *      de la caminata cíclica al regresar al paso 2.1, pero cifrando el bloqueC
 *      actual.
 * 3. Verifica si existe el token en la base de datos. Si existe, regresa al
 *    paso 1, con la misma llave y la misma entrada entradaX, pero aumenta
 *    en uno la entrada entradaU.
 */
void AHR::tokenizarHibridamente(unsigned char* llave)
{
  AES cifrador = AES(AES_256);
  cifrador.ponerLlave(llave);

  unsigned long long int limiteS =
    (unsigned long long int) pow((long double)10, (long double)L);

  /* Primer paso del algoritmo. */
  crearBloqueT();

  /* Caminata cíclica para obtener un token dentro del dominio del mensaje. */
  do{
    /* Segundo paso del algoritmo: cifrar el bloqueT y ponerlo en bloqueC. */
    cifrador.cifrarBloque(bloqueT);
    bloqueC = cifrador.obtenerBloqueTCifrado();

    /* Tercer y cuarto paso del algoritmo: verificar que esté dentro del dominio
     * del mensaje y pasarlo a su forma decimal.
     */
    obtenerNumeroC();
    memcpy(bloqueT, bloqueC, M);
  }while(token >= limiteS);

  /* Quinto paso del algoritmo: revisar si existe el token generado.*/
  if(existeToken())
  {
    /* Aumentar en uno la entradaU y volver a correr el algoritmo.*/
    entradaU += 1;
    tokenizarHibridamente(llave);
  }
}

/**
 * Se encarga de regresar el valor almacenado en la variable token.
 */
unsigned long long int AHR::obtenerToken()
{
  return token;
}
