/**
 * \file
 * \brief Definición de funciones de prueba del contenedor tipo arreglo.
 * Proyecto Lovelace.
 */

#include "cabeceras/red_feistel_prueba.hh"
#include "cabeceras/arreglo.hh"
#include "cabeceras/red_feistel.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

RedFeistelPrueba::RedFeistelPrueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "operaciones de cifrado y descifrado",
    RedFeistelPrueba::probarCifradoDescifrado
  });
}

/**
 * Prueba la operación de las redes Feistel con las funciones triviales.
 * De momento solamente se hacen con compuestos enteros; aunque debería ser lo
 * mismo para cualquier tipo de dato.
 *
 * \return Estado de la prueba.
 *
 * \todo ¿Qué pasa si cifrar tuviera una sobrecarga que recibe otra cosa con
 * una lista de inicialización? ¿Error de compilación, o cómo se resuelve la
 * ambigüedad?
 *
 * \todo Hacer prueba con algo que no sea trivial.
 */

bool RedFeistelPrueba::probarCifradoDescifrado()
{
  /* Prueba de cifrado trivial: en pares debe ser lo mismo. */
  RedFeistel<int> red {4, 4};
  Arreglo<int> textoCifrado = red.cifrar({1, 2, 3, 4});
  cout << "Prueba de cifrado trivial (par): " << endl
       << textoCifrado << endl;
  if (textoCifrado[0] != 1 || textoCifrado[3] != 4)
    return false;

  /* Mientras que en impares debe estar invertido. */
  RedFeistel<int> redDos {5, 4};
  Arreglo<int> textoCifradoDos = redDos.cifrar({1, 2, 3, 4});
  cout << "Prueba de cifrado trivial (impar): " << endl
       << textoCifradoDos << endl;
  if (textoCifradoDos[1] != 4 || textoCifradoDos[2] != 1)
    return false;

  /* Operación de descifrado par */
  Arreglo<int> textoDescifrado = red.descifrar(textoCifrado);
  cout << "Prueba de descifrado trivial (par): " << endl
       << textoDescifrado << endl;
  if (textoDescifrado[0] != 1 || textoDescifrado[3] != 4)
    return false;

  /* Operación de descifrado impar */
  Arreglo<int> textoDescifradoDos = redDos.descifrar(textoCifradoDos);
  cout << "Prueba de descifrado trivial (par): " << endl
       << textoDescifradoDos << endl;
   if (textoDescifradoDos[1] != 2 || textoDescifradoDos[2] != 3)
     return false;

  return true;
}
