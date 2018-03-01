prueba: prueba_cbc.cpp cbcmac.o
	g++ -c prueba_cbc.cpp -o binarios/prueba_cbc.o
	g++ -o binarios/prueba.out binarios/*.o libaesni/*.o

cbcmac.o: cbcmac.cpp cabeceras/cbcmac.h
	mkdir -p binarios
	g++ -c cbcmac.cpp -o binarios/cbcmac.o

limpiar:
	rm binarios/*.o &
	rm binarios/*.out