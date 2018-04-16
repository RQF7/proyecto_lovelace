#!/bin/sh

#
# Ejecución de pruebas de desempeño.
#
# Proyecto Lovelace.
#

ip_base=159.65.96.59
puerto_base=3306
usuario=administrador_lovelace_pruebas
contrasenia=l0v3lac3-padmin

ejecutable=./binarios/pruebas_desempenio
comando="$ejecutable $ip_base $puerto_base $usuario $contrasenia"

algoritmos=( FFX BPS TKR AHR DRBG )
pruebas=( 10 100 1000 )

cd implementaciones

for algoritmo in "${algoritmos[@]}"
do
  for numero in "${pruebas[@]}"
  do
    $comando ${algoritmo} ${numero}
  done
done

cd ..
