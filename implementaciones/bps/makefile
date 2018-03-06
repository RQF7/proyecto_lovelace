
CARPETA_BINARIOS    := binarios
BANDERAS            := -std=c++11 -Wall -ggdb
LIBRERIAS           := utilidades.cpp \
                       codificador.cpp \
                       cifrador_de_ronda.cpp \
                       cifrador_BC.cpp \
                       cifrador_BPS.cpp

BPS_Imp: BPS_Imp.cpp
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LIBRERIAS) BPS_Imp.cpp -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_BPS: prueba_BPS.cpp
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LIBRERIAS) prueba_BPS.cpp -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_cifrador_BC: prueba_cifrador_BC.cpp
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LIBRERIAS) prueba_cifrador_BC.cpp -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_cifrador_de_ronda: prueba_cifrador_de_ronda.cpp
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LIBRERIAS) prueba_cifrador_de_ronda.cpp -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_codificador: prueba_codificador.cpp
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LIBRERIAS) prueba_codificador.cpp -o \
	$(CARPETA_BINARIOS)/$@ -lcryptopp -lgmpxx -lgmp

prueba_utilidades: prueba_utilidades.cpp
	mkdir -p $(CARPETA_BINARIOS)
	g++ $(BANDERAS) $(LIBRERIAS) prueba_utilidades.cpp -o \
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

limpiar:
	rm -Rvf $(CARPETA_BINARIOS)
