/**
 * \file
 * \brief Implementación de pruebas de AHR.
 *
 * Proyecto Lovelace.
 */
#include "../tkr/cabeceras/pseudoaleatorio_aes.hh"
#include "cabeceras/ahr.hh"
#include "cabeceras/ahr_prueba.hh"
#include "../../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../acceso_a_datos/cabeceras/acceso_mysql.hh"
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
    "operación completa de tokenización y detokenización",
    AHRPrueba::probarOperacion
  });
}

/**
 * Prueba la operación normal de TKR: un primer proceso de tokenización debe
 * generar un nuevo token, mientras que la segunda vez se debe acceder al
 * anterior la detokenización es solamente una búsqueda en la base de datos.
 *
 * \return Estado de la prueba.
 */

bool AHRPrueba::probarOperacion()
{
  Implementaciones::AES cifrador = Implementaciones::AES();

  unsigned char llave[33] = { 0xc4,0x7b,0x02,0x94,0xdb,0xbb,0xee,0x0f,
                      0xec,0x47,0x57,0xf2,0x2f,0xfe,0xee,0x35,0x87,0xca,0x47,
                      0x30,0xc3,0xd3,0x3b,0x69,0x1d,0xf3,0x8b,0xab,0x07,0x6b,
                      0xc5,0x58, 0x00};

  /* Instanciación de algoritmo. */
  CDV* accesoADatos = new AccesoMySQL {};
  AHR ahrTokenizador {accesoADatos, llave};
  AHR ahrDetokenizador {accesoADatos};

  /* Prueba de tokenización y detokenización. */
  ArregloDeDigitos panUno ("432564228828");
  ArregloDeDigitos tokenUno (ahrTokenizador.operar({panUno}));
  ArregloDeDigitos rPanUno (ahrDetokenizador.deoperar({tokenUno}));

  cout << "PAN 1: " << panUno << endl
       << "\t Token 1: " << tokenUno << endl
       << "\t Token 1 descifrado: " << rPanUno << endl;

  ArregloDeDigitos panDos (1122333116565728ull);
  ArregloDeDigitos tokenDos (ahrTokenizador.operar({panDos}));
  ArregloDeDigitos rPanDos (ahrDetokenizador.deoperar({tokenDos}));

  cout << "PAN 2: " << panDos << endl
      << "\t Token 2: " << tokenDos << endl
      << "\t Token 2 descifrado: " << rPanDos << endl;

  if (panUno != rPanUno || panDos != rPanDos)
    return false;

  if(panUno.obtenerNumeroDeElementos() != tokenUno.obtenerNumeroDeElementos()
      || panDos.obtenerNumeroDeElementos() != tokenDos.obtenerNumeroDeElementos())
    return false;
  return true;
}
