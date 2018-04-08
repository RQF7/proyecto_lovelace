/**
 * \file
 * \brief Clase del algoritmo híbrido tokenizador AHR.
 */

#ifndef __AHRHH__
#define __AHRHH__

#include "../../acceso_a_datos/cabeceras/cdv.hh"
#include "../../acceso_a_datos/cabeceras/acceso_mysql.hh"
#include "../../aes_ensamblador/cabeceras/aes.hh"
#include "../../utilidades/cabeceras/algoritmo_tokenizador_irreversible.hh"

/** \brief  Tamaño del bloque del cifrador en bytes: 16 bytes = 256 bits*/
#define M 16

namespace Implementaciones
{
  /**
   * \brief Algoritmo tokenizador AHR
   *
   * Propuesto por Longo, Aragona y Sala.
   * El algoritmo requiere de un cifrador por bloque y una función criptográfica:
   * en esta implementación se utiliza AES con una llave de 256 bits y SHA256.
   * Requiere también acceso a la bóveda de datos de tarjeta para poder realizar
   * el proceso de detokenización.
   */

  class AHR : public AlgoritmoTokenizadorIrreversible
  {
  private:
    /** \brief  Entero con la entrada a tokenizar. */
    unsigned long long int mEntradaX;

    /** \brief  Entero con la entrada adicional (tweak). */
    unsigned long long int mEntradaU;

    /** \brief  Entero que almacena el token generado. */
    unsigned long long int mToken;

    /** \brief  Bloque que concatena la salida del SHA256 y la entradaX en
     *  binario.
     */
    unsigned char *mBloqueT;

    /** \brief  Bloque que contiene al bloque cifrado. */
    unsigned char *mBloqueC;

    /** \brief  Número de bytes necesarios para almacenar la entradaX:
      * N = log2(10^L) <- en bits, hay que pasarlo a bytes.
      */
    int mLongitudBytesEntradaX;

    /** \brief  Número de digitos de la entrada X:  */
    int mNumeroDigitosEntradaX;

    /** \brief Cadena que contiene el PAN obtenido mediante AHR. */
    std::string mTokenCompleto;

    /** \brief Cadena que contiene el PAN original. */
    std::string mPANOriginal;

    /** \brief Apuntador a la clase de acceso a la base de datos. */
    CDV* mAccesoADatos;

    /** \brief Cifrador AES para el proceso de tokenización */
    AES mCifrador;

    /** \brief Pasa a binario entradaX y la almacena en los últimos N bits de
      * bloqueT.
      */
    void obtenerBitsX();

    /** \brief Concatena en T la salida truncada del SHA y la entradaX en
      * binario.
      */
    void crearBloqueT();

    /** \brief Guarda en token los últimos N bits de bloqueC en base 10. */
    void obtenerNumeroC();

    /** \brief  Verifica si existen el token creado en la base de datos. */
    bool existeToken();
    /** \brief Operación de tokenización (declarada por la interfaz). */
    ArregloDeDigitos tokenizar(const ArregloDeDigitos&) override;

    /** \brief Método que obtiene el token dada una llave.*/
    void tokenizarHibridamente();

    /** \brief Método que permite acceder a la variable token.*/
    unsigned long long int obtenerToken();

    /** \brief Obtener del PAN, el IIN y el número de cuenta */
    void separarPAN(std::string);

    /** \brief Se concatena el IIN y el dígito verificador al token obtenido. */
    void completarToken();

    /** \brief Permite cambiar la llave que utiliza el cifrador por bloque. */
    void cambiarLlave(unsigned char*);

    /** \brief Operación de detokenización (declarada por la interfaz). */
    ArregloDeDigitos detokenizar(const ArregloDeDigitos&) override;

  public:
    /** \brief Constructor: recibe la referencia a la interfaz con la base
      * de datos que va a utilizar el algoritmo.
      */
    AHR(CDV*, unsigned char*);

    /** \brief Constructor por copia. */
    AHR(AHR const&);

    /** \brief Operador de asignación. */
    AHR& operator= (AHR const&);

    /** \brief Destructor.*/
    ~AHR();

    /** \brief El token dado no existe. */
    struct TokenInexistente : public Utilidades::Error {
      inline TokenInexistente(std::string mensaje)
      : Utilidades::Error{mensaje} {}};

    /** \brief La llave no es de 32 bytes. */
    struct LlaveInadecuada : public Utilidades::Error {
      inline LlaveInadecuada(std::string mensaje)
      : Utilidades::Error{mensaje} {}};
  };
}

#endif
