cbc_prueba: prueba_cbc.cpp e_cbc.o e_aes.o
	g++ -std=c++11 -c prueba_cbc.cpp -o binarios/prueba_cbc.o
	g++ -o binarios/prueba_cbc.out binarios/*.o libaesni/*.o

aes_prueba: prueba_aes.cpp e_aes.o
	g++ -c prueba_aes.cpp -o binarios/prueba_aes.o
	g++ -o binarios/prueba_aes.out binarios/*.o libaesni/*.o 

e_cbc.o: cbc.cpp cabeceras/cbc.hh
	mkdir -p binarios
	g++ -std=c++11 -c cbc.cpp -o binarios/cbc.o

e_aes.o: aes.cpp cabeceras/aes.hh
	mkdir -p binarios
	g++ -std=c++11 -c aes.cpp -o binarios/aes.o

limpiar:
	rm binarios/*.o &
	rm binarios/*.out