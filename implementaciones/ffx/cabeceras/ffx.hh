/**
 * \file
 * \brief Definición e implementación de FFX
 *
 * Fuera de la clase pero en el mismo espacio de nombres se declaran funciones
 * de suma y resta (por caracter y por bloque) para usar como argumentos en
 * la operación de combinación de la red Feistel. Estas funciones reciben
 * valores numéricos desde los argumentos del template (no de la función), para
 * que la firma siga sirviendo como argumento de la red Feistel (los alias
 * definidos ahí).
 *
 * \todo ¿Cómo hace esto el compilador? ¿Cuál es la diferencia entre un
 * argumento de template y uno de función?
 *
 * En cuanto a las implementaciones de las funciones, técnicamente ambas
 * versiones funcionan bien, sin embargo, la versión por bloques es más lenta
 * que la versión por caracter; esto porque la primera tiene que hacer
 * conversiones de número a arreglo y de arreglo a número.
 *
 * Proyecto Lovelace.
 */

#ifndef __FFX__
#define __FFX__

#include "arreglo.hh"
#include "red_feistel.hh"
#include "red_feistel_alternante.hh"
#include "red_feistel_desbalanceada.hh"

#include <cryptopp/aes.h>
#include <cryptopp/cbcmac.h>
#include <cmath>

namespace Implementaciones
{

  /**
   * \brief Implementación de FFX.
   *
   * \tparam tipo Tipo de dato con el que opera el algoritmo.
   */

  template <typename tipo>
  class FFX
  {
    public:

      /** \brief Enumera los tipos de redes Feistel. */
      enum class TipoDeRed {alternante, desbalanceada};

      /** \brief Enumera los tipos de suma. */
      enum class TipoDeSuma {porCaracter, porBloque};

      /** \brief Inicialización de parámetros de FFX. */
      FFX(unsigned char *llave, unsigned char *tweak, int tamanioTweak
        int numeroDeRondas, int tamanioDeMensaje,
        int desbalanceo = 0, TipoDeRed tipoDeRed = TipoDeRed::alternante,
        TipoDeSuma tipoDeSuma = TipoDeSuma::porCaracter,
        funcionDeOperacion<tipo> funcionDeRonda = operacionTrivial<tipo>,
        funcionDeOperacion<tipo> funcionDeRondaImpar = nullptr, int radix = 10);

      /** \brief Proceso de cifrado. */
      Arreglo<tipo> cifrar(Arreglo<tipo> textoEnClaro);

      /** \brief Proceso de descifrado. */
      Arreglo<tipo> descifrar(Arreglo<tipo> textoCifrado);

    private:

      /** \brief */
      int mRadix;

      /** \brief Red Feistel. */
      RedFeistel<tipo> mRedFeistel = nullptr;

  };

  /** \brief Suma por bloques */
  template<typename tipo, int base>
  Arreglo<tipo> sumaPorBloque(const Arreglo<tipo>& arregloUno,
    const Arreglo<tipo>& arregloDos);

  /** \brief Suma por bloques */
  template<typename tipo, int base>
  Arreglo<tipo> restaPorBloque(const Arreglo<tipo>& arregloUno,
    const Arreglo<tipo>& arregloDos);

  /** \brief Suma por bloques */
  template<typename tipo, int base>
  Arreglo<tipo> sumaPorCaracter(const Arreglo<tipo>& arregloUno,
    const Arreglo<tipo>& arregloDos);

  /** \brief Suma por bloques */
  template<typename tipo, int base>
  Arreglo<tipo> restaPorCaracter(const Arreglo<tipo>& arregloUno,
    const Arreglo<tipo>& arregloDos);

  /** \brief Función de ronda con CBC MAC AES. */
  template<typename tipo, unsigned char *llave,
    unsigned char *tweak, int longitudTweak, int tipoDeRed, int tipoDeSuma,
    int radix, int longitud, int desbalanceo, int numeroDeRondas>
  Arreglo<tipo> funcionRondaCbcMacAes(const Arreglo<tipo>& textoEnClaro);

  /** \brief Función de módulo */
  int modulo(int numeroUno, int numeroDos);

  /**
   * El desbalanceo por defecto es 0 (lo más cerca del centro posible).
   * El radix por defecto es 10: valor utilizado para el cifrado de dígitos.
   */

  template <typename tipo>
  FFX<tipo>::FFX(
    /** */
    unsigned char *llave,
    /** */
    unsigned char *tweak,
    /** */
    int tamanioTweak
    /** Número de rondas de la red Feistel subyacente. */
    int numeroDeRondas,
    /** Tamaño de las cadenas */
    int tamanioDeMensaje,
    /** Grado de desbalanceo */
    int desbalanceo,
    /** Tipo de red Feistel a ocupar. */
    TipoDeRed tipoDeRed,
    /** Tipo de suma a utilizar. */
    TipoDeSuma tipoDeSuma,
    /** Función ocupada en cada ronda. */
    funcionDeOperacion<tipo> funcionDeRonda,
    /** Función ocupada en rondas impares (solo para redes alternantes). */
    funcionDeOperacion<tipo> funcionDeRondaImpar,
    /** Cardinalidad de alfabeto. */
    int radix
  )
  :
  {
    /* Instanciar funciones de suma y resta */
    funcionDeCombinacion<tipo> operadorSuma =
      (tipoDeSuma == TipoDeSuma::porBloque)
      ? sumaPorBloque<tipo, radix>
      : sumaPorCaracter<tipo, radix>;
    funcionDeCombinacion<tipo> operadorResta =
      (tipoDeSuma == TipoDeSuma::porBloque)
      ? restaPorBloque<tipo, radix>
      : restaPorCaracter<tipo, radix>;

    /* Crear función de ronda */
    funcionDeOperacion<tipo> funcionDeRonda = funcionRondaCbcMacAes<tipo,
      llave, tweak, longitudTweak, tipoDeRed, tipoDeSuma, radix,
      tamanioDeMensaje, desbalanceo, numeroDeRondas>

    /* Instanciar red Feistel. */
    if (tipoDeRed == TipoDeRed::alternante)
      redFeistel = RedFeistelAlternante<tipo>{numeroDeRondas,
        tamanioDeMensaje, desbalanceo, funcionDeRonda, funcionDeRonda,
        operadorSuma, operadorResta};
    else
      redFeistel = RedFeistelDesbalanceada<tipo>{numeroDeRondas,
        tamanioDeMensaje, desbalanceo, funcionDeRonda,
        operadorSuma, operadorResta};
  }

  /**
   * \return Mensaje cifrado.
   */

  template <typename tipo>
  Arreglo<tipo> FFX<tipo>::cifrar(
    Arreglo<tipo> textoEnClaro        /**< Mensaje a cifrar. */
  )
  {
    return mRedFeistel.cifrar(textoEnClaro);
  }

  /**
   * \return Mensaje descifrado.
   */

  template <typename tipo>
  Arreglo<tipo> FFX<tipo>::descifrar(
    Arreglo<tipo> textoCifrado        /**> Mensaje a descifrar. */
  )
  {
    return mRedFeistel.descifrar(textoCifrado);
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

  template<typename tipo, int base>
  Arreglo<tipo> sumaPorBloque(
    const Arreglo<tipo>& arregloUno,      /**< Primer operando. */
    const Arreglo<tipo>& arregloDos       /**< Segundo operando. */
  )
  {
    int tamanio {arregloUno.obtenerNumeroDeElementos()};
    int numeroUno {arregloUno.convertirANumero(base)};
    int numeroDos {arregloDos.convertirANumero(base)};
    return Arreglo<tipo>::convertirAArreglo(modulo((numeroUno + numeroDos),
      static_cast<int>(pow(base, tamanio))), base, tamanio);
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

  template<typename tipo, int base>
  Arreglo<tipo> restaPorBloque(
    const Arreglo<tipo>& arregloUno,      /**< Primer operando. */
    const Arreglo<tipo>& arregloDos       /**< Segundo operando. */
  )
  {
    int tamanio {arregloUno.obtenerNumeroDeElementos()};
    int numeroUno {arregloUno.convertirANumero(base)};
    int numeroDos {arregloDos.convertirANumero(base)};
    return Arreglo<tipo>::convertirAArreglo(modulo((numeroUno - numeroDos),
      static_cast<int>(pow(base, tamanio))), base, tamanio);
  }

  /**
   * Realiza la suma dígito por dígito módulo la base.
   * Por ejemplo:
   * 79 + 12 = 81
   * 50 + 67 = 17
   *
   * \return Arreglo con suma por caracter.
   */

  template<typename tipo, int base>
  Arreglo<tipo> sumaPorCaracter(
    const Arreglo<tipo>& arregloUno,      /**< Primer operando. */
    const Arreglo<tipo>& arregloDos       /**< Segundo operando. */
  )
  {
    int tamanio {arregloUno.obtenerNumeroDeElementos()};
    Arreglo<tipo> resultado(tamanio);
    for (int i = 0; i < tamanio; i++)
      resultado.colocar(i, modulo((arregloUno[i] + arregloDos[i]), base));
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

  template<typename tipo, int base>
  Arreglo<tipo> restaPorCaracter(
    const Arreglo<tipo>& arregloUno,      /**< Primer operando. */
    const Arreglo<tipo>& arregloDos       /**< Segundo operando. */
  )
  {
    int tamanio {arregloUno.obtenerNumeroDeElementos()};
    Arreglo<tipo> resultado(tamanio);
    for (int i = 0; i < tamanio; i++)
      resultado.colocar(i, modulo((arregloUno[i] - arregloDos[i]), base));
    return resultado;
  }

  /**
   *
   */

  template<
    typename tipo,                        /**< */
    unsigned char *llave,                 /**< */
    unsigned char *tweak,                 /**< */
    int longitudTweak,                    /**< */
    int tipoDeRed,                        /**< */
    int tipoDeSuma,                       /**< */
    int radix,                            /**< */
    int longitud,                         /**< */
    int desbalanceo,                      /**< */
    int numeroDeRondas>                   /**< */
  Arreglo<tipo> funcionRondaCbcMacAes(
    const Arreglo<tipo>& textoEnClaro     /**< */
  )
  {
    /* Armar arreglo de mensaje */
    int longitudEntrada = 8 + longitudTweak + sizeof(int);
    unsigned char entrada [longitudEntrada];
    entrada[0] = 0;
    entrada[1] = static_cast<unsigned char> (tipoDeRed);
    entrada[2] = static_cast<unsigned char> (tipoDeSuma);
    entrada[3] = static_cast<unsigned char> (radix);
    entrada[4] = static_cast<unsigned char> (longitud);
    entrada[5] = static_cast<unsigned char> (desbalanceo);
    entrada[6] = static_cast<unsigned char> (numeroDeRondas);
    entrada[7] = 0;
    for (int i = 0, j = 8; i < longitudTweak; i++, j++)
      entrada[j] = tweak[i];
    int representacionNumero = textoEnClaro.convertirANumero(radix);
    entrada[7 + longitudTweak + 1] =
      static_cast<unsigned char> (representacionNumero);
    entrada[7 + longitudTweak + 2] =
      static_cast<unsigned char> (8 >> representacionNumero);
    entrada[7 + longitudTweak + 3] =
      static_cast<unsigned char> (16 >> representacionNumero);
    entrada[7 + longitudTweak + 4] =
      static_cast<unsigned char> (24 >> representacionNumero);

    /* Generar MAC */
    CryptoPP::CBC_MAC<CryptoPP::AES> cbcmac {llave};
    cbcmac.Update(entrada, longitudEntrada);
    unsigned char mac[cbcmac.DigestSize()];
    cbcmac.TruncatedFinal(mac, cbcmac.DigestSize());

    /* Partir por mitad */
    Arreglo<unsigned char> ladoIzquierdo (8), ladoDerecho(8);
    for (int i = 0; i < 16; i++)
      if (i < 8)
        ladoIzquierdo.colocar(i, mac[i]);
      else
        ladoDerecho.colocar(i - 8, mac[i]);

    int numeroIzquierdo = ladoIzquierdo.convertirANumero(256);
    int numeroDerecho = ladoIzquierdo.convertirANumero(256);
    int m = (longitud / 2) + desbalanceo, z;
    if (m <= 9)
      z = numeroDerecho % static_cast<int>(pow(radix, m));
    else
      z = numeroIzquierdo % static_cast<int>(pow(radix, m - 9))
        * (static_cast<int>(pow(radix, 9))
          + (numeroDerecho % static_cast<int>(pow(radix, 9))));
    return Arreglo<tipo>::convertirAArreglo(z, 10, m);
  }

  /**
   * Envolvente alrededor de la función de módulo normal para lidiar con
   * números negativos: si el primer operando es negativo, se regresa el
   * módulo del complemento.
   *
   * \todo Pasar esto a las utilidades.
   *
   * \return numeroUno % numeroDos
   */

  int modulo(
    int numeroUno,                        /**< Primer operando. */
    int numeroDos                         /**< Segundo operando. */
  )
  {
    return (numeroUno >= 0)
      ? numeroUno % numeroDos
      : numeroDos - ((numeroUno * -1) % numeroDos);
  }

}

#endif
