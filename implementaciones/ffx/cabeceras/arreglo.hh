/**
 * \file
 * \brief Implementación y definición de contenedor Arreglo.
 *
 * Al tratarse de una clase con plantillas («template»), la declaración y
 * la implementación deben estar juntas, en un mismo archivo; si se
 * intentan ligar por separado, hay problemas al ligar. Al parecer es técnica
 * estándar definir a las clases con plantillas dentro de los archivos de
 * cabeceras.
 */

#ifndef __ARREGLO__
#define __ARREGLO__

#include <ostream>

namespace Implementaciones
{
  /* Declaración *************************************************************/

  /**
   * \brief Contenedor de datos secuencial.
   *
   * Clase contenedor para datos secuenciales. El funcionamiento es muy similar
   * al «array» de la librería estándar (la ventaja es que con una
   * implementación propia podemos controlar operaciones de bajo nivel).
   *
   * Esta clase encapsula las operaciones de bajo nivel (con apuntadores y de
   * manejo de memoria) para ofrecer una interfaz clara y de alto nivel.
   *
   * \todo ¿En qué parte se refleja la documentación del template?
   *
   * \tparam tipo Tipo de dato del contenedor.
   */

  template <typename tipo>
  class Arreglo
  {
    public:

      /** \brief Construcción de arreglo del tamaño dado. */
      Arreglo(int numeroDeElementos);

      /** \brief Destructor de arreglo. */
      ~Arreglo();

      /** \brief Operación de lectura. */
      tipo operator[] (int indice) const;

      /** \brief Operación de escritura. */
      void colocar(int indice, tipo valor);

      /** \brief Regresa el tamaño del arreglo. */
      inline int obtenerNumeroDeElementos() const { return mNumeroDeElementos; }

      /** \brief Parte el arreglo según parámetros. */
      Arreglo<tipo> partir(int numeroDePartes, int parte);

    private:

      /** \brief Apuntador a sección de memoria con el contenido del arreglo.*/
      tipo *mArregloInterno;

      /** \brief Tamaño del arreglo (entero mayor a cero). */
      int mNumeroDeElementos;
  };

  /** \brief Impresión de un arreglo. */
  template <typename tipo>
  std::ostream& operator<<(std::ostream &flujo, const Arreglo<tipo> &arreglo);

  /** \brief Concatenación de dos arreglos. */
  template <typename tipo>
  Arreglo<tipo> operator+(const Arreglo<tipo> &arregloUno,
    const Arreglo<tipo> &arregloDos);

  /* Definición **************************************************************/

  /**
   * Reserva la memoria necesaria para el arreglo. El tamaño reservado equivale
   * al tamaño del tipo de dato multiplicado por el número de elementos.
   *
   * \todo comprobación de tamaño (máximo, mínimo).
   */

  template<typename tipo>
  Arreglo<tipo>::Arreglo(
    int numeroDeElementos /**< Número de elementos del arreglo. */
  ) :
    mNumeroDeElementos {numeroDeElementos}
  {
    mArregloInterno = new tipo[mNumeroDeElementos];
  }

  /**
   * Libera la memoria reservada para un arreglo.
   */

  template<typename tipo>
  Arreglo<tipo>::~Arreglo()
  {
    delete[] mArregloInterno;
  }

  /**
   * Regresa el elemento del arreglo en la posición dada.
   *
   * \return Elemento en la posición solicitada.
   *
   * \todo Comprobación de índice válido.
   */

  template<typename tipo>
  tipo Arreglo<tipo>::operator[](
    int indice /**< Índice de lectura. */
  ) const
  {
    return mArregloInterno[indice];
  }

  /**
   * Guarda el valor dado en la posición dada.
   *
   * \todo comprobación de índice válido.
   */

  template<typename tipo>
  void Arreglo<tipo>::colocar(
    int indice, /**< Posición del arreglo. */
    tipo valor  /**< Valor a guardar. */
  )
  {
    mArregloInterno[indice] = valor;
  }

  /**
   * Regresa un subarreglo del arreglo actual: primero se parte en
   * `numeroDePartes` distintas, y después se crea un nuevo arreglo con
   * la parte número `parte`.
   *
   * \warning El tamaño de la subdivisión está determinado por un división
   * entre enteros (truncada); en caso de división no entera y de petición
   * de último fragmento, los últimos elementos no van.
   *
   * \return Subarreglo número `parte`.
   *
   * \todo Soporte en los argumentos para solicitar varias partes a la vez.
   * \todo Validar coherencia en argumentos.
   */

  template<typename tipo>
  Arreglo<tipo> Arreglo<tipo>::partir(
    int numeroDePartes, /**< Número de particiones a hacer. **/
    int parte           /**< Número de partición deseada. **/
  )
  {
    int tamanioDeDivision = mNumeroDeElementos / numeroDePartes;
    Arreglo<tipo> subArreglo {tamanioDeDivision};
    for (int i = tamanioDeDivision * parte, j = 0;
      i < tamanioDeDivision * (parte + 1); i++, j++)
      subArreglo.colocar(j, mArregloInterno[i]);
    return subArreglo;
  }

  /**
   * Coloca en el flujo los elementos del arreglo separados por un
   * espacio. La disponibilidad de esta operación depende de la existencia
   * de una operación equivalente para un elemento del arreglo (error en
   * compilación).
   *
   * \return Referencia a flujo dado (para concatenar operaciones).
   *
   * \todo ¿Cómo hacer que el separador sea un parámetro más?
   */

  template <typename tipo>
  std::ostream& operator<<(
    std::ostream &flujo,          /**< Flujo de impresión. */
    const Arreglo<tipo> &arreglo  /**< Arreglo a imprimir. */
  )
  {
    for (int i = 0; i < arreglo.obtenerNumeroDeElementos(); i++)
      flujo << arreglo[i] << " ";
    return flujo;
  }

  /**
   * Operación de concatenación de arreglo: crea un nuevo objeto con
   * espacio para concatenar a los dos arreglos dados y los coloca en el
   * orden dado (la operación no es conmutativa).
   *
   * \todo Validación de coherencia de tipos.
   */

  template <typename tipo>
  Arreglo<tipo> operator+(
    const Arreglo<tipo> &arregloUno,  /**< Primer arreglo de concatenación. */
    const Arreglo<tipo> &arregloDos   /**< Segundo arreglo de concatenación. */
  )
  {
    int mitad = arregloUno.obtenerNumeroDeElementos();
    int total = mitad + arregloDos.obtenerNumeroDeElementos();
    Arreglo<tipo> resultado {total};
    for (int i = 0; i < total; i++)
      resultado.colocar(i, (i < mitad) ? arregloUno[i] : arregloDos[i - mitad]);
    return resultado;
  }
}

#endif
