/**
 * \file
 * \brief Implementación de función de ronda de FFX.
 *
 * Proyecto Lovelace.
 */

#ifndef __RONDA_FFX_A10__
#define __RONDA_FFX_A10__

#include "../../../utilidades/cabeceras/arreglo.hh"
#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include "../../../utilidades/interfaces_comunes/funcion_con_inverso_simetrico.hh"
#include <cryptopp/aes.h>
#include <cryptopp/cbcmac.h>
#include <iostream>

namespace Implementaciones
{
  /**
   * \brief Función de ronda de FFX.
   *
   * La función de ronda de FFX es simétrica: solo se tiene que definir la
   * operación de ida, la de vuelta la define *FuncionConInversoSimetrico*.
   *
   * Uno de los inconvenientes que (a mi modo de ver) tiene esta función de
   * ronda es que depende mucho del nivel superior, de los parámetros de FFX.
   * Me parecería más elegante una función de ronda que no se preocupe por
   * cosas como el tipo de red, o el tipo de suma; cuando menos más modular.
   */

  template <typename tipo>
  class RondaFFXA10
  : public Utilidades::FuncionConInversoSimetrico<Arreglo<tipo>, Arreglo<tipo>>
  {
    public:

      /** \brief Construye una nueva instancia de la función. */
      RondaFFXA10(unsigned char *llave, unsigned char *tweak,
        unsigned int longitudTweak, int tipoDeRed, int tipoDeSuma,
        unsigned int radix, unsigned int longitud, int desbalanceo,
        unsigned int numeroDeRondas);

      /** \brief Liberación de memoria. */
      ~RondaFFXA10();

      /** \brief Función de ronda. */
      Arreglo<tipo> operar(const std::vector<Arreglo<tipo>> &entrada) override;

      /** \brief Escritura sobre el tweak. */
      inline void colocarTweak(unsigned char *tweak, int longitudTweak)
        { mTweak = tweak; mLongitudTweak = longitudTweak; }

    private:

      /** \brief Llave de 64 bits (AES). */
      unsigned char *mLlave;

      /** \brief Tweak (longitud variable). */
      unsigned char *mTweak;

      /** \brief Longitud del tweak dado. */
      unsigned int mLongitudTweak;

      /** \brief Tipo de red usada (desbalanceada, alternante). */
      int mTipoDeRed;

      /** \brief Tipo de suma (por bloques, por caracter). */
      int mTipoDeSuma;

      /** \brief Cardinalidad del alfabeto usado. */
      unsigned int mRadix;

      /** \brief Longitud de los mensajes dados. */
      unsigned int mLongitud;

      /** \brief Grado de desbalanceo de la red. */
      int mDesbalanceo;

      /** \brief Número de rondas. */
      unsigned int mNumeroDeRondas;

      /** \brief Longitud del arreglo de entrada a primitiva. */
      unsigned int mLongitudEntrada;

      /** \brief Entrada a primitiva. */
      unsigned char *mEntrada;
  };

  /**
   * A excepción de los tres primeros argumentos, todos los demás son meramente
   * decorativos: se usan solo para rellenar el bloque de entrada del MAC. En
   * una implementación completa (junto con una entidad de FFX superior), estos
   * parámetros serán constantes a lo largo de las iteraciones de la red.
   *
   * En la versión original, la inicialización del arreglo de entrada (el
   * cuerpo de este constructor) se encuentra en la función de ronda. En
   * esta implementación se cambió de lugar buscando optimizar un poco la
   * ejecución.
   *
   * \param llave           Llave de 64 bits (AES).
   * \param tweak           Tweak (longitud variable).
   * \param longitudTweak   Longitud del tweak dado.
   * \param tipoDeRed       Tipo de red usada (desbalanceada, alternante).
   * \param tipoDeSuma      Tipo de suma (por bloques, por caracter).
   * \param radix           Cardinalidad del alfabeto usado.
   * \param longitud        Longitud de los mensajes dados.
   * \param desbalanceo     Grado de desbalanceo de la red.
   * \param numeroDeRondas  Número de rondas.
   */

  template<typename tipo>
  RondaFFXA10<tipo>::RondaFFXA10(
    unsigned char *llave,
    unsigned char *tweak,
    unsigned int longitudTweak,
    int tipoDeRed,
    int tipoDeSuma,
    unsigned int radix,
    unsigned int longitud,
    int desbalanceo,
    unsigned int numeroDeRondas
  )
  : mLlave{llave},
    mTweak{tweak},
    mLongitudTweak{longitudTweak},
    mTipoDeRed{tipoDeRed},
    mTipoDeSuma{tipoDeSuma},
    mRadix{radix},
    mLongitud{longitud},
    mDesbalanceo{desbalanceo},
    mNumeroDeRondas{numeroDeRondas},
    mLongitudEntrada{8 + mLongitudTweak + sizeof(int)},
    mEntrada{new unsigned char[mLongitudEntrada]}
  {
    /* Datos fijos. */
    mEntrada[0] = 0;
    mEntrada[1] = static_cast<unsigned char>(mTipoDeRed);
    mEntrada[2] = static_cast<unsigned char>(mTipoDeSuma);
    mEntrada[3] = static_cast<unsigned char>(mRadix);
    mEntrada[4] = static_cast<unsigned char>(mLongitud);
    mEntrada[5] = static_cast<unsigned char>(mDesbalanceo);
    mEntrada[6] = static_cast<unsigned char>(mNumeroDeRondas);
    mEntrada[7] = 0;

    /* Tweak. */
    for (unsigned int i = 0, j = 8; i < mLongitudTweak; i++, j++)
      mEntrada[j] = mTweak[i];
  }

  /**
   * Libera el arreglo de entrada a la primitiva.
   */

  template<typename tipo>
  RondaFFXA10<tipo>::~RondaFFXA10()
  {
    delete[] mEntrada;
  }

  /**
   * Implementación de función de ronda con CBC-MAC-AES.
   *
   * \return Texto cifrado de la longitud necesaria.
   */

  template<typename tipo>
  Arreglo<tipo> RondaFFXA10<tipo>::operar(
    const std::vector<Arreglo<tipo>> &textoEnClaro    /**< Texto a cifrar. */
  )
  {
    /* Representación numérica de mensaje. */
    entero representacionNumero = convertirANumero<tipo, entero>(
      textoEnClaro[0], mRadix);
    for (int i = 0; i < 8; i++)
      mEntrada[7 + mLongitudTweak + i + 1] =
        static_cast<unsigned char>(representacionNumero >> (8 + i));

    /* Generar MAC */
    CryptoPP::CBC_MAC<CryptoPP::AES> cbcmac {mLlave};
    cbcmac.Update(mEntrada, mLongitudEntrada);
    unsigned char mac[cbcmac.DigestSize()];
    cbcmac.TruncatedFinal(mac, cbcmac.DigestSize());

    /* Partir por mitad */
    Arreglo<int> ladoIzquierdo (8), ladoDerecho(8);
    for (int i = 0; i < 16; i++)
      if (i < 8)
        ladoIzquierdo[i] = mac[i];
      else
        ladoDerecho[i - 8] = mac[i];

    /* Formatear salida a longitud adecuada. */
    entero numeroIzquierdo = convertirANumero<int, entero>(ladoIzquierdo, 256);
    entero numeroDerecho = convertirANumero<int, entero>(ladoDerecho, 256);
    entero z;
    if (mLongitud <= 9)
      z = modulo(numeroDerecho, potencia<entero>(mRadix, mLongitud));
    else
      z = (modulo(numeroIzquierdo, potencia<entero>(mRadix, mLongitud - 9))
        * potencia<entero>(mRadix, 9))
        + modulo(numeroDerecho, potencia<entero>(mRadix, 9));

    return convertirAArreglo<tipo, entero>(z, mRadix, mLongitud);
  }

}

#endif
