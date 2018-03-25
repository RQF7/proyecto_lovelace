/**
 * \file
 * \brief Implementación de pruebas de utilidades matemáticas.
 *
 * Proyecto Lovelace.
 */

#include "cabeceras/arreglo.hh"
#include "cabeceras/codificador.hh"
#include "cabeceras/codificador_prueba.hh"
#include <iostream>

using namespace Utilidades;
using namespace UtilidadesPruebas;
using namespace std;

CodificadorPrueba::CodificadorPrueba()
: Prueba{"pruebas del codificador"}
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "prueba de codificación en base 64",
    CodificadorPrueba::probarBase64
  });
  mListaDePruebas.push_back(FuncionDePrueba{
    "prueba de codificación en base 32",
    CodificadorPrueba::probarBase32
  });
  mListaDePruebas.push_back(FuncionDePrueba{
    "prueba de codificación en base 16",
    CodificadorPrueba::probarBase16
  });
}

/**
 * Prueba la operación con distintas longitudes a la entrada. En particular, los casos
 * triviales con uno y dos caracteres de padding.
 *
 * \return Estado de la prueba.
 */

bool CodificadorPrueba::probarBase64()
{
  Codificador codificador{};

  /* Prueba múltiplo. */
  Arreglo<unsigned char> arreglo {'r', 'Q', 'f'};
  string resultado = codificador.operar({arreglo});
  Arreglo<unsigned char> arregloResulatdo = codificador.deoperar({resultado});
  cout << "Prueba con múltiplos:" << endl << "Arreglo 1: ";
  for (int i = 0; i < arreglo.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arreglo[i]) << " ";
  cout << endl;
  cout << "Codificado 1: " << resultado << endl;
  cout << "Decodificado 1: ";
  for (int i = 0; i < arregloResulatdo.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arregloResulatdo[i]) << " ";
  cout << endl;
  if (arreglo != arregloResulatdo)
    return false;

  /* Prueba con padding = 2. */
  Arreglo<unsigned char> arregloDos {'r'};
  string resultadoDos = codificador.operar({arregloDos});
  Arreglo<unsigned char> arregloResultadoDos = codificador.deoperar({resultadoDos});
  cout << "Prueba con dos caracteres de padding:" << endl << "Arreglo 2: ";
  for (int i = 0; i < arregloDos.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arregloDos[i]) << " ";
  cout << endl;
  cout << "Codificado 2: " << resultadoDos << endl;
  cout << "Decodificado 2: ";
  for (int i = 0; i < arregloResultadoDos.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arregloResultadoDos[i]) << " ";
  cout << endl;
  if (arregloDos != arregloResultadoDos)
    return false;

  /* Prueba con padding = 1. */
  Arreglo<unsigned char> arregloTres {'r', 'q'};
  string resultadoTres = codificador.operar({arregloTres});
  Arreglo<unsigned char> arregloResultadoTres = codificador.deoperar({resultadoTres});
  cout << "Prueba con un caracter de padding:" << endl << "Arreglo 3: ";
  for (int i = 0; i < arregloTres.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arregloTres[i]) << " ";
  cout << endl;
  cout << "Codificado 3: " << resultadoTres << endl;
  cout << "Decodificado 3: ";
  for (int i = 0; i < arregloResultadoTres.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arregloResultadoTres[i]) << " ";
  cout << endl;
  if (arregloTres != arregloResultadoTres)
    return false;

  /* Prueba con padding = 2. y muchos elementos, */
  Arreglo<unsigned char> arregloCuatro {'r', 'q', '9', '0', 'h', 't', 'Z'};
  string resultadoCuatro = codificador.operar({arregloCuatro});
  Arreglo<unsigned char> arregloResultadoCuatro = codificador.deoperar({resultadoCuatro});
  cout << "Prueba con dos caracteres de padding:" << endl << "Arreglo 3: ";
  for (int i = 0; i < arregloCuatro.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arregloCuatro[i]) << " ";
  cout << endl;
  cout << "Codificado 3: " << resultadoCuatro << endl;
  cout << "Decodificado 3: ";
  for (int i = 0; i < arregloResultadoCuatro.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arregloResultadoCuatro[i]) << " ";
  cout << endl;
  if (arregloCuatro != arregloResultadoCuatro)
    return false;

  return true;
}

/**
 *
 */

bool CodificadorPrueba::probarBase32()
{
  Codificador codificador{Codificador::Base::Base32};

  /* Prueba múltiplo. */
  Arreglo<unsigned char> arreglo {'a', 'x', '9', 'r', '?'};
  string resultado = codificador.operar({arreglo});
  Arreglo<unsigned char> arregloDos = codificador.deoperar({resultado});
  cout << "Prueba con múltiplos: " << endl << "Arreglo 1: ";
  for (int i = 0; i < arreglo.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arreglo[i]) << " ";
  cout << endl;
  cout << "Codificado 1: " << resultado << endl;
  cout << "Decodificado 1: ";
  for (int i = 0; i < arregloDos.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arregloDos[i]) << " ";
  cout << endl;
  return true;
}

/**
 *
 */

bool CodificadorPrueba::probarBase16()
{
  Codificador codificador{Codificador::Base::Base16};

  /* Prueba múltiplo. */
  Arreglo<unsigned char> arreglo {'v', 'n', '5', 'c', '1', 'l'};
  string resultado = codificador.operar({arreglo});
  Arreglo<unsigned char> arregloDos = codificador.deoperar({resultado});
  cout << "Prueba con múltiplos: " << endl << "Arreglo 1: ";
  for (int i = 0; i < arreglo.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arreglo[i]) << " ";
  cout << endl;
  cout << "Codificado 1: " << resultado << endl;
  cout << "Decodificado 1: ";
  for (int i = 0; i < arregloDos.obtenerNumeroDeElementos(); i++)
    cout << static_cast<int>(arregloDos[i]) << " ";
  cout << endl;

  return true;
}
