/*
 * Super clase de todas las pruebas, declaración.
 * Proyecto Lovelace.
 */

#include <vector>
#include "funcion_de_prueba.hh"

class Prueba
{
  public:
    bool probar();

  protected:
    std::vector<FuncionDePrueba> mListaDePruebas;
};
