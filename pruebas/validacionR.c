#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
  char* str = malloc(sizeof(char));
  int n = 0;

  printf("Dame una cadena de texto: ");
  while ((str[n] = getchar()) != '\n' && str[n] != EOF) 
  {
    n++;
    char* temp = realloc(str, n + 1);
    if(temp == NULL)
    {
      free(str);
      return 1;
    }
    str = temp;
  }
  str[n] = '\0';
  printf("La cadena cuenta con %i caracteres \nLo que escribiste fue: ", n);
  printf("%s", str);

  printf("\n");
  free(str);
  return 0;
}
