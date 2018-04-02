/**
 * \file
 * \brief Declaración de plantilla para intermediario de arreglos.
 *
 * Proyecto Lovelace.
 */

#ifndef __INTERMEDIARIO_DE_ARREGLO__
#define __INTERMEDIARIO_DE_ARREGLO__

/* Para evitar referencias circulares. */
template<typename tipo>
class ArregloBase;

namespace Utilidades
{
  /**
   * \brief Clase intermediario para arreglo.
   *
   * Patrón de diseño de intermediario (Proxy object). Permite seguir teniendo
   * acceso a un elemento dado del arreglo después de utilizar el operador de
   * índice ([]). De esta manera se pueden hacer operaciones de escritura
   * (lo que antes hacía la operación de Arreglo::colocar).
   *
   * \tparam tipo Tipo de arreglo del que se es intermediario.
   */

  template <typename tipo>
  class IntermediarioDeArreglo
  {
    public:

      /** \brief Construcción de intermediario. */
      IntermediarioDeArreglo(ArregloBase<tipo> &arreglo, int indice);

      /** \brief Sobrecarga de operador de asignación. */
      virtual tipo& operator=(tipo elemento);

      /** \brief Operador de conversión implícita */
      operator tipo&();

      /* Solo para no mandar al olvido mis inútiles esfuerzos antes de descubrir
       * las conversiones implícitas entre tipos: */

//      /** \brief Sobrecarga de operador de igualdad. */
//      inline bool operator==(const tipo& elemento)
//        { return mArreglo.mArregloInterno[mIndice] == elemento; }
//
//      /** \brief Sobrecarga de operador de desigualdad. */
//      inline bool operator!=(const tipo& elemento)
//        { return mArreglo.mArregloInterno[mIndice] != elemento; }
//
//      /** \brief Sobrecarga de operador de desigualdad. */
//      inline bool operator<(const tipo& elemento)
//        { return mArreglo.mArregloInterno[mIndice] < elemento; }
//
//      /** \brief Sobrecarga de operador de desigualdad. */
//      inline bool operator<=(const tipo& elemento)
//        { return mArreglo.mArregloInterno[mIndice] <= elemento; }
//
//      /** \brief Sobrecarga de operador de desigualdad. */
//      inline bool operator>(const tipo& elemento)
//        { return mArreglo.mArregloInterno[mIndice] > elemento; }
//
//      /** \brief Sobrecarga de operador de desigualdad. */
//      inline bool operator>=(const tipo& elemento)
//        { return mArreglo.mArregloInterno[mIndice] >= elemento; }
//
//      /** \brief Sobrecarga de operador de desigualdad. */
//      inline tipo operator*(const tipo& elemento)
//        { return mArreglo.mArregloInterno[mIndice] * elemento; }
//

      /**
       * \brief Sobrecarga de operador de subíndice.
       *
       * Con la conversión automática de tipos debería ser suficiente (esta
       * función debería estar comentada como las de arriba). Sin embargo,
       * por alguna obscura razón, no está funcionando para arreglos con
       * clases. En particular con los vectores:
       * ```
       * Arreglo<vector<int>> p {{1, 2}, {3, 4}};
       * if (p[0][1] == 1)
       *   return true;
       * ```
       * Lo normal sería que la primera operación de subíndice («p[0]»)
       * regresara un intermediario para que después aplicara la
       * conversión automática de tipos (ese intermediario debería poder
       * convertirse de forma implícita a un vector).
       */

      inline auto operator[](int indice)
        { return mArreglo.mArregloInterno[mIndice][indice]; }

    protected:

      /** \brief Referencia a arreglo. */
      ArregloBase<tipo>& mArreglo;

      /** \brief Índice de arreglo. */
      int mIndice;
  };

  /**
   * Construye un nuevo intermediario asociado al arreglo y al índice dados.
   */

  template<typename tipo>
  IntermediarioDeArreglo<tipo>::IntermediarioDeArreglo(
    ArregloBase<tipo>& arreglo,     /** Referencia a arreglo. */
    int indice                      /** Índice de arreglo. */
  )
  : mArreglo {arreglo},
    mIndice {indice}
  {
  }

  /**
   * Operador de asignación. Permite interactuar con el arreglo al que se
   * hace referencia.
   */

  template<typename tipo>
  tipo& IntermediarioDeArreglo<tipo>::operator=(
    tipo elemento                     /* Elemento a escribir. */
  )
  {
    return  mArreglo.mArregloInterno[mIndice] = elemento;
  }

  /**
   * Conversión automática de una instancia de intermediario de arreglo
   * al tipo del arreglo interno. Esto permite que algo como lo
   * siguiente sea válido:
   * ```
   * Arreglo<int> arreglo {8};
   * if (arreglo[0] == 8)
   *   return true;
   * ```
   * Sin esta función sería un error de compilación la comparación lógica,
   * dado que no está definida entre un intermediario de arreglo y un entero.
   * Antes de sacar el error, el compilador intenta hacer conversiones de tipos
   * entre los operandos, y como en este caso un intermediario de arreglo se
   * puede convertir de forma implícita a un entero, todo está en orden.
   *
   * \todo La conversión automática parece no estar funcionando cuando el
   * arreglo se compone de clases (ver el caso de los vectores en operator[]);
   * por ejemplo:
   * ```
   * Arreglo<string> prueba {"uno", "dos"};
   * if (prueba[0] == "uno")
   *   return true;
   * if (string{prueba[0]} == "uno")
   *   return false;
   * ```
   * La primera comparación resulta en un error de compilación.
   */

  template<typename tipo>
  IntermediarioDeArreglo<tipo>::operator tipo&()
  {
    return mArreglo.mArregloInterno[mIndice];
  }

}

#endif
