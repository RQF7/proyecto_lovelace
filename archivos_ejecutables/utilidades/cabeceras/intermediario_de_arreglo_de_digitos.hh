/**
 * \file
 * \biref Declaración de intermediario de arreglo de dígitos.
 */

#ifndef __INTERMEDIARIO_DE_ARREGLO_DE_DIGITOS__
#define __INTERMEDIARIO_DE_ARREGLO_DE_DIGITOS__

#include "intermediario_de_arreglo.hh"

/* Para evitar referencias circulares. */
class ArregloDeDigitos;

namespace Utilidades
{
  /**
   * \brief Clase intermediario con arreglo de dígitos.
   *
   * La relación entre esta clase y ArregloDeDigitos imita la que hay
   * Utilidades::IntermediarioDeArreglo y Arreglo. Existe dado que el
   * arreglo de dígitos tiene una asignación propia.
   *
   * Cuando menos la operación de conversión entre tipos sí se hereda de la
   * superclase. También utiliza el mismo índice; sin embargo fue necesarip
   * tener dos referencias: la de la superclase (de tipo Arreglo) y la de esta
   * (de tipo ArregloDeDigitos). ESto porque la operación de asignación
   * ocupa datos propios del arreglo de dígitos.
   */

  class IntermediarioDeArregloDeDigitos : public IntermediarioDeArreglo<int>
  {
    public:

      /** \brief Contructor a partir de referencia. */
      IntermediarioDeArregloDeDigitos(ArregloDeDigitos &arreglo, int indice);

      /** \brief Sobrecarga de operación de asignación. */
      int& operator=(int elemento) override;

    private:

      /** \brief Referencia a arreglo de dígitos asociado. */
      ArregloDeDigitos& mArregloDeDigitos;
  };
}

#endif
