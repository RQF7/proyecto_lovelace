/**
 * \file
 * \brief Cliente de demonio tokenizador.
 *
 * Equivalente de lovelace.cpp pero que hace uso de los objetos ya inicializados
 * del demonio.
 *
 * TODO: Definir cómo será la gestión de llaves.
 *
 * Proyecto Lovelace.
 */

#include <fcntl.h>     /* open */
#include <string.h>    /* memset */
#include <sys/types.h> /* mkfifo */
#include <sys/stat.h>  /* mkfifo, open */
#include <unistd.h>    /* write, close, unlink */

#include "../utilidades/cabeceras/arreglo_de_digitos.hh"

#include <iostream>
#include <string>

using namespace std;

/** \brief Mensaje con instrucciones. */
void imprimirAyuda();

/** \brief Define el tamaño del buffer de comunicación
 *  entre cliente y demonio. */
#define TAMANIO_DE_BUFFER 1024

 /**
  * \brief
  *
  * \return Estado de ejecución.
  */

int main (int numeroDeArgumentos, char **argumentos)
{
  /* Discriminación por número de argumentos. */
  if (numeroDeArgumentos < 2)
  {
    imprimirAyuda();
    return EXIT_FAILURE;
  }

  /* Conexión con demonio. */
  string nombreDeTuberia {"/tmp/lovelace"};
  int descriptorDeArchivo = open(nombreDeTuberia.c_str(), O_WRONLY);
  char buffer[TAMANIO_DE_BUFFER];
  if (descriptorDeArchivo < 0)
  {
    cerr << "Error al abrir descriptor de la tubería." << endl
      << "El demonio debe estar corriendo." << endl;
    exit(EXIT_FAILURE);
  }

  string operacion {argumentos[1]};
  string metodo {argumentos[2]};
  ArregloDeDigitos elemento {string{argumentos[3]}};
  buffer[0] = operacion == "-e" ? 1 : 2;
  buffer[1] = metodo == "FFX" ? 1 :
              metodo == "BPS" ? 2 :
              metodo == "TKR" ? 3 :
              metodo == "AHR" ? 4 : 5;
  buffer[2] = elemento.obtenerNumeroDeElementos();
  for (unsigned int i = 0; i < elemento.obtenerNumeroDeElementos(); i++)
    buffer[i + 3] = elemento[i];
  write(descriptorDeArchivo, buffer, elemento.obtenerNumeroDeElementos() + 4);

  /* Cierre de conexión. */
  close(descriptorDeArchivo);
  return EXIT_SUCCESS;
}

/**
 * Imprime en la salida estándar un mensaje dirigido al usuario del programa
 * indicando cómo es la operación correcta.
 */

void imprimirAyuda()
{
  cout << "Uso de programa: " << endl
      << "./binarios/cliente_tokenizacion OPERACIÓN ARGUMENTOS" << endl
      << "OPERACIÓN := -e | -d " << endl
      << "-e MÉTODO PAN" << endl
      << "  Genera el token del PAN dado con el método" << endl
      << "  especificado." << endl
      << "-d MÉTODO TOKEN" << endl
      << "  Detokeniza el token dado con el método" << endl
      << "  especificado." << endl
      << "MÉTODO := TKR | FFX | BPS | HAR | DRBG" << endl
      << "-h" << endl
      << "  Imprime este mensaje." << endl
      << endl;
}
