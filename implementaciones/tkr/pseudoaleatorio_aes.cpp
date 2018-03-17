/**
 * \file
 * \brief Función pseudoaleatoria usando AES.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/pseudoaleatorio_aes.hh"
#include "../../utilidades/cabeceras/utilidades_matematicas.hh"
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>

using namespace Implementaciones;
using namespace CryptoPP;
using namespace std;

/**
 * Inicializa los objetos comunes a todas las iteraciones del cifrador:
 * una objeto de aes, un objeto de ecb y una referencia al bloque de
 * la llave.
 *
 * Importante: la política de memoria para esta clase es la misma que para
 * todas las clases de las redes Feistel; es la misma clase la encargada
 * de liberar su memoria, por lo que es un error en tiempo de ejecución
 * intentar liberar la memoria de la llave fuera de esta clase.
 */

PseudoaleatorioAES::PseudoaleatorioAES(
  unsigned char* llave                  /**< llave para cifrador por bloques. */
)
: mLlave {llave},
  mCifradoAES {mLlave, AES::DEFAULT_KEYLENGTH},
  mCifradoECB {mCifradoAES}
{
}

/**
 * Libera la memoria del arreglo de la llave.
 */

PseudoaleatorioAES::~PseudoaleatorioAES()
{
  //delete[] mLlave;
}

/**
 * Operación de función: recibe en el vector de los argumentos un
 * contador (el estado el algoritmo en RN) y la longitud de bits que el
 * resultado debe tener. La longitud real regresada es el múltiplo del
 * tamaño de bloque de AES (128 bits) más cercano hacia arriba.
 *
 * Este es el algoritmo propuesto en el artículo de TKR para instanciar f
 * con un cifrador por bloques.
 *
 * \return Arreglo de bytes con contenido del cifrado.
 */

Arreglo<unsigned char> PseudoaleatorioAES::operar(
  const std::vector<entero>& entrada    /**< Contador y longitud de resultado. */
)
{
  int numeroDeBloques = static_cast<int>(ceil(entrada[1] / 128.0));
  Arreglo<unsigned char> resultado (numeroDeBloques * 16);
  unsigned char bufferUno[16];
  memset(bufferUno, 0, 16);
  for (int i = 0; i < 8; i++)
    bufferUno[i] = static_cast<unsigned char>(entrada[0] >> (i * 8));
  unsigned char bufferDos[16];
  cifrar(bufferUno, bufferDos, 0);
  for (int i = 0; i < numeroDeBloques; i++)
  {
    cifrar(bufferDos, bufferUno, i);
    for (int j = 0; j < 16; j++)
      resultado.colocar((i * 16) + j, bufferUno[j]);
  }
  return resultado;
}

/**
 * Función interna para comunicarse con AES. recibe la memoria con la que
 * debe operar y el contador; a este se le hace un xor con el último bloque
 * de la entrada antes de cifrarse (modo de operación de contador).
 */

void PseudoaleatorioAES::cifrar(
  unsigned char *entrada,
  unsigned char *salida,
  int contador
)
{
  string cadenaBuffer;
  entrada[0] ^= static_cast<unsigned char>(contador);
  StreamTransformationFilter filtro(mCifradoECB, new StringSink(cadenaBuffer),
    StreamTransformationFilter::NO_PADDING);
  filtro.Put(entrada, 16);
  filtro.MessageEnd();
  memcpy(salida, cadenaBuffer.c_str(), 16);
}
