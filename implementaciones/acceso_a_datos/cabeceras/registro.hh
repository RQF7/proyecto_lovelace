/**
 * \file
 * \brief Declaración de clase de modelo de datos.
 */

#ifndef __REGISTRO__
#define __REGISTRO__

 #include "../../../utilidades/cabeceras/arreglo.hh"

namespace Implementaciones
{
  class Registro
  {
    private:
      Arreglo<int> mPAN;
      Arreglo<int> mToken;
      Arreglo<int> mInformacionAsociada;
    public:
      inline Arreglo<int> obtenerPAN() { return mPan; }
      inline Arreglo<int> obtenerToken() { return mToken; }
      inline Arreglo<int> obtenerInformacionAsociada() {
        return mInformacionAsociada: }
      inline void colocarPAN(Arreglo<int> pan) { mPAN = pan; }
      inline void colocarToken(Arreglo<int> token) {mToken = token; }
      inline void colocarInformacionAsociada(Arreglo<int> mInformacionAsociada){
        mInformacionAsociada = mInformacionAsociada; }
  };
}

#endif
