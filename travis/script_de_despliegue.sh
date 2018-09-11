#!/bin/bash

#
# Script para ejecutar en droplet de digital ocean.
# Fase de despliegue.
#
# Proyecto Lovelace.
#

./travis/actualizar_repositorio.sh $1
npm install
grunt
. entorno_virtual/bin/activate
./travis/reiniciar_modelos $2
./travis/reiniciar_apache.sh $2
systemctl status apache2
