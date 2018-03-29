/**
 * \file
 * \brief Declaración de un arreglo de dígitos.
 */

#ifndef __ARREGLO_DE_DIGITOS__
#define __ARREGLO_DE_DIGITOS__

#include "arreglo.hh"
#include "intermediario_de_arreglo_de_digitos.hh"
#include "utilidades_matematicas.hh"
#include <ostream>
#include <string>

/**
 * \brief Representación de un arreglo de dígitos.
 *
 * Un arreglo de dígitos es un arreglo de ints. De manera interna guarda en
 * todo momento una representación equivalente en cadena y una representación
 * numérica (como entero de 64 bits).
 */

class ArregloDeDigitos : public Arreglo<int>
{
  public:

    /** \brief Construcción de un arreglo de dígitos a partir de una cadena. */
    ArregloDeDigitos(std::string cadena, int base = 10);

    /** \brief Construcción de un arreglo de dígitos a partir de un número. */
    ArregloDeDigitos(entero numero, int base = 10);

    /** \brief Especialización de arreglo de enteros. */
    ArregloDeDigitos(const Arreglo<int>& arreglo, int base = 10);

    /** \brief Arreglo vacío, solo reserva memoria. */
    ArregloDeDigitos(unsigned int numeroDeElementos, int base = 10);

    /** \brief Arreglo vacío, sin reserva de memoria. */
    ArregloDeDigitos();

    /** \brief Acceso con subíndice. */
    Utilidades::IntermediarioDeArregloDeDigitos operator[](int indice);

    /** \brief Operación de subíndice (constante). */
    int operator[](int indice) const override;

    /** \brief Operación de escritura. */
    [[deprecated]]
    void colocar(int indice, int valor) override;

    /** \brief Regresa la representación en cadena. */
    inline std::string obtenerCadena() const { return mCadena; }

    /** \brief Regresa la representación numérica. */
    inline entero obtenerNumero() const { return mNumero; }

    /** \brief Función de impresión, amiga. */
    friend std::ostream& operator<<(
      std::ostream& flujo, const ArregloDeDigitos &arreglo);

  private:

    /** \brief Representación en cadena. */
    std::string mCadena;

    /** \brief Representación numérica. */
    entero mNumero = 0;

    /** \brief Base en la que se encuentran los dígitos. */
    int mBase;

    /** El intermediario es amigo. */
    friend class Utilidades::IntermediarioDeArregloDeDigitos;
};

/** \brief Impresión de un arreglo de dígitos. */
std::ostream& operator<<(std::ostream& flujo, const ArregloDeDigitos &arreglo);

#endif
