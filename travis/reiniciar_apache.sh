#!/usr/bin/expect -f

#
# Script de expect (interactivo) para reiniciar apache
# en droplet de digital ocean.
#

set timeout -1

spawn sudo systemctl restart apache2
expect "[sudo] password for ricardo: "
send -- $CONTRASENIA_SERVIDOR
send -- "\n"
expect eof
