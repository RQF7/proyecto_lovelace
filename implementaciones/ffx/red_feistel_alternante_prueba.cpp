/**
 * \file
 * \brief Definición de funciones de prueba de una red Feistel alternante.
 * Proyecto Lovelace.
 */

#include "cabeceras/red_feistel_alternante_prueba.hh"
#include "cabeceras/arreglo.hh"
#include "cabeceras/red_feistel_alternante.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

RedFeistelAlternantePrueba::RedFeistelAlternantePrueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "operaciones de cifrado y descifrado",
    RedFeistelAlternantePrueba::probarCifradoDescifrado
  });
}

/**
 * Realiza pruebas con las redes feistel alternantes (operaciones triviales).
 *
 * \return Estado de la prueba.
 */

bool RedFeistelAlternantePrueba::probarCifradoDescifrado()
{
  /* Bloque impar, desbalanceo 0, rondas pares. */
  RedFeistelAlternante<int> red {10, 5};
  Arreglo<int> textoEnClaro {1, 2, 3, 4, 5};
  Arreglo<int> textoCifrado = red.cifrar(textoEnClaro);
  Arreglo<int> textoDescifrado = red.descifrar(textoCifrado);
  cout << "Bloque impar, desbalanceo 0, rondas pares: " << endl
       << "En claro - " << textoEnClaro << endl
       << "Cifrado - " << textoCifrado << endl
       << "Descifrado - " << textoDescifrado << endl;
  if (textoEnClaro != textoCifrado)
    return false;

  /* Bloque impar, desbalanceo 0, rondas impares. */
  RedFeistelAlternante<int> redDos {11, 5};
  Arreglo<int> textoEnClaroDos {1, 2, 3, 4, 5};
  Arreglo<int> textoCifradoDos = redDos.cifrar(textoEnClaroDos);
  Arreglo<int> textoDescifradoDos = redDos.descifrar(textoCifradoDos);
  cout << "Bloque impar, desbalanceo 0, rondas impares: " << endl
       << "En claro - " << textoEnClaroDos << endl
       << "Cifrado - " << textoCifradoDos << endl
       << "Descifrado - " << textoDescifradoDos << endl;
  if (textoEnClaroDos != textoCifradoDos)
    return false;

  /* Bloque impar, desbalanceo 2, rondas pares. */
  RedFeistelAlternante<int> redTres {10, 7, 2};
  Arreglo<int> textoEnClaroTres {1, 2, 3, 4, 5, 6, 7};
  Arreglo<int> textoCifradoTres = redTres.cifrar(textoEnClaroTres);
  Arreglo<int> textoDescifradoTres = redTres.descifrar(textoCifradoTres);
  cout << "Bloque impar, desbalanceo 2, rondas impares: " << endl
       << "En claro - " << textoEnClaroTres << endl
       << "Cifrado - " << textoCifradoTres << endl
       << "Descifrado - " << textoDescifradoTres << endl;
  if (textoEnClaroTres != textoCifradoTres)
    return false;

  /* Bloque impar, desbalanceo 2, rondas impares. */
  RedFeistelAlternante<int> redCuatro {11, 7, 2};
  Arreglo<int> textoEnClaroCuatro {1, 2, 3, 4, 5, 6, 7};
  Arreglo<int> textoCifradoCuatro = redCuatro.cifrar(textoEnClaroCuatro);
  Arreglo<int> textoDescifradoCuatro = redCuatro.descifrar(textoCifradoCuatro);
  cout << "Bloque impar, desbalanceo 2, rondas impares: " << endl
       << "En claro - " << textoEnClaroCuatro << endl
       << "Cifrado - " << textoCifradoCuatro << endl
       << "Descifrado - " << textoDescifradoCuatro << endl;
  if (textoEnClaroCuatro != textoCifradoCuatro)
    return false;

  return true;
}
