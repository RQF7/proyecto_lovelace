/**
 * \file
 * \brief Ejecutable de demonio tokenizador.
 *
 * TODO: Para que esto realmente valga la pena hay que sacar todas las
 * inicializaciones del ciclo del servidor y ponerlas al inicio, junto
 * a las demás inicializaciones.
 *
 * Proyecto Lovelace.
 */

#include <fcntl.h>     /* open */
#include <string.h>    /* memset */
#include <sys/types.h> /* mkfifo */
#include <sys/stat.h>  /* mkfifo, open */
#include <unistd.h>    /* read, close, unlink */

#include "acceso_a_datos/cabeceras/acceso_mysql.hh"
#include "acceso_a_datos/cabeceras/cdv.hh"
#include "drbg/cabeceras/drbg.hh"
#include "drbg/cabeceras/hash_drbg.hh"
#include "drbg/cabeceras/pseudoaleatorio_drbg.hh"
#include "tkr/cabeceras/pseudoaleatorio_aes.hh"
#include "utilidades/cabeceras/algoritmo_tokenizador.hh"
#include "../utilidades/cabeceras/arreglo.hh"
#include "../utilidades/cabeceras/arreglo_de_digitos.hh"

#include <iostream>
#include <string>

using namespace Implementaciones;
using namespace std;

/** \brief Define el tamaño del buffer de comunicación
 *  entre cliente y demonio. */
#define TAMANIO_DE_BUFFER 1024

/**
 * \brief
 *
 * \return Estado de ejecución.
 */

int main(int numeroDeArgumentos, char **argumentos)
{
  /* Inicialización de tubería. */
  string nombreDeTuberia {"/tmp/lovelace"};
  mkfifo(nombreDeTuberia.c_str(), 0666);
  int descriptorDeArchivo = open(nombreDeTuberia.c_str(), O_RDONLY);
  char buffer[TAMANIO_DE_BUFFER];

  /* Inicialización infraestructura para tokenizar. */
  AlgoritmoTokenizador* algoritmoTokenizador {nullptr};
  CDV* accesoADatos = new AccesoMySQL {};
  DRBG *drbg = new HashDRBG{Arreglo<unsigned char>{1, 2, 3},
    DRBG::NivelDeSeguridad::nivel128, HashDRBG::TipoDeFuncionHash::SHA256};
  PseudoaleatorioDRBG *puenteDrbg{new PseudoaleatorioDRBG{drbg}};

  /* Ejecución tipo servidor. */
  while (true)
    if(read(descriptorDeArchivo, buffer, TAMANIO_DE_BUFFER) > 0)
    {
      int operacion = buffer[0];
      int metodo = buffer[1];
      unsigned int numeroDeDigitos = buffer[2];
      ArregloDeDigitos elemento (numeroDeDigitos);
      for (unsigned int i = 0; i < numeroDeDigitos; i++)
        elemento[i] = buffer[i + 3];
      cout << "Operación: " << operacion << endl
        << "Método: " << metodo << endl
        << "Elemento: " << elemento << endl;
    }

  /* Liberación de recursos. */
  close(descriptorDeArchivo);
  unlink(nombreDeTuberia.c_str());
  delete algoritmoTokenizador;
  delete accesoADatos;
  // TODO: ¿el destructor está protegido?
  //delete drbg;
  delete puenteDrbg;
  return EXIT_SUCCESS;
}
