/**
 * \file
 * \brief Interfza ejecutable a algoritmos tokenizadores.
 *
 * Proyecto Lovelace.
 */

#include "acceso_a_datos/cabeceras/acceso_mysql.hh"
#include "bps/cabeceras/cifrador_de_ronda.hh"
#include "bps/cabeceras/cifrador_BPS.hh"
#include "ffx/cabeceras/ffx_a10.hh"
#include "tkr/cabeceras/funcion_rn.hh"
#include "tkr/cabeceras/pseudoaleatorio_aes.hh"
#include "tkr/cabeceras/tkr.hh"
#include "utilidades/cabeceras/utilidades_criptograficas.hh"
#include "../utilidades/cabeceras/arreglo_de_digitos.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace Implementaciones;
using namespace std;

/** \brief Mensaje con instrucciones. */
void imprimirAyuda();

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
  if (numeroDeArgumentos < 3)
  {
    imprimirAyuda();
    return EXIT_FAILURE;
  }

  string operacion {argumentos[1]};
  /* Generar llave. */
  if (operacion == "-k")
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
    ArregloDeDigitos pan {string{argumentos[3]}};
    string nombreArchivoLlave {argumentos[4]};
    cout << "Tokenizar " << pan << " con " << metodo << "." << endl;
    ArregloDeDigitos token {tokenizar(metodo, nombreArchivoLlave, pan)};
    cout << "Resultado: " << token << endl;
  }
  /* Detokenizar. */
  else if (operacion == "-d")
  {
    string metodo {argumentos[2]};
    ArregloDeDigitos token {string{argumentos[3]}};
    string nombreArchivoLlave {argumentos[4]};
    cout << "Detokenizar " << token << " con " << metodo << "." << endl;
    ArregloDeDigitos pan {detokenizar(metodo, nombreArchivoLlave, token)};
    cout << "Resultado: " << pan << endl;
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
      << "OPERACIÓN := -k | -e | -d | -h " << endl
      << "-k NOMBRE_DE_ARCHIVO LONGITUD" << endl
      << "  Genera una llave aleatoria de la longitud solicitada y" << endl
      << "  la guarda en el archivo dado." << endl
      << "-e MÉTODO PAN ARCHIVO_DE_LLAVE" << endl
      << "  Genera el token del PAN dado con el método y la llave" << endl
      << "  especificados."
      << "-d MÉTODO TOKEN ARCHIVO_DE_LLAVE" << endl
      << "  Detokeniza el token dado con el método y la llave" << endl
      << "  especificados." << endl
      << "MÉTODO := TKR | FFX | BPS | HAR" << endl
      << "-k" << endl
      << "  Imprime este mensaje." << endl
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
  unsigned char* llave = generarLlave(longitud);
  fstream archivo {nombreDeArchivo.c_str(),
    fstream::out | fstream::binary | fstream::trunc};
  archivo.write(reinterpret_cast<const char*>(llave), longitud);
  archivo.close();
  delete[] llave;
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
  fstream archivo {nombreDeArchivo.c_str(), fstream::in | fstream::binary};
  int marcaDeInicio = archivo.tellg();
  archivo.seekg(0, ios::end);
  int marcaDeFin =  archivo.tellg();
  int longitud = marcaDeFin - marcaDeInicio;
  archivo.seekg(0, ios::beg);
  unsigned char* llave = new unsigned char[longitud];
  archivo.read(reinterpret_cast<char*>(llave), longitud);
  archivo.close();
  return llave;
}

/**
 *
 */

ArregloDeDigitos tokenizar(
  string metodo,
  string nombreArchivoLlave,
  const ArregloDeDigitos& pan
)
{
  unsigned char *llave = leerLlave(nombreArchivoLlave);
  ArregloDeDigitos resultado;
  if (metodo == "TKR")
  {
    PseudoaleatorioAES* aes = new PseudoaleatorioAES {llave};
    FuncionRN* funcion = new FuncionRN {aes};
    CDV* accesoADatos = new AccesoMySQL {};
    TKR tkr {funcion, accesoADatos};
    ArregloDeDigitos token {tkr.tokenizar(pan)};
    resultado = token;
  }
  else if (metodo == "FFX")
  {
    FFXA10<int> ffx {llave, nullptr, 0, 16};
    Arreglo<int> textoCifrado = ffx.operar({pan});
    resultado = ArregloDeDigitos{textoCifrado};
  }
  else if (metodo == "BPS")
  {
    vector<char> alfabetoNumerico;
    for (int i = 0; i < 10; i++)
      alfabetoNumerico.push_back('0' + i);
    CifradorBPS BPS(alfabetoNumerico, 8, CifradorDeRonda::BANDERA_AES);
    ArregloDeDigitos token {BPS.cifrar(pan.obtenerCadena(), llave, 0)};
    resultado = token;
  }
  delete[] llave;
  return resultado;
}

/**
 *
 */

ArregloDeDigitos detokenizar(
  string metodo,
  string nombreArchivoLlave,
  const ArregloDeDigitos& token
)
{
  unsigned char *llave = leerLlave(nombreArchivoLlave);
  ArregloDeDigitos resultado;
  if (metodo == "TKR")
  {
    CDV* accesoADatos = new AccesoMySQL {};
    PseudoaleatorioAES* aes = new PseudoaleatorioAES {llave};
    FuncionRN* funcion = new FuncionRN {aes};
    TKR tkr {funcion, accesoADatos};
    ArregloDeDigitos pan {tkr.detokenizar(token)};
    resultado = pan;
  }
  else if (metodo == "FFX")
  {
    FFXA10<int> ffx {llave, nullptr, 0, 16};
    Arreglo<int> textoDescifrado = ffx.deoperar({token});
    resultado = ArregloDeDigitos{textoDescifrado};
  }
  else if (metodo == "BPS")
  {
    vector<char> alfabetoNumerico;
    for (int i = 0; i < 10; i++)
      alfabetoNumerico.push_back('0' + i);
    CifradorBPS BPS(alfabetoNumerico, 8, CifradorDeRonda::BANDERA_AES);
    ArregloDeDigitos pan {BPS.descifrar(token.obtenerCadena(), llave, 0)};
    resultado = pan;
  }
  delete[] llave;
  return resultado;
}
