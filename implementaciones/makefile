#
# Construcción de programa de pruebas de implementaciones.
# Proyecto Lovelace.
#

PROGRAMA_PRINCIPAL	:= programa_de_pruebas
PROGRAMA_DOS				:= lovelace
PRUEBA_DESEMP       := pruebas_desempenio
CARPETA_BINARIOS		:= binarios
CARPETA_OBJETOS			:= objetos
LISTA_DE_FUENTES		:= programa_de_pruebas.cpp \
											 acceso_a_datos/acceso_simulado.cpp \
											 acceso_a_datos/acceso_mysql.cpp \
											 acceso_a_datos/acceso_mysql_prueba.cpp \
											 redes_feistel/red_feistel_prueba.cpp \
											 redes_feistel/red_feistel_alternante_prueba.cpp \
											 redes_feistel/red_feistel_desbalanceada_prueba.cpp \
											 drbg/aleatoriedad_trivial.cpp \
											 drbg/aleatoriedad_trivial_prueba.cpp \
											 drbg/drbg.cpp \
											 drbg/hash_drbg.cpp \
											 drbg/hash_drbg_prueba.cpp \
											 drbg/ctr_drbg.cpp \
											 drbg/ctr_drbg_prueba.cpp \
											 ffx/combinacion_por_caracter_prueba.cpp \
											 ffx/combinacion_por_bloque_prueba.cpp \
											 ffx/ronda_ffx_a10_prueba.cpp \
											 ffx/ffx_a10_prueba.cpp \
											 tkr/pseudoaleatorio_trivial.cpp \
											 tkr/pseudoaleatorio_trivial_prueba.cpp \
											 tkr/pseudoaleatorio_aes.cpp \
											 tkr/pseudoaleatorio_aes_prueba.cpp \
											 tkr/funcion_rn.cpp \
											 tkr/funcion_rn_prueba.cpp \
											 tkr/tkr.cpp \
											 tkr/tkr_prueba.cpp \
											 aes_ensamblador/aes.cpp \
											 aes_ensamblador/aes_prueba.cpp \
											 aes_ensamblador/libaesni/libaes_lin64.o \
											 ahr/ahr.cpp \
											 ahr/ahr_prueba.cpp \
											 utilidades/utilidades_tarjetas.cpp \
											 utilidades/utilidades_tarjetas_prueba.cpp \
											 utilidades/utilidades_criptograficas.cpp \
											 utilidades/utilidades_criptograficas_prueba.cpp \
											 utilidades/algoritmo_tokenizador.cpp \
											 utilidades/algoritmo_tokenizador_reversible.cpp \
											 utilidades/algoritmo_tokenizador_irreversible.cpp \
											 utilidades/prueba.cpp \
											 utilidades/conjunto_de_pruebas.cpp \
											 utilidades/arreglo.cpp \
											 utilidades/arreglo_de_digitos.cpp \
											 utilidades/intermediario_de_arreglo_de_digitos.cpp
FUENTES_DOS					:= lovelace.cpp \
											 acceso_a_datos/acceso_mysql.cpp \
											 bps/cifrador_de_ronda.cpp \
                       bps/cifrador_BC.cpp \
											 bps/utilidades.cpp \
                       bps/cifrador_BPS.cpp \
											 bps/codificador.cpp \
											 drbg/aleatoriedad_trivial.cpp \
											 drbg/drbg.cpp \
											 drbg/hash_drbg.cpp \
											 tkr/pseudoaleatorio_trivial.cpp \
											 tkr/pseudoaleatorio_aes.cpp \
											 tkr/funcion_rn.cpp \
											 tkr/tkr.cpp \
											 aes_ensamblador/aes.cpp \
											 aes_ensamblador/libaesni/libaes_lin64.o \
											 ahr/ahr.cpp \
											 utilidades/utilidades_tarjetas.cpp \
											 utilidades/utilidades_criptograficas.cpp \
											 utilidades/algoritmo_tokenizador.cpp \
											 utilidades/algoritmo_tokenizador_reversible.cpp \
											 utilidades/algoritmo_tokenizador_irreversible.cpp \
											 utilidades/arreglo.cpp \
											 utilidades/arreglo_de_digitos.cpp \
											 utilidades/intermediario_de_arreglo_de_digitos.cpp \
											 utilidades/codificador.cpp
FUENTES_TRES        := pruebas_desempenio.cpp \
											 acceso_a_datos/acceso_mysql_pruebas.cpp \
											 acceso_a_datos/acceso_mysql.cpp \
											 bps/cifrador_de_ronda.cpp \
                       bps/cifrador_BC.cpp \
											 bps/utilidades.cpp \
                       bps/cifrador_BPS.cpp \
											 bps/codificador.cpp \
											 drbg/aleatoriedad_trivial.cpp \
											 drbg/drbg.cpp \
											 drbg/hash_drbg.cpp \
											 tkr/pseudoaleatorio_trivial.cpp \
											 tkr/pseudoaleatorio_aes.cpp \
											 tkr/funcion_rn.cpp \
											 tkr/tkr.cpp \
											 aes_ensamblador/aes.cpp \
											 aes_ensamblador/libaesni/libaes_lin64.o \
											 ahr/ahr.cpp \
											 utilidades/utilidades_tarjetas.cpp \
											 utilidades/utilidades_criptograficas.cpp \
											 utilidades/algoritmo_tokenizador.cpp \
											 utilidades/algoritmo_tokenizador_reversible.cpp \
											 utilidades/algoritmo_tokenizador_irreversible.cpp \
											 utilidades/arreglo.cpp \
											 utilidades/arreglo_de_digitos.cpp \
											 utilidades/intermediario_de_arreglo_de_digitos.cpp
LISTA_DE_OBJETOS		:= $(addprefix $(CARPETA_OBJETOS)/, \
												 $(LISTA_DE_FUENTES:.cpp=.o))
OBJETOS_DOS		      := $(addprefix $(CARPETA_OBJETOS)/, \
												 $(FUENTES_DOS:.cpp=.o))
OBJETOS_TRES        := $(addprefix $(CARPETA_OBJETOS)/, \
                         $(FUENTES_TRES:.cpp=.o))
BANDERAS_GENERALES	:= -std=c++14 -Wall -ggdb
BANDERAS_DE_LIGADO	:= -lcryptopp -lmysqlcppconn -lgmpxx -lgmp

$(CARPETA_BINARIOS)/$(PROGRAMA_PRINCIPAL): $(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	$(CXX) $(BANDERAS_GENERALES) $(LISTA_DE_OBJETOS) $(BANDERAS_DE_LIGADO) -o $@

$(CARPETA_BINARIOS)/$(PROGRAMA_DOS): $(OBJETOS_DOS)
	mkdir -p $(CARPETA_BINARIOS)
	$(CXX) $(BANDERAS_GENERALES) $(OBJETOS_DOS) $(BANDERAS_DE_LIGADO) -o $@

$(CARPETA_BINARIOS)/$(PRUEBA_DESEMP): $(OBJETOS_TRES)
	mkdir -p $(CARPETA_BINARIOS)
	$(CXX) $(BANDERAS_GENERALES) $(OBJETOS_TRES) $(BANDERAS_DE_LIGADO) -o $@

$(CARPETA_OBJETOS)/programa_de_pruebas.o: programa_de_pruebas.cpp
	mkdir -p $(CARPETA_OBJETOS)
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/lovelace.o: lovelace.cpp
	mkdir -p $(CARPETA_OBJETOS)
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/pruebas_desempenio.o: pruebas_desempenio.cpp
	mkdir -p $(CARPETA_OBJETOS)
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/redes_feistel/red_feistel_prueba.o: \
	redes_feistel/red_feistel_prueba.cpp redes_feistel/cabeceras/red_feistel.hh
	mkdir -p $(CARPETA_OBJETOS)/redes_feistel
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/redes_feistel/red_feistel_alternante_prueba.o: \
	redes_feistel/red_feistel_alternante_prueba.cpp \
	redes_feistel/cabeceras/red_feistel_alternante.hh
	mkdir -p $(CARPETA_OBJETOS)/redes_feistel
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/redes_feistel/red_feistel_desbalanceada_prueba.o: \
	redes_feistel/red_feistel_desbalanceada_prueba.cpp \
	redes_feistel/cabeceras/red_feistel_desbalanceada.hh
	mkdir -p $(CARPETA_OBJETOS)/redes_feistel
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ffx/combinacion_por_caracter_prueba.o: \
	ffx/combinacion_por_caracter_prueba.cpp \
	ffx/cabeceras/combinacion_por_caracter.hh
	mkdir -p $(CARPETA_OBJETOS)/ffx
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ffx/combinacion_por_bloque_prueba.o: \
	ffx/combinacion_por_bloque_prueba.cpp ffx/cabeceras/combinacion_por_bloque.hh
	mkdir -p $(CARPETA_OBJETOS)/ffx
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ffx/ronda_ffx_a10_prueba.o: ffx/ronda_ffx_a10_prueba.cpp \
	ffx/cabeceras/ronda_ffx_a10.hh
	mkdir -p $(CARPETA_OBJETOS)/ffx
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ffx/ffx_a10_prueba.o: ffx/ffx_a10_prueba.cpp \
	ffx/cabeceras/ffx_a10.hh
	mkdir -p $(CARPETA_OBJETOS)/ffx
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/utilidades_tarjetas.o: \
	utilidades/utilidades_tarjetas.cpp \
	utilidades/cabeceras/utilidades_tarjetas.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/utilidades_tarjetas_prueba.o: \
	utilidades/utilidades_tarjetas_prueba.cpp \
	utilidades/cabeceras/utilidades_tarjetas_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/utilidades_criptograficas.o: \
	utilidades/utilidades_criptograficas.cpp \
	utilidades/cabeceras/utilidades_criptograficas.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/utilidades_criptograficas_prueba.o: \
	utilidades/utilidades_criptograficas_prueba.cpp \
	utilidades/cabeceras/utilidades_criptograficas_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/algoritmo_tokenizador.o: \
	utilidades/algoritmo_tokenizador.cpp \
	utilidades/cabeceras/algoritmo_tokenizador.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/algoritmo_tokenizador_reversible.o: \
	utilidades/algoritmo_tokenizador_reversible.cpp \
	utilidades/cabeceras/algoritmo_tokenizador_reversible.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/algoritmo_tokenizador_irreversible.o: \
	utilidades/algoritmo_tokenizador_irreversible.cpp \
	utilidades/cabeceras/algoritmo_tokenizador_irreversible.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/pseudoaleatorio_trivial.o: \
	tkr/pseudoaleatorio_trivial.cpp \
	tkr/cabeceras/pseudoaleatorio_trivial.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/pseudoaleatorio_trivial_prueba.o: \
	tkr/pseudoaleatorio_trivial_prueba.cpp \
	tkr/cabeceras/pseudoaleatorio_trivial_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/pseudoaleatorio_aes.o: \
	tkr/pseudoaleatorio_aes.cpp \
	tkr/cabeceras/pseudoaleatorio_aes.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/pseudoaleatorio_aes_prueba.o: \
	tkr/pseudoaleatorio_aes_prueba.cpp \
	tkr/cabeceras/pseudoaleatorio_aes_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/funcion_rn.o: \
	tkr/funcion_rn.cpp \
	tkr/cabeceras/funcion_rn.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/funcion_rn_prueba.o: \
	tkr/funcion_rn_prueba.cpp \
	tkr/cabeceras/funcion_rn_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/tkr.o: tkr/tkr.cpp tkr/cabeceras/tkr.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/tkr/tkr_prueba.o: tkr/tkr_prueba.cpp \
	tkr/cabeceras/tkr_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/tkr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/aes_ensamblador/aes.o: aes_ensamblador/aes.cpp \
	aes_ensamblador/cabeceras/aes.hh
	mkdir -p $(CARPETA_OBJETOS)/aes_ensamblador
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/aes_ensamblador/aes_prueba.o: aes_ensamblador/aes_prueba.cpp \
	aes_ensamblador/cabeceras/aes_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/aes_ensamblador
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/aes_ensamblador/libaesni/libaes_lin64.o: \
	aes_ensamblador/libaesni/iaes_asm_interface.h \
	aes_ensamblador/libaesni/iaesni.h \
	aes_ensamblador/libaesni/intel_aes.c
	mkdir -p $(CARPETA_OBJETOS)/aes_ensamblador/libaesni
	yasm -D__linux__ -f elf64 aes_ensamblador/libaesni/asm/iaesx64.s  -o \
		$(CARPETA_OBJETOS)/aes_ensamblador/libaesni/iaesx64.o
	yasm -D__linux__ -f elf64 aes_ensamblador/libaesni/asm/do_rdtsc.s -o \
		$(CARPETA_OBJETOS)/aes_ensamblador/libaesni/do_rdtsc.o
	gcc -Wall -fPIC -c aes_ensamblador/libaesni/intel_aes.c -o \
		$(CARPETA_OBJETOS)/aes_ensamblador/libaesni/intel_aes.o
	gcc -shared -o $@ $(CARPETA_OBJETOS)/aes_ensamblador/libaesni/*.o

$(CARPETA_OBJETOS)/ahr/ahr.o: ahr/ahr.cpp ahr/cabeceras/ahr.hh
	mkdir -p $(CARPETA_OBJETOS)/ahr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/ahr/ahr_prueba.o: ahr/ahr_prueba.cpp \
	ahr/cabeceras/ahr_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/ahr
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/acceso_a_datos/acceso_simulado.o: \
	acceso_a_datos/acceso_simulado.cpp \
	acceso_a_datos/cabeceras/acceso_simulado.hh
	mkdir -p $(CARPETA_OBJETOS)/acceso_a_datos
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/acceso_a_datos/acceso_mysql.o: \
	acceso_a_datos/acceso_mysql.cpp acceso_a_datos/cabeceras/acceso_mysql.hh
	mkdir -p $(CARPETA_OBJETOS)/acceso_a_datos
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/acceso_a_datos/acceso_mysql_pruebas.o: \
	acceso_a_datos/acceso_mysql_pruebas.cpp \
	acceso_a_datos/cabeceras/acceso_mysql_pruebas.hh
	mkdir -p $(CARPETA_OBJETOS)/acceso_a_datos
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/acceso_a_datos/acceso_mysql_prueba.o: \
	acceso_a_datos/acceso_mysql_prueba.cpp \
	acceso_a_datos/cabeceras/acceso_mysql_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/acceso_a_datos
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/drbg/aleatoriedad_trivial.o: \
	drbg/aleatoriedad_trivial.cpp drbg/cabeceras/aleatoriedad_trivial.hh
	mkdir -p $(CARPETA_OBJETOS)/drbg
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/drbg/aleatoriedad_trivial_prueba.o: \
	drbg/aleatoriedad_trivial_prueba.cpp \
	drbg/cabeceras/aleatoriedad_trivial_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/drbg
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/drbg/drbg.o: \
	drbg/drbg.cpp drbg/cabeceras/drbg.hh
	mkdir -p $(CARPETA_OBJETOS)/drbg
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/drbg/hash_drbg.o: \
	drbg/hash_drbg.cpp drbg/cabeceras/hash_drbg.hh
	mkdir -p $(CARPETA_OBJETOS)/drbg
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/drbg/hash_drbg_prueba.o: \
	drbg/hash_drbg_prueba.cpp drbg/cabeceras/hash_drbg_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/drbg
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/drbg/ctr_drbg.o: \
	drbg/ctr_drbg.cpp drbg/cabeceras/ctr_drbg.hh
	mkdir -p $(CARPETA_OBJETOS)/drbg
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/drbg/ctr_drbg_prueba.o: \
	drbg/ctr_drbg_prueba.cpp drbg/cabeceras/ctr_drbg_prueba.hh
	mkdir -p $(CARPETA_OBJETOS)/drbg
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/bps/cifrador_de_ronda.o: bps/cifrador_de_ronda.cpp \
	bps/cabeceras/cifrador_de_ronda.hh
	mkdir -p $(CARPETA_OBJETOS)/bps
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/bps/cifrador_BC.o: bps/cifrador_BC.cpp \
	bps/cabeceras/cifrador_BC.hh
	mkdir -p $(CARPETA_OBJETOS)/bps
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/bps/utilidades.o: bps/utilidades.cpp \
	bps/cabeceras/utilidades.hh
	mkdir -p $(CARPETA_OBJETOS)/bps
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/bps/cifrador_BPS.o: bps/cifrador_BPS.cpp \
	bps/cabeceras/cifrador_BPS.hh
	mkdir -p $(CARPETA_OBJETOS)/bps
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/bps/codificador.o: bps/codificador.cpp \
	bps/cabeceras/codificador.hh
	mkdir -p $(CARPETA_OBJETOS)/bps
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/prueba.o: ../utilidades/prueba.cpp
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/conjunto_de_pruebas.o: \
	../utilidades/conjunto_de_pruebas.cpp
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/arreglo_de_digitos.o: \
	../utilidades/arreglo_de_digitos.cpp \
	../utilidades/cabeceras/arreglo_de_digitos.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/arreglo.o: \
	../utilidades/arreglo.cpp \
	../utilidades/cabeceras/arreglo.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/intermediario_de_arreglo_de_digitos.o: \
	../utilidades/intermediario_de_arreglo_de_digitos.cpp \
	../utilidades/cabeceras/intermediario_de_arreglo_de_digitos.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/utilidades/codificador.o: \
	../utilidades/codificador.cpp \
	../utilidades/cabeceras/codificador.hh
	mkdir -p $(CARPETA_OBJETOS)/utilidades
	$(CXX) $(BANDERAS_GENERALES) -c $< -o $@

correr: $(CARPETA_BINARIOS)/$(PROGRAMA_PRINCIPAL)
	./$<

limpiar:
	rm -Rvf $(CARPETA_BINARIOS) $(CARPETA_OBJETOS)
