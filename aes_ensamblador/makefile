#
# Construcción de programas en ensamblador.
# Proyecto Lovelace.
#

binarios/prueba: objetos/prueba.o
	mkdir -p binarios
	ld -o $@ $<

objetos/prueba.o: prueba.asm
	mkdir -p objetos
	nasm -f elf64 -o $@ $<
