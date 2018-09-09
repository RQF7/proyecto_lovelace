#!/usr/bin/expect -f

#
# Script de expect (interactivo) para hacer pull desde
# digital ocean.
#

set contrasenia [lindex $argv 0];
set timeout -1

spawn git pull
expect "Username for 'https://github.com': "
send -- "RQF7\n"
expect "Password for 'https://RQF7@github.com': "
send -- $contrasenia
send -- "\n"
expect eof
