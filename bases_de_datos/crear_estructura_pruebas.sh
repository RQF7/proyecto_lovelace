#!/bin/bash

#
# Script para crear la estructura de la base de pruebas.
# No necesita permisos de administrador.
#
# Proyecto Lovelace.
#

USUARIO='administrador_lovelace_pruebas'
CONTRASENIA='l0v3lac3-padmin'

mysql -u $USUARIO -p$CONTRASENIA lovelace_pruebas < crear_estructura_pruebas.sql
mysql -u $USUARIO -p$CONTRASENIA lovelace_pruebas < poblar_pruebas.sql
