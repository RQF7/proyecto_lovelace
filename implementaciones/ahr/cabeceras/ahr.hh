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
  class AHR : public AlgoritmoTokenizadorIrreversible
  {
  private:
    /** \brief  Entero con la entrada a tokenizar. */
    unsigned long long int entradaX;

    /** \brief  Entero con la entrada adicional (tweak). */
    unsigned long long int entradaU;

    /** \brief  Entero que almacena el token generado. */
    unsigned long long int token;

    /** \brief  Bloque que concatena la salida del SHA256 y la entradaX en
     *  binario.
     */
    unsigned char *bloqueT;

    /** \brief  Bloque que contiene al bloque cifrado. */
    unsigned char *bloqueC;

    /** \brief  Número de bytes necesarios para almacenar la entradaX:
      * N = log2(10^L) <- en bits, hay que pasarlo a bytes.
      */
    int N;

    /** \brief  Número de digitos de la entrada X:  */
    int L;

    /** \brief Cadena que contiene el PAN obtenido. */
    std::string nuevoPAN;

    /** \brief Cadena que contiene el PAN original. */
    std::string viejoPAN;

    /** \brief Apuntador a la clase de acceso a la base de datos. */
    CDV* accesoADatos;

    /** \brief Cifrador AES para el proceso de tokenización */
    AES cifrador;

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

    /** \brief Operación de detokenización (declarada por la interfaz). */
    ArregloDeDigitos detokenizar(const ArregloDeDigitos&) override;
    
  public:
    /** \brief Constructor: recibe la referencia a la interfaz con la base
      * de datos que va a utilizar el algoritmo.
      */
    AHR(CDV*, unsigned char*);

    /** C\brief Constructor por copia. */
    AHR(AHR const&);

    /** \brief Operador de asignación. */
    AHR& operator= (AHR const&);

    /** \brief Destructor.*/
    ~AHR();

    /** \brief El token dado no existe. */
    struct TokenInexistente : public Utilidades::Error {
      inline TokenInexistente(std::string mensaje)
      : Utilidades::Error{mensaje} {}};

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
  };
}

#endif
