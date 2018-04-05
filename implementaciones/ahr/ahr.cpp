#include "cabeceras/ahr.hh"
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
 * Constructor por defecto. Se encarga de inicializar los bloques mBloqueT y
 * mBloqueC. Recibe como parámetros la referencia a la base de datos que
 * se va a utilizar y la llave con la que se inicializará el cifrador.
 */
AHR::AHR(CDV* baseDeDatos, unsigned char* llave)
: mAccesoADatos{baseDeDatos}
{
  mBloqueT = new unsigned char[M];
  mBloqueC = new unsigned char[M];

  mCifrador = AES(AES_256);
  mCifrador.ponerLlave(llave);
}

/**
 * Se encarga de crear un objeto a partir de
 * otro ya existente. Ambos objetos quedan utilizables.
 */
AHR::AHR(AHR const& otro)
{
  mBloqueT = new unsigned char[M];
  memcpy(mBloqueT, otro.mBloqueT, M);

  mBloqueC = new unsigned char[M];
  memcpy(mBloqueC, otro.mBloqueC, M);

  mEntradaX = otro.mEntradaX;
  mEntradaU = otro.mEntradaU;
  mToken    = otro.mToken;

  mLongitudBytesEntradaX = otro.mLongitudBytesEntradaX;
  mNumeroDigitosEntradaX = otro.mNumeroDigitosEntradaX;

  mTokenCompleto = string(otro.mTokenCompleto);
  mPANOriginal = string(otro.mPANOriginal);

  mAccesoADatos = otro.mAccesoADatos;
  mCifrador = AES(otro.mCifrador);
}

/**
 * Caso especial del operador de asignación donde
 * la fuente y el destino son del mismo tipo. A diferencia del constructor
 * por copia, limpia los miembros antes de asignarlos.
 */
AHR& AHR::operator=(AHR const& otro)
{
  unsigned char *auxiliar1 = new unsigned char[M];
  memcpy(auxiliar1, otro.mBloqueT, M);
  delete [] mBloqueT;
  mBloqueT = auxiliar1;

  unsigned char *auxiliar2 = new unsigned char[M];
  memcpy(auxiliar2, otro.mBloqueC, M);
  delete [] mBloqueC;
  mBloqueC = auxiliar2;

  mEntradaX = otro.mEntradaX;
  mEntradaU = otro.mEntradaU;
  mToken    = otro.mToken;

  mLongitudBytesEntradaX = otro.mLongitudBytesEntradaX;
  mNumeroDigitosEntradaX = otro.mNumeroDigitosEntradaX;

  mTokenCompleto = string(otro.mTokenCompleto);
  mPANOriginal = string(otro.mPANOriginal);

  mAccesoADatos = otro.mAccesoADatos;
  mCifrador = AES(otro.mCifrador);

  return *this;
}

/**
 * Se encarga de liberar la memoria reservada por los constructores.
 */
AHR::~AHR()
{
  delete [] mBloqueT;
  delete [] mBloqueC;
}

/**
  * Este método se encarga de <<romper>> el PAN y obtener el IIN, el número
  * de cuenta y, tomándolos en cuenta, determina los valores de mNumeroDigitosEntradaX y mLongitudBytesEntradaX.
  */
void AHR::separarPAN(string PAN)
{
  mPANOriginal = string(PAN);
  mNumeroDigitosEntradaX = PAN.length() - 6 - 1;

  char *auxU = new char[6];
  char *auxX = new char[mNumeroDigitosEntradaX];

  memcpy(auxU, PAN.c_str(), 6);
  memcpy(auxX, PAN.c_str()+6, mNumeroDigitosEntradaX);

  mEntradaU = stoull(auxU);
  mEntradaX = stoull(auxX);

  mLongitudBytesEntradaX = ceil(ceil(log2(pow(10, mNumeroDigitosEntradaX))) / 8.0);

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
  mTokenCompleto =  to_string(mEntradaU) + to_string(mToken);
  ArregloDeDigitos temporal = ArregloDeDigitos(mTokenCompleto);

  mTokenCompleto += to_string(modulo(algoritmoDeLuhn(temporal, false)+1, 10));
}

/**
  * Este método se encarga de poner en los últimos mLongitudBytesEntradaX bytes del mBloqueT
  * la mEntradaX en binario. Utiliza una máscara que inicia con un uno en la
  * posición más significativa y va haciendo un corrimiento hacia la derecha,
  * comparando con la mEntradaX; si encuentra un uno en la posición
  * correspondiente, mascaraByte se encarga de poner un uno en el bit j del
  * byte i correspondiente.
  */
void AHR::obtenerBitsX()
{
  memset(mBloqueT, 0x00, M);
  unsigned long long int mascara =
    (unsigned long long int) pow((long double)2, (long double)(8*mLongitudBytesEntradaX)-1);
  unsigned char mascaraByte;

  for(int i = M-mLongitudBytesEntradaX; i < M; i++)
  {
    mascaraByte = 0x80;
    for(int j = 0; j < 8; j++)
    {
      if(mascara & mEntradaX)
      {
        mBloqueT[i] = mBloqueT[i]|mascaraByte;
      }
      mascaraByte = mascaraByte >> 1;
      mascara = mascara >> 1;
    }
  }
}

/**
  * Este método se encarga del primer paso del algoritmo: obtener el mBloqueT
  * que será utilizado como entrada para el cifrador por bloques. Primero
  * obtiene la salida de la función pública (SHA256 en este caso) de la entrada
  * adicional mEntradaU. Luego llama a la función obtenerBitsX para llenar los
  * últimos mLongitudBytesEntradaX bloques del mBloqueT y, finalmente, le concatena al inicio los
  * bytes más significativos de la salida del SHA para completar el tamaño
  * de bloque del cifrador.
  */
void AHR::crearBloqueT()
{
  string cadenaU  = to_string(mEntradaU);
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
  for(int i=0; i < M - mLongitudBytesEntradaX; i++)
  {
    mBloqueT[i] = salidaFCompleta[j];
    j++;
  }
}

/**
 * Se encarga de obtener la representación decimal de los últimos mLongitudBytesEntradaX bits del
 * mBloqueC. Guarda el resultado en el entero token.
 */
void AHR::obtenerNumeroC()
{
  unsigned char mascara;
  unsigned long long int auxiliar;
  unsigned long long int auxiliar2 = (8*mLongitudBytesEntradaX)-1;
  mToken = 0;

  for(int i = M-mLongitudBytesEntradaX; i < M; i++)
  {
    mascara = 0x80;
    for(int j = 8; j > 0; j--)
    {
      if(mascara & mBloqueC[i])
      {
        auxiliar =
          (unsigned long long int) pow((long double)2, (long double)auxiliar2);
        mToken += auxiliar;
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
  ArregloDeDigitos token_arreglo = ArregloDeDigitos(this->mTokenCompleto);
  Registro busqueda = mAccesoADatos->buscarPorToken(token_arreglo);

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
    ArregloDeDigitos pan_arreglo = ArregloDeDigitos(this->mPANOriginal);
    busqueda.colocarToken(token_arreglo);
    busqueda.colocarPAN(pan_arreglo);
    mAccesoADatos->guardar(busqueda);
    return false;
  }

}

/**
 * Método principal que se encarga de crear el token:
 * 1. Crea el mBloqueT al concatenar la salida truncada del SHA256 (alimentada
 *    con mEntradaU) y la representación binaria de mEntradaX.
 * 2. Realiza al menos una vez los siguientes pasos:
 *  2.1 Cifrar el mBloqueT mediante AES256 y lo guarda en el mBloqueC.
 *  2.2 Obtiene la representación decimal de los últimos mLongitudBytesEntradaX bits del mBloqueC
 *      y los guarda en token.
 *  2.3 Comprueba que el valor en token sea menor a 10^mNumeroDigitosEntradaX: en otras palabras,
 *      verifica que tenga mNumeroDigitosEntradaX dígitos. En caso de que no lo tenga, usa el método
 *      de la caminata cíclica al regresar al paso 2.1, pero cifrando el mBloqueC
 *      actual.
 * 3. Verifica si existe el token en la base de datos. Si existe, regresa al
 *    paso 1, con la misma llave y la misma entrada mEntradaX, pero aumenta
 *    en uno la entrada mEntradaU.
 */
void AHR::tokenizarHibridamente()
{
  unsigned long long int limiteS =
    (unsigned long long int) pow((long double)10, (long double)mNumeroDigitosEntradaX);

  /* Primer paso del algoritmo. */
  crearBloqueT();

  /* Caminata cíclica para obtener un token dentro del dominio del mensaje. */
  do{
    /* Segundo paso del algoritmo: cifrar el mBloqueT y ponerlo en mBloqueC. */
    mCifrador.cifrarBloque(mBloqueT);
    mBloqueC = mCifrador.obtenerBloqueTCifrado();

    /* Tercer y cuarto paso del algoritmo: verificar que esté dentro del dominio
     * del mensaje y pasarlo a su forma decimal.
     */
    obtenerNumeroC();
    memcpy(mBloqueT, mBloqueC, M);
  }while(mToken >= limiteS);

  /* Quinto paso del algoritmo: revisar si existe el token generado.*/
  if(existeToken())
  {
    /* Aumentar en uno la mEntradaU y volver a correr el algoritmo.*/
    mEntradaU += 1;
    tokenizarHibridamente();
  }
}

/**
 * Se encarga de regresar el valor almacenado en la variable token.
 */
unsigned long long int AHR::obtenerToken()
{
  return mToken;
}
/**
 * Este método se encarga de cambiar la llave que utiliza el cifrador AES.
 */
void AHR::cambiarLlave(unsigned char* llave)
{
  mCifrador.ponerLlave(llave);
  return;
}

/**
 * Este método realiza la tokenización, recibe como argumento el PAN
 * en un arreglo de dígitos. Primero descompone el PAN, luego aplica
 * el algoritmo propuesto en el número de cuenta y, al final, regresa
 * en un arreglo de dígitos el token creado.
 */
ArregloDeDigitos AHR::tokenizar (const ArregloDeDigitos& pan)
{
  separarPAN(pan.obtenerCadenaEfectiva());
  tokenizarHibridamente();
  return ArregloDeDigitos(mTokenCompleto);
}

/**
 * Este método se encarga de regresar el PAN que corresponde al
 * token dado en el argumento. Como este es un algoritmo irreversible,
 * busca en la base de datos el token dado y regresa el PAN asociado.
 * En caso de no existir, lanza una excepción.
 */
ArregloDeDigitos AHR::detokenizar(const ArregloDeDigitos& token)
{
  Registro informacion = mAccesoADatos->buscarPorToken(token);
  if (informacion.obtenerPAN() == Arreglo<int>{})
    throw TokenInexistente{"El token no está en la base de datos."};
  return informacion.obtenerPAN();
}
