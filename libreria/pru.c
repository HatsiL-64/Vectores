#include <stdio.h>
#include <stdlib.h>
#include "funjs.h"

int main(void)
{
  char *respuesta = NULL, **palabras;
  int nPalabras;
  printf("Dame una cadena: ");
  respuesta = scani();
  printf("Cadena:%s", respuesta);
  printf("Trim:%s", respuesta);
  printf("Digito: %s", digito(respuesta) ? "si" : "no");
  printf("split:");
  for(int i = 0; i < nPalabras; i++)
    printf("%i-%s\t", i + 1, palabras[i]);
  free(respuesta);
  free(palabras);
  return 0;
}
