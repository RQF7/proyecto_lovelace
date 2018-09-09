#!/bin/sh

#
# Script para ejecutar en droplet de digital ocean.
# Fase de despliegue.
#
# Proyecto Lovelace.
#

cd proyecto_lovelace
./travis/actualizar_repositorio.sh
npm install
grunt
source entorno_virtual/bin/activate
python administrar.py makemigrations general programa_tokenizador
python administrar.py migrate
./travis/reiniciar_apache.sh
systemctl status apache2
