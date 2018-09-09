#!/usr/bin/expect -f

#
# Script de expect (interactivo) para reiniciar apache
# en droplet de digital ocean.
#

set contrasenia [lindex $argv 0];
set timeout -1

spawn systemctl restart apache2
expect "Password: "
send -- $contrasenia
send -- "\n"
expect eof
