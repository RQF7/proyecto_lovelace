/**
 * \file
 * \brief Declaración de función RN de TKR
 *
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_RN__
#define __FUNCION_RN__

#include "pseudoaleatorio_aes.hh"
#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Función para generar tokens aleatorios ocupada por TKR2a.
   *
   * Esta sí es criptográficamente segura. Es la que se describe en el propio
   * artículo de TKR.
   */

  class FuncionRN : public Utilidades::Funcion<Arreglo<int>, int>
  {
    public:
      /** \brief Alias para función interna. */
      using FuncionInterna = Funcion<Arreglo<unsigned char>, entero>;

      /** \brief Inicialización de parámetros. */
      FuncionRN(FuncionInterna* funcionInterna,
        int longitudDeCadena = 16, int cardinalidadDeAlfabeto = 10);

      /** \brief Liberación de memoria. */
      ~FuncionRN();

      /** \brief Generación de token pseudoaleatorio. */
      Arreglo<int> operar(const std::vector<int>& entrada) override;

      /** \brief Redistribuye los bytes del arreglo dado. */
      Arreglo<unsigned char> redistribuir(
        const Arreglo<unsigned char> &original);

    private:
      /** \brief Apuntador a primitiva subyacente. */
      FuncionInterna* mFuncionInterna;

      /** \brief Longitud de cadenas resultado */
      int mLongitudDeCadena;

      /** \brief Cardinalidad del alfabeto usado. */
      int mCardinalidadDeAlfabeto;

      /** \brief Longitud en bits de cada elemento de cadena. */
      int mLongitudDeBits;

      /** \brief Contador usado como estado para función interna. */
      static entero mContador;
  };
}

#endif
