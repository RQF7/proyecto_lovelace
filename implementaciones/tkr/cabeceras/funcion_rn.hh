/**
 * \file
 * \brief Declaración de función RN de TKR
 *
 * Proyecto Lovelace.
 */

#ifndef __FUNCION_RN__
#define __FUNCION_RN__

#include "pseudoaleatorio_aes.hh"
#include "../../acceso_a_datos/cabeceras/acceso_simulado.hh"
#include "../../../utilidades/cabeceras/arreglo_de_digitos.hh"
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

  class FuncionRN : public Utilidades::Funcion<ArregloDeDigitos,
    unsigned int>
  {
    public:
      /** \brief Alias para función interna. */
      using FuncionInterna = Funcion<Arreglo<unsigned char>, entero>;

      /** \brief Inicialización de parámetros. */
      FuncionRN(FuncionInterna* funcionInterna,
        CDV* baseDeDatos = new AccesoSimulado,
        unsigned int longitudDeCadena = 16u,
        unsigned int cardinalidadDeAlfabeto = 10u);

      /** \brief Liberación de memoria. */
      ~FuncionRN();

      /** \brief Generación de token pseudoaleatorio. */
      ArregloDeDigitos operar(const std::vector<unsigned int>& entrada) override;

      /** \brief Redistribuye los bytes del arreglo dado. */
      Arreglo<unsigned char> redistribuir(
        const Arreglo<unsigned char> &original);

    private:
      /** \brief Apuntador a primitiva subyacente. */
      FuncionInterna* mFuncionInterna;

      /** \brief Apuntador a una clase de acceso a datos. */
      CDV* mBaseDeDatos;

      /** \brief Longitud de cadenas resultado */
      unsigned int mLongitudDeCadena;

      /** \brief Cardinalidad del alfabeto usado. */
      unsigned int mCardinalidadDeAlfabeto;

      /** \brief Longitud en bits de cada elemento de cadena. */
      unsigned int mLongitudDeBits;

      /** \brief Contador usado como estado para función interna. */
      entero mContador;
  };
}

#endif
