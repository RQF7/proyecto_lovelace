/**
 * \file
 * \brief Implementación de pruebas de TKR2.
 *
 * Proyecto Lovelace.
 */
#include "../tkr/cabeceras/pseudoaleatorio_aes.hh"
#include "cabeceras/ahr.hh"
#include "cabeceras/ahr_prueba.hh"
#include "../acceso_a_datos/cabeceras/acceso_mysql.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include <cryptopp/aes.h>
#include <cryptopp/drbg.h>
#include <cryptopp/sha.h>
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace CryptoPP;
using namespace std;

/**
 * Agrega al vector de pruebas el método probarOperación
 */
AHRPrueba::AHRPrueba()
: Utilidades::Prueba{"pruebas de AHR"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operación completa con uso de base de datos",
    AHRPrueba::probarOperacion
  });
}

/**
 * Prueba la operación normal de TKR: un primer proceso de tokenización debe
 * generar un nuevo token, mientras que la segunda ves se debe acceder al
 * anterior la detokenización es solamente una búsqueda en la base de datos.
 *
 * \return Estado de la prueba.
 */

bool AHRPrueba::probarOperacion()
{
  Implementaciones::AES cifrador = Implementaciones::AES();
  if(!cifrador.revisarInstrucciones())
  {
    cout << "No se tienen instrucciones AES en el procesador." << endl;
    return false;
  }
  /* Generar llave aleatoria. */
  unsigned char *llave = new unsigned char[CryptoPP::AES::MAX_KEYLENGTH];
  Hash_DRBG<SHA256, 128/8, 440/8> generadorAleatorio{};
  generadorAleatorio.GenerateBlock(llave, CryptoPP::AES::MAX_KEYLENGTH);

  /* Instanciación de algoritmo. */
  CDV* accesoADatos = new AccesoMySQL {};
  AHR ahr {accesoADatos, llave};

  /* Prueba de tokenización y detokenización. */
  ArregloDeDigitos panUno (887766322946577840ull);
  ArregloDeDigitos tokenUno (ahr.operar({panUno}));
  ArregloDeDigitos rPanUno (ahr.deoperar({tokenUno}));

  cout << "PAN 1: " << panUno << endl
       << "\t Token 1: " << tokenUno << endl
       << "\t Token 1 descifrado: " << rPanUno << endl;

  ArregloDeDigitos panDos (1122333116565728ull);
  ArregloDeDigitos tokenDos (ahr.operar({panDos}));
  ArregloDeDigitos rPanDos (ahr.deoperar({tokenDos}));

  cout << "PAN 2: " << panDos << endl
      << "\t Token 2: " << tokenDos << endl
      << "\t Token 2 descifrado: " << rPanDos << endl;

  if (panUno != rPanUno || panDos != rPanDos)
    return false;
  return true;
}
