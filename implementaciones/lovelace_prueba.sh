#!/bin/bash

#
# Prueba de programa tokenizador.
# Recibe de la línea de comandos el número de pruebas a realizar.
#
# Proyecto lovelace.
#

ejecutable=./binarios/lovelace
numeroDePruebas=$1

for i in `seq 1 $numeroDePruebas`
do

  # Prueba de FFX #############################################################
  echo "Prueba $i con FFX ==============================="

  $ejecutable -k temporal.llave 16
  echo "Llave: "
  cat temporal.llave
  echo ""

  panUno=$($ejecutable -r)
  echo "PAN original: " $panUno

  tokenUno=$($ejecutable -e FFX $panUno temporal.llave)
  echo "Token: " $tokenUno

  panUnoDescifrado=$($ejecutable -d FFX $tokenUno temporal.llave)
  echo "Pan descifrado: " $panUnoDescifrado

  rm temporal.llave
  if [ $panUno -eq $panUnoDescifrado ]; then
    echo "Prueba de FFX exitosa."
  else
    echo "Error en FFX."
    exit -1
  fi
  echo ""

  # Prueba de BPS #############################################################
  echo "Prueba $i con BPS ==============================="

  $ejecutable -k temporal.llave 16
  echo "Llave: "
  cat temporal.llave
  echo ""

  panUno=$($ejecutable -r)
  echo "PAN original: " $panUno

  tokenUno=$($ejecutable -e BPS $panUno temporal.llave)
  echo "Token: " $tokenUno

  panUnoDescifrado=$($ejecutable -d BPS $tokenUno temporal.llave)
  echo "Pan descifrado: " $panUnoDescifrado

  rm temporal.llave
  if [ $panUno -eq $panUnoDescifrado ]; then
    echo "Prueba de BPS exitosa."
  else
    echo "Error en BPS."
    exit -1
  fi
  echo ""

  # Prueba de TKR #############################################################
  echo "Prueba $i con TKR ==============================="

  $ejecutable -k temporal.llave 16
  echo "Llave: "
  cat temporal.llave
  echo ""

  panUno=$($ejecutable -r)
  echo "PAN original: " $panUno

  tokenUno=$($ejecutable -e TKR $panUno temporal.llave)
  echo "Token: " $tokenUno

  panUnoDescifrado=$($ejecutable -d TKR $tokenUno)
  echo "Pan descifrado: " $panUnoDescifrado

  rm temporal.llave
  if [ $panUno -eq $panUnoDescifrado ]; then
    echo "Prueba de TKR exitosa."
  else
    echo "Error en TKR."
    exit -1
  fi
  echo ""

  # Prueba de AHR #############################################################
  echo "Prueba $i con AHR ==============================="

  $ejecutable -k temporal.llave 32
  echo "Llave: "
  cat temporal.llave
  echo ""

  panUno=$($ejecutable -r)
  echo "PAN original: " $panUno

  tokenUno=$($ejecutable -e AHR $panUno temporal.llave)
  echo "Token: " $tokenUno

  panUnoDescifrado=$($ejecutable -d AHR $tokenUno)
  echo "Pan descifrado: " $panUnoDescifrado

  rm temporal.llave
  if [ $panUno -eq $panUnoDescifrado ]; then
    echo "Prueba de AHR exitosa."
  else
    echo "Error en AHR."
    exit -1
  fi
  echo ""

  # Prueba de DRBG ############################################################
  echo "Prueba $i con DRBG ==============================="

  panUno=$($ejecutable -r)
  echo "PAN original: " $panUno

  tokenUno=$($ejecutable -e DRBG $panUno)
  echo "Token: " $tokenUno

  panUnoDescifrado=$($ejecutable -d DRBG $tokenUno)
  echo "Pan descifrado: " $panUnoDescifrado

  if [ $panUno -eq $panUnoDescifrado ]; then
    echo "Prueba de DRBG exitosa."
  else
    echo "Error en DRBG."
    exit -1
  fi
  echo ""

done
exit 0
