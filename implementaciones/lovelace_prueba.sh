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
  echo "Prueba con FFX ==============================="

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
  echo "Prueba con BPS ==============================="

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
  echo "Prueba con TKR ==============================="

  $ejecutable -k temporal.llave 16
  echo "Llave: "
  cat temporal.llave
  echo ""

  panUno=$($ejecutable -r)
  echo "PAN original: " $panUno

  tokenUno=$($ejecutable -e TKR $panUno temporal.llave)
  echo "Token: " $tokenUno

  panUnoDescifrado=$($ejecutable -d TKR $tokenUno temporal.llave)
  echo "Pan descifrado: " $panUnoDescifrado

  rm temporal.llave
  if [ $panUno -eq $panUnoDescifrado ]; then
    echo "Prueba de TKR exitosa."
  else
    echo "Error en TKR."
    exit -1
  fi
  echo ""

done
exit 0
