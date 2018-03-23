/**
 * \file
 * \brief Definición de función de combinación por caracter.
 */

#ifndef __COMBINACION_POR_CARACTER__
#define __COMBINACION_POR_CARACTER__

#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include "../../../utilidades/interfaces_comunes/funcion_con_inverso.hh"

namespace Implementaciones
{
  /**
   * \brief Función de combinación por caracter.
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
  class CombinacionPorCaracter : public Utilidades::FuncionConInverso<
    Arreglo<tipo>, Arreglo<tipo>>
  {
    public:

      /** \brief Construcción de una combinación por caracter. */
      CombinacionPorCaracter(tipo base = 10);

      /** \brief Suma por caracter. */
      Arreglo<tipo> operar(
        const std::vector<Arreglo<tipo>> &entrada) override;

      /** \brief Resta por caracter. */
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
  CombinacionPorCaracter<tipo>::CombinacionPorCaracter(
    tipo base               /**< Base de operaciones. */
  )
  : mBase {base}
  {
  }

  /**
   * Realiza la suma dígito por dígito módulo la base.
   * Por ejemplo:
   * 79 + 12 = 81
   * 50 + 67 = 17
   *
   * \return Arreglo con suma por caracter.
   */

  template <typename tipo>
  Arreglo<tipo> CombinacionPorCaracter<tipo>::operar(
    /** Vector con datos a sumar (se esperan solamente dos). */
    const std::vector<Arreglo<tipo>> &entrada
  )
  {
    int tamanio {entrada[0].obtenerNumeroDeElementos()};
    Arreglo<tipo> resultado(tamanio);
    for (int i = 0; i < tamanio; i++)
      resultado[i] = modulo<tipo>((entrada[0][i] + entrada[1][i]), mBase);
    return resultado;
  }

  /**
   * Realiza la resta dígito por dígito módulo la base.
   * Por ejemplo:
   * 81 - 79 = 12
   * 17 - 50 = 67
   *
   * \return Arreglo con resta por caracter.
   */

  template <typename tipo>
  Arreglo<tipo> CombinacionPorCaracter<tipo>::deoperar(
    /** Vector con datos a restar (se esperan solamente dos). */
    const std::vector<Arreglo<tipo>> &entrada
  )
  {
    int tamanio {entrada[0].obtenerNumeroDeElementos()};
    Arreglo<tipo> resultado(tamanio);
    for (int i = 0; i < tamanio; i++)
      resultado[i] = modulo<tipo>((entrada[0][i] - entrada[1][i]), mBase);
    return resultado;
  }

}

#endif
