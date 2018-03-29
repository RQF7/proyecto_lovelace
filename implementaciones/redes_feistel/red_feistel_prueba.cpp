/**
 * \file
 * \brief Definición de funciones de prueba de una red Feistel..
 * Proyecto Lovelace.
 */

#include "cabeceras/red_feistel.hh"
#include "cabeceras/red_feistel_prueba.hh"
#include "../../utilidades/cabeceras/arreglo.hh"
#include <iostream>

using namespace Implementaciones;
using namespace ImplementacionesPruebas;
using namespace std;

RedFeistelPrueba::RedFeistelPrueba()
: Utilidades::Prueba{"pruebas de redes Feistel balanceadas"}
{
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "operaciones de cifrado y descifrado",
    RedFeistelPrueba::probarCifradoDescifrado
  });
  mListaDePruebas.push_back(Utilidades::FuncionDePrueba{
    "construcción de una metared Feistel",
    RedFeistelPrueba::metaRedFeistel
  });
}

/**
 * Prueba la operación de las redes Feistel con las funciones triviales.
 * De momento solamente se hacen con compuestos enteros; aunque debería ser lo
 * mismo para cualquier tipo de dato.
 *
 * \return Estado de la prueba.
 */

bool RedFeistelPrueba::probarCifradoDescifrado()
{
  /* Prueba de cifrado trivial: en pares debe ser lo mismo. */
  RedFeistel<int> red {4, 4};
  Arreglo<int> textoCifrado = red.operar({{1, 2, 3, 4}});
  cout << "Prueba de cifrado trivial (par): " << endl
       << textoCifrado << endl;
  if (textoCifrado[0] != 1 || textoCifrado[3] != 4)
    return false;

  /* Mientras que en impares debe estar invertido. */
  RedFeistel<int> redDos {5, 4};
  Arreglo<int> textoCifradoDos = redDos.operar({{1, 2, 3, 4}});
  cout << "Prueba de cifrado trivial (impar): " << endl
       << textoCifradoDos << endl;
  if (textoCifradoDos[1] != 4 || textoCifradoDos[2] != 1)
    return false;

  /* Operación de descifrado par */
  Arreglo<int> textoDescifrado = red.deoperar({textoCifrado});
  cout << "Prueba de descifrado trivial (par): " << endl
       << textoDescifrado << endl;
  if (textoDescifrado[0] != 1 || textoDescifrado[3] != 4)
    return false;

  /* Operación de descifrado impar */
  Arreglo<int> textoDescifradoDos = redDos.deoperar({textoCifradoDos});
  cout << "Prueba de descifrado trivial (par): " << endl
       << textoDescifradoDos << endl;
   if (textoDescifradoDos[1] != 2 || textoDescifradoDos[2] != 3)
     return false;

  return true;
}

/**
 * \brief Construcción de una meta red Feistel.
 *
 * Al ser la propia red una implementación de la interfaz *Funcion*, también
 * sirve para instanciar a la función de ronda: en el caso del ejemplo, la
 * red interna usa una implementación trivial con 4 rondas, mientras
 * que la red externa usa a la interna como función de ronda (la operación de
 * combinación se queda con el valor por defecto) con 4 rondas; de esta forma
 * una operación de cifrado o descifrado realiza 16 rondas.
 *
 * \return Estado de la prueba.
 */

bool RedFeistelPrueba::metaRedFeistel()
{
  RedFeistel<int>* redInterna = new RedFeistel<int>{4, 4};
  RedFeistel<int> metaRed {4, 4, redInterna};
  Arreglo<int> textoCifrado = metaRed.operar({{1, 2, 3, 4}});
  Arreglo<int> textoDescifrado = metaRed.deoperar({textoCifrado});
  cout << "Prueba de meta red, texto cifrado: " << endl
       << textoCifrado << endl
       << "Prueba de meta red, texto descifrado: " << endl
       << textoDescifrado << endl;
  if (textoDescifrado != Arreglo<int>{1, 2, 3, 4})
    return false;

  return true;
}
