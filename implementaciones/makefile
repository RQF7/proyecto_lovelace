#
# Construcción de programa de pruebas de implementaciones.
# Proyecto Lovelace.
#

PROGRAMA_PRINCIPAL	:= programa_de_pruebas
CARPETA_BINARIOS		:= binarios
CARPETA_OBJETOS			:= objetos
LISTA_DE_FUENTES		:= programa_de_pruebas.cpp \
											 redes_feistel/red_feistel_prueba.cpp \
											 redes_feistel/red_feistel_alternante_prueba.cpp \
											 redes_feistel/red_feistel_desbalanceada_prueba.cpp \
											 ffx/combinacion_por_caracter_prueba.cpp \
											 ffx/combinacion_por_bloque_prueba.cpp \
											 ffx/ronda_ffx_a10_prueba.cpp \
											 ffx/ffx_a10_prueba.cpp \
											 utilidades/utilidades_tarjetas.cpp \
											 utilidades/utilidades_tarjetas_prueba.cpp \
											 utilidades/algoritmo_tokenizador.cpp \
											 tkr/pseudoaleatorio_trivial.cpp \
											 tkr/pseudoaleatorio_trivial_prueba.cpp \
											 tkr/pseudoaleatorio_aes.cpp \
											 tkr/pseudoaleatorio_aes_prueba.cpp \
											 tkr/funcion_rn.cpp \
											 tkr/funcion_rn_prueba.cpp \
											 tkr/tkr.cpp \
											 tkr/tkr_prueba.cpp \
											 acceso_a_datos/acceso_simulado.cpp \
											 utilidades/prueba.cpp
LISTA_DE_OBJETOS		:= $(addprefix $(CARPETA_OBJETOS)/, \
												 $(LISTA_DE_FUENTES:.cpp=.o))
BANDERAS_GENERALES	:= -std=c++11 -Wall -ggdb
BANDERAS_DE_LIGADO	:= -lcryptopp

$(CARPETA_BINARIOS)/$(PROGRAMA_PRINCIPAL): $(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS_GENERALES) $(LISTA_DE_OBJETOS) $(BANDERAS_DE_LIGADO) -o $@

$(CARPETA_OBJETOS)/programa_de_pruebas.o: programa_de_pruebas.cpp
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/redes_feistel/red_feistel_prueba.o: \
	redes_feistel/red_feistel_prueba.cpp redes_feistel/cabeceras/red_feistel.hh
	mkdir -p $(CARPETA_OBJETOS)/redes_feistel
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/redes_feistel/red_feistel_alternante_prueba.o: \
	redes_feistel/red_feistel_alternante_prueba.cpp \
	redes_feistel/cabeceras/red_feistel_alternante.hh
	mkdir -p $(CARPETA_OBJETOS)/redes_feistel
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/redes_feistel/red_feistel_desbalanceada_prueba.o: \
	redes_feistel/red_feistel_desbalanceada_prueba.cpp \
	redes_feistel/cabeceras/red_feistel_desbalanceada.hh
	mkdir -p $(CARPETA_OBJETOS)/redes_feistel
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ffx/combinacion_por_caracter_prueba.o: \
	ffx/combinacion_por_caracter_prueba.cpp \
	ffx/cabeceras/combinacion_por_caracter.hh
	mkdir -p $(CARPETA_OBJETOS)/ffx
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ffx/combinacion_por_bloque_prueba.o: \
	ffx/combinacion_por_bloque_prueba.cpp ffx/cabeceras/combinacion_por_bloque.hh
	mkdir -p $(CARPETA_OBJETOS)/ffx
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ffx/ronda_ffx_a10_prueba.o: ffx/ronda_ffx_a10_prueba.cpp \
	ffx/cabeceras/ronda_ffx_a10.hh
	mkdir -p $(CARPETA_OBJETOS)/ffx
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ffx/ffx_a10_prueba.o: ffx/ffx_a10_prueba.cpp \
	ffx/cabeceras/ffx_a10.hh
	mkdir -p $(CARPETA_OBJETOS)/ffx
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/utilidades_tarjetas.o: \
	utilidades/utilidades_tarjetas.cpp \
	utilidades/cabeceras/utilidades_tarjetas.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/utilidades_tarjetas_prueba.o: \
	utilidades/utilidades_tarjetas_prueba.cpp \
	utilidades/cabeceras/utilidades_tarjetas_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/algoritmo_tokenizador.o: \
	utilidades/algoritmo_tokenizador.cpp \
	utilidades/cabeceras/algoritmo_tokenizador.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/pseudoaleatorio_trivial.o: \
	tkr/pseudoaleatorio_trivial.cpp \
	tkr/cabeceras/pseudoaleatorio_trivial.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/pseudoaleatorio_trivial_prueba.o: \
	tkr/pseudoaleatorio_trivial_prueba.cpp \
	tkr/cabeceras/pseudoaleatorio_trivial_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/pseudoaleatorio_aes.o: \
	tkr/pseudoaleatorio_aes.cpp \
	tkr/cabeceras/pseudoaleatorio_aes.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/pseudoaleatorio_aes_prueba.o: \
	tkr/pseudoaleatorio_aes_prueba.cpp \
	tkr/cabeceras/pseudoaleatorio_aes_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/funcion_rn.o: \
	tkr/funcion_rn.cpp \
	tkr/cabeceras/funcion_rn.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/funcion_rn_prueba.o: \
	tkr/funcion_rn_prueba.cpp \
	tkr/cabeceras/funcion_rn_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/tkr.o: tkr/tkr.cpp tkr/cabeceras/tkr.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/tkr_prueba.o: tkr/tkr_prueba.cpp \
	tkr/cabeceras/tkr_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/acceso_a_datos/acceso_simulado.o: \
	acceso_a_datos/acceso_simulado.cpp \
	acceso_a_datos/cabeceras/acceso_simulado.hh
	mkdir -p $(CARPETA_OBJETOS)/acceso_a_datos
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/prueba.o: ../utilidades/prueba.cpp
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	g++ $(BANDERAS_GENERALES) -c $< -o $@

correr: $(CARPETA_BINARIOS)/$(PROGRAMA_PRINCIPAL)
	./$<

limpiar:
	rm -Rvf $(CARPETA_BINARIOS) $(CARPETA_OBJETOS)
