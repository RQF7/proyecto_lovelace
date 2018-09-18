/**
 * \file
 * \brief Interfaz ejecutable a algoritmos tokenizadores.
 *
 * Proyecto Lovelace.
 */

#include "acceso_a_datos/cabeceras/acceso_mysql.hh"
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
#include "ahr/cabeceras/ahr.hh"
#include "utilidades/cabeceras/algoritmo_tokenizador.hh"
#include "utilidades/cabeceras/utilidades_criptograficas.hh"
#include "utilidades/cabeceras/utilidades_tarjetas.hh"
#include "../utilidades/cabeceras/arreglo_de_digitos.hh"
#include "../utilidades/cabeceras/codificador.hh"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace Implementaciones;
using namespace std;

/** \brief Mensaje con instrucciones. */
void imprimirAyuda();

/** \brief Genera un PAN válido aleatorio. */
void generarPAN();

/** \brief Genración de llave pseudoaleatoria. */
void generarLlave(string nombreDeArchivo, int longitud);

/** \brief Lee la llave del archivo dado. */
unsigned char* leerLlave(string nombreDeArchivo);

/** \brief Proceso de tokenización. */
ArregloDeDigitos tokenizar(string metodo, string nombreArchivoLlave,
  const ArregloDeDigitos& pan);

/** \brief Proceso de detokenización. */
ArregloDeDigitos detokenizar(string metodo, string nombreArchivoLlave,
  const ArregloDeDigitos& pan);

/**
 * Función principal de interfaz con algoritmos tokenizadores. Recibe de
 * los argumentos de la línea de comandos la operación y actúa en consecuencia.
 *
 * \return Estado de ejecución.
 */

int main(int numeroDeArgumentos, char** argumentos)
{
  /* Discriminación por número de argumentos. */
  if (numeroDeArgumentos < 2)
  {
    imprimirAyuda();
    return EXIT_FAILURE;
  }

  string operacion {argumentos[1]};
  /* Generar PAN aleatorio. */
  if (operacion == "-r")
  {
    generarPAN();
  }
  /* Calcular dígito de verificación. */
  else if (operacion == "-l")
  {
    ArregloDeDigitos pan {string{argumentos[2]}};
    cout << algoritmoDeLuhn(pan) << endl;
  }
  /* Genera llave. */
  else if (operacion == "-k")
  {
    string nombreDeArchivo {argumentos[2]};
    int longitud {stoi(string{argumentos[3]})};
    cout << "Generar llave de " << longitud << " bits." << endl;
    generarLlave(nombreDeArchivo, longitud);
    cout << "Llave guardada en " << nombreDeArchivo << "." << endl;
  }
  /* Tokenizar. */
  else if (operacion == "-e")
  {
    string metodo {argumentos[2]};
    ArregloDeDigitos pan (string{argumentos[3]});
    string nombreArchivoLlave {(numeroDeArgumentos > 4) ? argumentos[4] : ""};
    ArregloDeDigitos token (tokenizar(metodo, nombreArchivoLlave, pan));
    cout << token << endl;
  }
  /* Detokenizar. */
  else if (operacion == "-d")
  {
    string metodo {argumentos[2]};
    ArregloDeDigitos token (string{argumentos[3]});
    string nombreArchivoLlave {(numeroDeArgumentos > 4) ? argumentos[4] : ""};
    ArregloDeDigitos pan (detokenizar(metodo, nombreArchivoLlave, token));
    cout << pan << endl;
  }
  /* Ayuda. */
  else if (operacion == "-h")
  {
    imprimirAyuda();
  }
  else
  {
   imprimirAyuda();
   return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/**
 * Imprime en la salida estándar un mensaje dirigido al usuario del programa
 * indicando cómo es la operación correcta.
 */

void imprimirAyuda()
{
  cout << "Uso de programa: " << endl
      << "./binarios/lovelace OPERACIÓN ARGUMENTOS" << endl
      << "OPERACIÓN := -r | -l | -k | -e | -d | -h " << endl
      << "-r" << endl
      << "  Genera PAN aleatorio válido." << endl
      << "-l PAN" << endl
      << "  Calcula el dígito de verificación del número dado."
      << "-k NOMBRE_DE_ARCHIVO LONGITUD" << endl
      << "  Genera una llave aleatoria de la longitud solicitada y" << endl
      << "  la guarda en el archivo dado." << endl
      << "-e MÉTODO PAN ARCHIVO_DE_LLAVE" << endl
      << "  Genera el token del PAN dado con el método y la llave" << endl
      << "  especificados."
      << "-d MÉTODO TOKEN ARCHIVO_DE_LLAVE" << endl
      << "  Detokeniza el token dado con el método y la llave" << endl
      << "  especificados." << endl
      << "MÉTODO := TKR | FFX | BPS | HAR | DRBG" << endl
      << "-h" << endl
      << "  Imprime este mensaje." << endl
      << endl;
}

/**
 * Genera un PAN aleatorio y lo imprime en la salida estándar.
 */

void generarPAN()
{
  srand(time(NULL));
  PseudoaleatorioTrivial generador {};
  cout << generador.operar({static_cast<unsigned int>(rand() % 7 + 12)})
       << endl;
}

/**
 * Genera una llave aleatoria de la longitud solicitada y la guarda en el
 * archivo de la ruta dada.
 */

void generarLlave(
  string nombreDeArchivo,     /**< Ruta a archivo destino. */
  int longitud                /**< Longitud en bytes de llave. */
)
{
  Arreglo<unsigned char> llave = generarLlave(longitud); 
  Utilidades::Codificador codificador {};
  string llaveCodificada = codificador.operar({llave});
  fstream archivo {nombreDeArchivo.c_str(),
    fstream::out | fstream::binary | fstream::trunc};
  archivo.write(llaveCodificada.c_str(), llaveCodificada.size());
  archivo.close();
}

/**
 * Lee la llave desde el archivo especificado.
 *
 * Importante: los clientes de esta función deben liberar la memoria reservada.
 *
 * \return Arreglo con llave leída.
 */

unsigned char* leerLlave(
  string nombreDeArchivo      /**< Ruta al archivo de la llave. */
)
{
  fstream archivo {nombreDeArchivo.c_str(), fstream::in};
  string llaveCodificada;
  archivo >> llaveCodificada;
  archivo.close();
  Utilidades::Codificador codificador {};
  Arreglo<unsigned char> llave = codificador.deoperar({llaveCodificada});
  return llave.obtenerCopiaDeArreglo();
}

/**
 * Función de tokenización. Lee la llave del archivo dado y cifra el PAN dado
 * con el método solicitado.
 *
 * \return Token del PAN dado.
 */

ArregloDeDigitos tokenizar(
  string metodo,                /**< Cadena con método a ocupar. */
  string nombreArchivoLlave,    /**< Ruta a archivo de llave. */
  const ArregloDeDigitos& pan   /**< Arreglo de dígitos con el PAN. */
)
{
  unsigned char *llave = (nombreArchivoLlave != "") ?
    leerLlave(nombreArchivoLlave) : nullptr;
  ArregloDeDigitos resultado;
  AlgoritmoTokenizador* algoritmoTokenizador {nullptr};
  unsigned int longitud = pan.obtenerNumeroDeElementos() - 7;
  if (metodo == "TKR")
  {
    CDV* accesoADatos = new AccesoMySQL {};
    PseudoaleatorioAES* aes = new PseudoaleatorioAES {llave};
    FuncionRN* funcion = new FuncionRN {aes, accesoADatos, longitud};
    algoritmoTokenizador = new TKR{funcion, accesoADatos};
  }
  else if (metodo == "FFX")
  {
    algoritmoTokenizador = new FFXA10<int>{llave, nullptr, 0, longitud};
  }
  else if (metodo == "BPS")
  {
    algoritmoTokenizador = new CifradorBPS{8,
      CifradorDeRonda::BANDERA_AES, llave};
  }
  else if (metodo == "AHR")
  {
    CDV* accesoADatos = new AccesoMySQL {};
    algoritmoTokenizador = new AHR{accesoADatos, llave};
  }
  else if (metodo == "DRBG")
  {
    CDV* accesoADatos = new AccesoMySQL {};
    //DRBG *drbg = new HashDRBG{Arreglo<unsigned char>{1, 2, 3},
    //  DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256};
    DRBGCryptopp *drbg = new DRBGCryptopp{};
    FuncionDRBG* funcion = new FuncionDRBG{drbg};
    algoritmoTokenizador = new TKR{funcion, accesoADatos};
  }
  resultado = algoritmoTokenizador->operar({pan});
  delete algoritmoTokenizador;
  delete[] llave;
  return resultado;
}

/**
 * Operación de detokenización. Lee la llave del archivo dado y detokeniza el
 * token dado con el método solicitado.
 *
 * \return Arreglo de dígitos con el PAN.
 */

ArregloDeDigitos detokenizar(
  string metodo,
  string nombreArchivoLlave,
  const ArregloDeDigitos& token
)
{
  unsigned char *llave = (nombreArchivoLlave != "") ?
    leerLlave(nombreArchivoLlave) : nullptr;
  ArregloDeDigitos resultado;
  AlgoritmoTokenizador* algoritmoTokenizador {nullptr};
  unsigned int longitud = token.obtenerNumeroDeElementos() - 7;
  if (metodo == "TKR")
  {
    CDV* accesoADatos = new AccesoMySQL {};
    algoritmoTokenizador = new TKR{nullptr, accesoADatos};
  }
  else if (metodo == "FFX")
  {
    algoritmoTokenizador = new FFXA10<int>{llave, nullptr, 0, longitud};
  }
  else if (metodo == "BPS")
  {
    algoritmoTokenizador = new CifradorBPS{8,
      CifradorDeRonda::BANDERA_AES, llave};
  }
  else if (metodo == "AHR")
  {
    CDV* accesoADatos = new AccesoMySQL {};
    algoritmoTokenizador = new AHR{accesoADatos};
  }
  else if (metodo == "DRBG")
  {
    CDV* accesoADatos = new AccesoMySQL {};
    algoritmoTokenizador = new TKR{nullptr, accesoADatos};
  }
  resultado = algoritmoTokenizador->deoperar({token});
  delete algoritmoTokenizador;
  delete[] llave;
  return resultado;
}
