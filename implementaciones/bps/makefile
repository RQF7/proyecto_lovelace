#
# Construcción de programa de pruebas de BPS.
# Proyecto Lovelace.
#

CARPETA_BINARIOS    := binarios
CARPETA_OBJETOS			:= objetos
BANDERAS            := -std=c++11 -Wall -ggdb

# ¿Librerías? ¿Por qué "librerías"?
LIBRERIAS           := utilidades.cpp \
                       codificador.cpp \
                       cifrador_de_ronda.cpp \
                       cifrador_BC.cpp \
                       cifrador_BPS.cpp
LISTA_DE_OBJETOS		:= $(addprefix $(CARPETA_OBJETOS)/, \
												 $(LIBRERIAS:.cpp=.o))

BPS_Imp: $(CARPETA_OBJETOS)/BPS_Imp.o $(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LISTA_DE_OBJETOS) $< -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_BPS: $(CARPETA_OBJETOS)/prueba_BPS.o $(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LISTA_DE_OBJETOS) $< -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_cifrador_BC: $(CARPETA_OBJETOS)/prueba_cifrador_BC.o $(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LISTA_DE_OBJETOS) $< \
	-o $(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_cifrador_de_ronda: $(CARPETA_OBJETOS)/prueba_cifrador_de_ronda.o \
	$(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LISTA_DE_OBJETOS) $< -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_codificador: $(CARPETA_OBJETOS)/prueba_codificador.o $(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LISTA_DE_OBJETOS) $< -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_utilidades: $(CARPETA_OBJETOS)/prueba_utilidades.o $(LISTA_DE_OBJETOS)
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LISTA_DE_OBJETOS) $< -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

correr_BPS_Imp: $(CARPETA_BINARIOS)/BPS_Imp
	$(CARPETA_BINARIOS)/BPS_Imp ${ARGS}

correr_prueba_BPS: $(CARPETA_BINARIOS)/prueba_BPS
	$(CARPETA_BINARIOS)/prueba_BPS

correr_prueba_cifrador_BC: $(CARPETA_BINARIOS)/prueba_cifrador_BC
	$(CARPETA_BINARIOS)/prueba_cifrador_BC

correr_prueba_cifrador_de_ronda: $(CARPETA_BINARIOS)/prueba_cifrador_de_ronda
	$(CARPETA_BINARIOS)/prueba_cifrador_de_ronda

correr_prueba_codificador: $(CARPETA_BINARIOS)/prueba_codificador
	$(CARPETA_BINARIOS)/prueba_codificador

correr_prueba_utilidades: $(CARPETA_BINARIOS)/prueba_utilidades
	$(CARPETA_BINARIOS)/prueba_utilidades

$(CARPETA_OBJETOS)/utilidades.o: utilidades.cpp cabeceras/utilidades.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/codificador.o: codificador.cpp cabeceras/codificador.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/cifrador_de_ronda.o: cifrador_de_ronda.cpp \
	cabeceras/cifrador_de_ronda.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/cifrador_BC.o: cifrador_BC.cpp \
	cabeceras/cifrador_BC.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/cifrador_BPS.o: cifrador_BPS.cpp \
	cabeceras/cifrador_BPS.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/BPS_Imp.o: BPS_Imp.cpp \
	cabeceras/cifrador_BPS.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/prueba_BPS.o: prueba_BPS.cpp \
	cabeceras/cifrador_BPS.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/prueba_cifrador_BC.o: prueba_cifrador_BC.cpp \
	cabeceras/cifrador_BPS.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/prueba_cifrador_de_ronda.o: prueba_cifrador_de_ronda.cpp \
	cabeceras/cifrador_BPS.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/prueba_codificador.o: prueba_codificador.cpp \
	cabeceras/cifrador_BPS.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

$(CARPETA_OBJETOS)/prueba_utilidades.o: prueba_utilidades.cpp \
	cabeceras/cifrador_BPS.hh
	mkdir -p $(CARPETA_OBJETOS)
	g++ $(BANDERAS_GENERALES) -c $< -o $@

limpiar:
	rm -Rvf $(CARPETA_BINARIOS) $(CARPETA_OBJETOS)
