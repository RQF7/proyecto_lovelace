/**
 * \file
 * \brief Ejecutable de pruebas de desempeño.
 *
 * Proyecto Lovelace.
 */

#include "acceso_a_datos/cabeceras/acceso_mysql_pruebas.hh"
#include "acceso_a_datos/cabeceras/acceso_mysql.hh"
#include "bps/cabeceras/cifrador_de_ronda.hh"
#include "bps/cabeceras/cifrador_BPS.hh"
#include "drbg/cabeceras/aleatoriedad_trivial.hh"
#include "drbg/cabeceras/hash_drbg.hh"
#include "drbg/cabeceras/pseudoaleatorio_drbg.hh"
#include "ffx/cabeceras/ffx_a10.hh"
#include "tkr/cabeceras/funcion_rn.hh"
#include "tkr/cabeceras/pseudoaleatorio_aes.hh"
#include "tkr/cabeceras/pseudoaleatorio_trivial.hh"
#include "tkr/cabeceras/tkr.hh"
#include "ahr/cabeceras/ahr.hh"
#include "utilidades/cabeceras/algoritmo_tokenizador.hh"
#include "utilidades/cabeceras/utilidades_criptograficas.hh"
#include "utilidades/cabeceras/utilidades_tarjetas.hh"
#include <cryptopp/drbg.h>
#include <cryptopp/sha.h>
#include <chrono>
#include <string>
#include <tuple>

using namespace Implementaciones;
using namespace std;
using namespace std::chrono;
using namespace CryptoPP;

ArregloDeDigitos generarPAN();
tuple<AlgoritmoTokenizador*, int> parametrizarAlgoritmo(const char*);

int main(int argc, char* argv[])
{
  int numPruebas = 10000;

  if(argc < 6)
  {
    cout << "Uso: " << argv[0]
      << " ip puerto usuario clave algoritmo [num_pruebas]" << endl;
    exit(1);
  }
  if(argc == 7)
  {
    numPruebas = atoi(argv[6]);
  }

  string ip = string(argv[1]);
  int puerto = atoi(argv[2]);
  string usuario = string(argv[3]);
  string contrasenia = string(argv[4]);

  high_resolution_clock::time_point tiempoInicial, tiempoFinal;
  auto duracionCifrado = 0;
  auto duracionDescifrado = 0;

  ArregloDeDigitos token;
  ArregloDeDigitos pan;
  AlgoritmoTokenizador* algoritmoTokenizador {nullptr};

  tuple<AlgoritmoTokenizador*, int> tupla = parametrizarAlgoritmo(argv[5]);
  algoritmoTokenizador = get<0>(tupla);
  int idAlgoritmo = get<1>(tupla);

  cout << "Realizando " << numPruebas << " pruebas." << endl;
  for(int i=0; i<numPruebas; i++)
  {
    pan = generarPAN();

    /* Tomar tiempo de cifrado. */
    tiempoInicial = high_resolution_clock::now();
    token = algoritmoTokenizador->operar({pan});
    tiempoFinal = high_resolution_clock::now();
    duracionCifrado += duration_cast<microseconds>
      (tiempoFinal - tiempoInicial).count();

    /* Tomar tiempo de descifrado. */
    tiempoInicial = high_resolution_clock::now();
    pan = algoritmoTokenizador->deoperar({token});
    tiempoFinal = high_resolution_clock::now();
    duracionDescifrado += duration_cast<microseconds>
      (tiempoFinal - tiempoInicial).count();
  }

  cout << "\tTiempo total en cifrado (en microsegundos): "
       << duracionCifrado <<  endl
       << "\tTiempo total en descifrado (en microsegundos): "
       << duracionDescifrado <<  endl;

  BDP* accesoADatos = new AccesoMySQLPruebas(ip, puerto, usuario, contrasenia);
  accesoADatos->registrarTiempoCifrado(
    idAlgoritmo, duracionCifrado, numPruebas
  );
  accesoADatos->registrarTiempoDescifrado(
    idAlgoritmo, duracionDescifrado, numPruebas
  );

  delete algoritmoTokenizador;
  return 1;
}

ArregloDeDigitos generarPAN()
{
  srand(time(NULL));
  PseudoaleatorioTrivial generador {};
  return generador.operar({static_cast<unsigned int>(16)});
}

tuple<AlgoritmoTokenizador*, int> parametrizarAlgoritmo(const char* algoritmo)
{
  if (!strcmp(algoritmo, "BPS"))
  {
    cout << "Iniciando algoritmo BPS" << endl;
    Arreglo<unsigned char> llaveA = generarLlave(16);
    unsigned char* llave = llaveA.obtenerCopiaDeArreglo();
    return make_tuple(
      new CifradorBPS{8,CifradorDeRonda::BANDERA_AES, llave}, ID_BPS);
  }
  else if(!strcmp(algoritmo, "TKR"))
  {
    cout << "Iniciando algoritmo TKR" << endl;
    Arreglo<unsigned char> llaveA = generarLlave(16);
    unsigned char* llave = llaveA.obtenerCopiaDeArreglo();
    CDV* accesoADatos = new AccesoMySQL {};
    PseudoaleatorioAES* aes = new PseudoaleatorioAES {llave};
    FuncionRN* funcion = new FuncionRN {aes, accesoADatos, 9};
    return make_tuple(new TKR{funcion, accesoADatos}, ID_TKR);
  }
  else if(!strcmp(algoritmo, "FFX"))
  {
    cout << "Iniciando algoritmo FFX" << endl;
    Arreglo<unsigned char> llaveA = generarLlave(16);
    unsigned char* llave = llaveA.obtenerCopiaDeArreglo();
    return make_tuple(new FFXA10<int>{llave, nullptr, 0, 9}, ID_FFX);
  }
  else if(!strcmp(algoritmo, "AHR"))
  {
    cout << "Iniciando algoritmo AHR" << endl;
    Arreglo<unsigned char> llaveA = generarLlave(32);
    unsigned char* llave = llaveA.obtenerCopiaDeArreglo();
    CDV* accesoADatos = new AccesoMySQL {};
    return make_tuple(new AHR{accesoADatos, llave}, ID_AHR);
  }
  else if(!strcmp(algoritmo, "DRBG"))
  {
    cout << "Iniciando algoritmo DRBG" << endl;
    CDV* accesoADatos = new AccesoMySQL {};
    DRBG *drbg = new HashDRBG{Arreglo<unsigned char>{1, 2, 3},
      DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256};
    PseudoaleatorioDRBG *puenteDRBG{new PseudoaleatorioDRBG{drbg}};
    FuncionRN* funcion = new FuncionRN {puenteDRBG, accesoADatos, 9};
    return make_tuple(new TKR{funcion, accesoADatos}, ID_DRBG);
  }
  AlgoritmoTokenizador* algoritmoNulo {nullptr};
  return make_tuple(algoritmoNulo, 0);
}
