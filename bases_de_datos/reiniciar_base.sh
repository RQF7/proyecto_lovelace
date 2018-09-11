#!/usr/bin/expect -f

#
# Script para reiniciar el estado de la base de datos.
#
# Borra la base anterior y crea una nueva.
#
# Proyecto Lovelace.
#

set contrasenia [lindex $argv 0];
set timeout -1

spawn mysql -u root -p lovelace_cdv -e "drop database lovelace_cdv"
expect "Enter password: "
send -- $contrasenia
send -- "\n"
expect eof

spawn mysql -u root -p -e "source crear_base.sql"
expect "Enter password: "
send -- $contrasenia
send -- "\n"
expect eof
