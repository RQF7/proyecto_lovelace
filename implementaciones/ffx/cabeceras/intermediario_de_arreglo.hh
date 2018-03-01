
#ifndef __INTERMEDIARIO_DE_ARREGLO__
#define __INTERMEDIARIO_DE_ARREGLO__

namespace Implementaciones
{
  /* Para evitar referencias circulares. */
  template<typename tipo>
  class Arreglo;

  /**
   * \brief
   */

  template <typename tipo>
  class IntermediarioDeArreglo
  {
    public:

      /** \brief Construcción de intermediario. */
      IntermediarioDeArreglo(Arreglo<tipo> &arreglo, int indice);

      /** \brief Sobrecarga de operador de asignación. */
      tipo& operator=(tipo elemento);

    private:

      /** \brief Referencia a arreglo. */
      Arreglo<tipo>& mArreglo;

      /** \brief Índice de arreglo. */
      int mIndice;
  };

  /**
   *
   */

  template<typename tipo>
  IntermediarioDeArreglo<tipo>::IntermediarioDeArreglo(
    Arreglo<tipo>& arreglo,     /** Referencia a arreglo. */
    int indice                  /** Índice de arreglo. */
  )
  : mArreglo {arreglo},
    mIndice {indice}
  {
  }

  /**
   *
   */

   template<typename tipo>
   tipo& IntermediarioDeArreglo<tipo>::operator=(tipo elemento)
   {
     mArreglo.mArregloInterno[mIndice] = elemento;
     return  mArreglo.mArregloInterno[mIndice];
   }

}

#endif
