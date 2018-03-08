/**
 * \file
 * \brief Definición de función de combinación por bloque.
 */

#ifndef __COMBINACION_POR_BLOQUE__
#define __COMBINACION_POR_BLOQUE__

#include "arreglo.hh"
#include "funcion_con_inverso.hh"
#include "utilidades_matematicas.hh"
#include <cmath>

namespace Implementaciones
{
  /**
   * \brief Función de combinación por bloque.
   *
   * Al tratarse de una fución con inverso (abstracta) se proveen
   * implementaciones tanto para la suma como para la resta. La base en la que
   * operan estas funciones es un miembro de datos que se puede pasar al
   * contructor.
   *
   * Ambas operaciones trabajan con arreglos del tipo especificado en el
   * template.
   */

  template <typename tipo /**< Tipo de dato de los arreglos. */ >
  class CombinacionPorBloque : public FuncionConInverso<Arreglo<tipo>,
    Arreglo<tipo>>
  {
    public:

      /** \brief Construcción de una combinación por bloque. */
      CombinacionPorBloque(tipo base = 10);

      /** \brief Suma por bloque. */
      Arreglo<tipo> operar(
        const std::vector<Arreglo<tipo>> &entrada) override;

      /** \brief Resta por bloque. */
      Arreglo<tipo> deoperar(
        const std::vector<Arreglo<tipo>> &entrada) override;

    private:
      /** \brief Base en la que operan la suma y la resta. */
      tipo mBase;
  };

  /**
   * El único de dato que mantiene la clase es la base en la que operan
   * las funciones de suma y resta.
   */

  template <typename tipo>
  CombinacionPorBloque<tipo>::CombinacionPorBloque(
    tipo base               /**< Base de operaciones. */
  )
  : mBase {base}
  {
  }

  /**
   * Interpreta como número ambos argumentos, los suma y al resultado le saca
   * módulo para dejarlo en el mismo conjunto.
   * Por ejemplo:
   * 79 + 12 = 91
   * 50 + 67 = 17
   *
   * \return Arreglo con suma por bloque.
   */

  template <typename tipo>
  Arreglo<tipo> CombinacionPorBloque<tipo>::operar(
    /** Vector con datos a sumar (se esperan solamente dos). */
    const std::vector<Arreglo<tipo>> &entrada
  )
  {
    int tamanio {entrada[0].obtenerNumeroDeElementos()};
    int numeroUno {entrada[0].convertirANumero(mBase)};
    int numeroDos {entrada[1].convertirANumero(mBase)};
    return Arreglo<tipo>::convertirAArreglo(modulo((numeroUno + numeroDos),
      static_cast<int>(pow(mBase, tamanio))), mBase, tamanio);
  }

  /**
   * Interpreta como número ambos argumentos, los resta y al resultado le saca
   * módulo para dejarlo en el mismo conjunto.
   * Por ejemplo:
   * 91 - 79 = 12
   * 17 - 50 = 67
   *
   * \return Arreglo con resta por bloque.
   */

  template <typename tipo>
  Arreglo<tipo> CombinacionPorBloque<tipo>::deoperar(
    /** Vector con datos a restar (se esperan solamente dos). */
    const std::vector<Arreglo<tipo>> &entrada
  )
  {
    int tamanio {entrada[0].obtenerNumeroDeElementos()};
    int numeroUno {entrada[0].convertirANumero(mBase)};
    int numeroDos {entrada[1].convertirANumero(mBase)};
    return Arreglo<tipo>::convertirAArreglo(modulo((numeroUno - numeroDos),
      static_cast<int>(pow(mBase, tamanio))), mBase, tamanio);
  }
}

#endif
