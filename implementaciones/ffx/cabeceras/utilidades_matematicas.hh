/**
 * \brief Declaración y definición de funciones matemáticas comunes.
 * En la mayoría de los casos el tipo de los operadores es un template, por lo
 * que la implementación se encuentra junto a la declaración.
 * Proyecto Lovelace.
 */

#ifndef __UTILIDADES_MATEMATICAS__
#define __UTILIDADES_MATEMATICAS__

namespace Implementaciones
{
  /** \brief Operación de módulo. */
  template <typename tipo>
  tipo modulo(tipo numeroUno, tipo numeroDos);

  /**
   * Envolvente alrededor de la función de módulo normal para lidiar con
   * números negativos: si el primer operando es negativo, se regresa el
   * módulo del complemento.
   *
   * \return numeroUno % numeroDos
   */

  template <typename tipo>
  tipo modulo(
    tipo numeroUno,                        /**< Primer operando. */
    tipo numeroDos                         /**< Segundo operando. */
  )
  {
    return (numeroUno >= 0)
      ? numeroUno % numeroDos
      : numeroDos - ((numeroUno * -1) % numeroDos);
  }
}

#endif
