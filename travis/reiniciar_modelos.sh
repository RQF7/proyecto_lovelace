#!/usr/bin/sh

#
# Script para reiniciar el estado de los modelos en django.
#
# Proyecto Lovelace.
#

cd bases_de_datos
./reiniciar_base.sh $1
cd ..
rm -Rfv sistema_tokenizador/general/migrations \
  sistema_tokenizador/programa_tokenizador/migrations
python administrar_sistema_tokenizador.py makemigrations general programa_tokenizador
python administrar_sistema_tokenizador.py migrate
python bases_de_datos/datos_base.py
python bases_de_datos/datos_de_prueba.py
