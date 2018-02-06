#
# Construcción de programa de pruebas de librerías.
# Proyecto Lovelace.
#

PROGRAMA_PRINCIPAL	:= programa_de_pruebas
CARPETA_BINARIOS		:= binarios
CARPETA_OBJETOS			:= objetos
LISTA_DE_FUENTES		:= programa_de_pruebas.cpp \
											 utilidades/prueba.cpp \
											 cryptopp/prueba_AES.cpp
LISTA_DE_OBJETOS		:= $(addprefix $(CARPETA_OBJETOS)/, \
												 $(LISTA_DE_FUENTES:.cpp=.o))

$(CARPETA_BINARIOS)/$(PROGRAMA_PRINCIPAL): $(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	g++ -lcryptopp $(LISTA_DE_OBJETOS) -o $@

$(CARPETA_OBJETOS)/programa_de_pruebas.o: programa_de_pruebas.cpp
	mkdir -p $(CARPETA_OBJETOS)
	g++ -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/prueba.o: utilidades/prueba.cpp
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	g++ -c $< -o $@

$(CARPETA_OBJETOS)/cryptopp/prueba_AES.o: cryptopp/prueba_AES.cpp
	mkdir -p $(CARPETA_OBJETOS)/cryptopp
	g++ -c $< -o $@

correr: $(CARPETA_BINARIOS)/$(PROGRAMA_PRINCIPAL)
	./$<

limpiar:
	rm -Rvf $(CARPETA_BINARIOS) $(CARPETA_OBJETOS)
