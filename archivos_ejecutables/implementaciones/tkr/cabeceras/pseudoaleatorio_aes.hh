/**
 * \file
 * \brief Generación de pseudoaleatorio con AES.
 */

#ifndef __PSEUDOALEATORIO_AES__
#define __PSEUDOALEATORIO_AES__

#include "../../../utilidades/cabeceras/utilidades_matematicas.hh"
#include "../../../utilidades/interfaces_comunes/funcion.hh"
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <vector>

namespace Implementaciones
{
  /**
   * \brief Generación de número pseudoaleatorio usando AES.
   *
   * Función usada como generador aleatorio interno en \ref FuncionRN.
   * Procedimiento descrito en artículo de TKR.
   *
   * \todo Generalizar para que funcione con cualquier cifrador por
   * bloque de cryptopp.
   */

  class PseudoaleatorioAES
  : public Utilidades::Funcion<Arreglo<unsigned char>, entero>
  {
    public:
      /** \brief Inicialización de parámetros */
      PseudoaleatorioAES(unsigned char *llave);

      /** \brief Liberación de memoria */
      ~PseudoaleatorioAES();

      /** \brief Genera una secuencia de bytes de la longitud pedida. */
      Arreglo<unsigned char> operar(
        const std::vector<entero>& entrada) override;

    private:
      /** \brief Llave para cifrador por bloques. */
      unsigned char *mLlave;

      /** \brief Instancia de cifrador AES. */
      CryptoPP::AES::Encryption mCifradoAES;

      /** \brief Modo de operación ECB. */
      CryptoPP::ECB_Mode_ExternalCipher::Encryption mCifradoECB;

      /** \brief Flujo de cifrador. */
      void cifrar(unsigned char *origen, unsigned char *destino, int contador);
  };
}

#endif
