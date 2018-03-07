#
# Construcción de programa de pruebas de librerías.
# Proyecto Lovelace.
#

PROGRAMA_PRINCIPAL	:= programa_de_pruebas
CARPETA_BINARIOS		:= binarios
CARPETA_OBJETOS			:= objetos
LISTA_DE_FUENTES		:= programa_de_pruebas.cpp \
											 arreglo_prueba.cpp \
											 red_feistel_prueba.cpp \
											 red_feistel_alternante_prueba.cpp \
											 red_feistel_desbalanceada_prueba.cpp \
											 combinacion_por_caracter_prueba.cpp \
											 combinacion_por_bloque_prueba.cpp \
											 utilidades/prueba.cpp
LISTA_DE_OBJETOS		:= $(addprefix $(CARPETA_OBJETOS)/, \
												 $(LISTA_DE_FUENTES:.cpp=.o))
BANDERAS_GENERALES	:= -std=c++11 -Wall -ggdb

$(CARPETA_BINARIOS)/$(PROGRAMA_PRINCIPAL): $(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS_GENERALES) $(LISTA_DE_OBJETOS) -o $@

$(CARPETA_OBJETOS)/programa_de_pruebas.o: programa_de_pruebas.cpp
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/arreglo_prueba.o: arreglo_prueba.cpp cabeceras/arreglo.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/red_feistel_prueba.o: red_feistel_prueba.cpp \
	cabeceras/red_feistel.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/red_feistel_alternante_prueba.o: \
	red_feistel_alternante_prueba.cpp cabeceras/red_feistel_alternante.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/red_feistel_desbalanceada_prueba.o: \
	red_feistel_desbalanceada_prueba.cpp cabeceras/red_feistel_desbalanceada.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/combinacion_por_caracter_prueba.o: \
	combinacion_por_caracter_prueba.cpp cabeceras/combinacion_por_caracter.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/combinacion_por_bloque_prueba.o: \
	combinacion_por_bloque_prueba.cpp cabeceras/combinacion_por_bloque.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ffx_prueba.o: ffx_prueba.cpp cabeceras/ffx.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/prueba.o: ../../utilidades/prueba.cpp
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	g++ $(BANDERAS_GENERALES) -c $< -o $@

correr: $(CARPETA_BINARIOS)/$(PROGRAMA_PRINCIPAL)
	./$<

limpiar:
	rm -Rvf $(CARPETA_BINARIOS) $(CARPETA_OBJETOS)
