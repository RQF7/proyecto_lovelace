/**
 *
 */

#include <fcntl.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main(int numeroDArgumentos, char **argumentos)
{
  char *nombre = "/tmp/lovelace";
  mkfifo(nombre, 0666);
  int descriptorDeArchivo = open(nombre, O_RDONLY);
  char buffer[1024];
  while (true)
    if(read(descriptorDeArchivo, buffer, 1024) > 0)
    {
      string cadenaRecibida{buffer};
      cout << cadenaRecibida << endl;
      memset(buffer, 0, 1024);
    }
  close(descriptorDeArchivo);
  unlink(nombre);
  return 0;
}
