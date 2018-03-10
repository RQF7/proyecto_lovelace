/**
 * \file
 * \brief Implementación de pruebas de utilidades matemáticas.
 * Proyecto Lovelace.
 */

#include "cabeceras/utilidades_matematicas.hh"
#include "cabeceras/utilidades_matematicas_prueba.hh"
#include <iostream>

using namespace Utilidades;
using namespace UtilidadesPruebas;
using namespace std;

UtilidadesMatematicasPrueba::UtilidadesMatematicasPrueba()
{
  mListaDePruebas.push_back(FuncionDePrueba{
    "prueba la operación de potencia",
    UtilidadesMatematicasPrueba::probarPotencia
  });
    mListaDePruebas.push_back(FuncionDePrueba{
      "prueba la operación de módulo",
      UtilidadesMatematicasPrueba::probarModulo
    });
}

/**
 * Prueba la operación de la función potencia para enteros normales y para
 * enteros largos. En el caso de los enteros normales, son con signo: desde
 * -(2 ^ 31) hasta (2 ^ 31) - 1. En el caso de los largos, son sin signo
 * (el alias es para unsigned long long int): desde 0 hata (2 ^ 64) - 1.
 *
 * \note En la comparación de resultados `ull` declara un literal de
 * unsigned long long int.
 *
 * \return Estado de la prueba.
 */

bool UtilidadesMatematicasPrueba::probarPotencia()
{
  /* Pruebas con enteros normales. */
  int pruebaUno = potencia<int>(2, 16);
  int pruebaDos = potencia<int>(2, 31) - 1;
  int pruebaTres = potencia<int>(2, 31);
  cout << "Pruebas con tipo int:"  << endl
       << "2 ^ 16 = " << pruebaUno << endl
       << "2 ^ 31 - 1 = " << pruebaDos << endl
       << "2 ^ 31 = " << pruebaTres << endl;
  if (pruebaUno != 65536 || pruebaDos != 2147483647 || pruebaTres != -2147483648)
    return false;

  /* Pruebas con enteros grandes (8 bytes). */
  entero pruebaCuatro = potencia<entero>(2, 16);
  entero pruebaCinco = potencia<entero>(2, 64) - 1;
  entero pruebaSeis = potencia<entero>(2, 64);
  cout << "Pruebas con tipo unsigned long long int:"  << endl
       << "2 ^ 16 = " << pruebaCuatro << endl
       << "2 ^ 64 - 1 = " << pruebaCinco << endl
       << "2 ^ 64 = " << pruebaSeis << endl;
  if (pruebaCuatro != 65536 || pruebaCinco != 18446744073709551615ull ||
    pruebaSeis != 0)
    return false;
  return true;
}

/**
 * Prueba de la operación módulo para casos normales y para casos con números
 * negativos (razón principal por la que se escribió esta fucnión).
 *
 * \return Estado de la prueba.
 */

bool UtilidadesMatematicasPrueba::probarModulo()
{
  /* Prueba de módulos normales. */
  int pruebaUno = modulo(67, 7);
  int pruebaDos = modulo(12 * 5, 12);
  cout << "Prueba de módulos normales:" << endl
       << "67 mod 7 = " << pruebaUno << endl
       << "60 mod 12 = " << pruebaDos << endl;
  if (pruebaUno != 67 % 7 || pruebaDos != 0)
    return false;

  /* Prueba de módulos negativos. */
  int pruebaTres = modulo(-7, 10);
  int pruebaCuatro = modulo(-158, 6);
  cout << "Prueba de módulos negativos:" << endl
       << "-7 mod 10 = " << pruebaTres << endl
       << "-158 mod 6 = " << pruebaCuatro << endl;
  if (pruebaTres != 3 || pruebaCuatro != 4)
    return false;
  return true;
}
