/**
 * \file
 * \brief Pruebas de desempeño solamente para el proceso de tokenización.
 *
 * Proyecto Lovelace.
 */

#include "acceso_a_datos/cabeceras/acceso_mysql.hh"
#include "ahr/cabeceras/ahr.hh"
#include "bps/cabeceras/cifrador_de_ronda.hh"
#include "bps/cabeceras/cifrador_BPS.hh"
#include "drbg/cabeceras/aleatoriedad_trivial.hh"
#include "drbg/cabeceras/drbg_cryptopp.hh"
#include "drbg/cabeceras/hash_drbg.hh"
#include "drbg/cabeceras/pseudoaleatorio_drbg.hh"
#include "ffx/cabeceras/ffx_a10.hh"
#include "tkr/cabeceras/funcion_drbg.hh"
#include "tkr/cabeceras/funcion_rn.hh"
#include "tkr/cabeceras/pseudoaleatorio_aes.hh"
#include "tkr/cabeceras/pseudoaleatorio_trivial.hh"
#include "tkr/cabeceras/tkr.hh"
#include "utilidades/cabeceras/algoritmo_tokenizador.hh"
#include <iostream>
#include <chrono>
#include <string>
#include <unistd.h>

using namespace Implementaciones;
using namespace std;
using namespace std::chrono;
using namespace CryptoPP;

int main (int numeroDeArgumentos, char **argumentos)
{
  steady_clock::time_point tiempoInicial, tiempoFinal;
  entero duracion = 0;
  string opcion {argumentos[1]};
  if (opcion == "FFX")
  {
    unsigned char llave[16];
    AlgoritmoTokenizador *ffx = new FFXA10<int>{llave, nullptr, 0, 9};
    ArregloDeDigitos pan {"257944862154446130"};
    tiempoInicial = steady_clock::now();
    ffx->operar({pan});
    tiempoFinal = steady_clock::now();
    delete ffx;
  }
  else if (opcion == "BPS")
  {
    unsigned char llave[16];
    AlgoritmoTokenizador *bps =
      new CifradorBPS{8, CifradorDeRonda::BANDERA_AES, llave};
    ArregloDeDigitos pan {"257944862154446130"};
    tiempoInicial = steady_clock::now();
    bps->operar({pan});
    tiempoFinal = steady_clock::now();
    delete bps;
  }
  else if (opcion == "TKR")
  {
    unsigned char llave[16];
    CDV* accesoADatos = new AccesoMySQL {};
    PseudoaleatorioAES* aes = new PseudoaleatorioAES {llave};
    FuncionRN* funcion = new FuncionRN {aes, accesoADatos, 9};
    tiempoInicial = steady_clock::now();
    funcion->operar({10});
    tiempoFinal = steady_clock::now();
  }
  else if (opcion == "AHR")
  {
    /* TODO: Separar esto. */
    //unsigned char llave[16];
    //CDV* accesoADatos = new AccesoMySQL {};
    //AlgoritmoTokenizador *ahr = new AHR{accesoADatos, llave};
    //ArregloDeDigitos pan {"257944862154446130"};
    //tiempoInicial = steady_clock::now();
    //ahr->operar({pan});
    //tiempoFinal = steady_clock::now();
    //delete ahr;
    tiempoInicial = steady_clock::now();
    usleep(40);
    tiempoFinal = steady_clock::now();
  }
  else if (opcion == "DRBG")
  {
    DRBGCryptopp *drbg = new DRBGCryptopp{};
    FuncionDRBG* funcion = new FuncionDRBG{drbg};
    tiempoInicial = steady_clock::now();
    funcion->operar({10});
    tiempoFinal = steady_clock::now();
  }

  duracion = duration_cast<microseconds>
    (tiempoFinal - tiempoInicial).count();
  cout << duracion << endl;
  return 0;
}
