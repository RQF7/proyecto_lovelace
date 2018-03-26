ahr_prueba: ahr_pruebas.cpp e_ahr.o e_aes.o
	g++ -std=c++11 ahr_pruebas.cpp binarios/*.o ../aes_ensamblador/libaesni/*.o ../objetos/*/*.o -o binarios/prueba_ahr.out -lcryptopp -lmysqlcppconn

e_ahr.o: ahr.cpp cabeceras/ahr.hh
	mkdir -p binarios
	g++ -std=c++11 -c ahr.cpp -o binarios/ahr.o -lcryptopp

e_aes.o: ../aes_ensamblador/aes.cpp ../aes_ensamblador/cabeceras/aes.hh
	mkdir -p binarios
	g++ -std=c++11 -c ../aes_ensamblador/aes.cpp -o binarios/aes.o

limpiar:
	rm binarios/*.o &
	rm binarios/*.out
