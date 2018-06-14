/**
 * \file
 * \brief Prueba de implementaciones de entropía en hardware.
 *
 * La que debe de funcionar es «rdseed»; en mi laptop no está implementada.
 * Compilar con la bandera «-march=native».
 */

#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
  printf("Hola mundo!\n");
  uint32_t *semilla = malloc(sizeof(uint32_t) * 16);
  int estado = _rdrand32_step(semilla);
  //int estado = _rdseed32_step(semilla);
  printf("Estado: %d\n", estado);
  free(semilla);
  return 0;
}
