#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double magnitud;
  double angulo;
  double* comp;
} vector;

// La funcion scani() sirve para crear cadenas de texto dinamicas de esta forma evitas tener problemas
// por falta de espacio en el arreglo. Es importante usar esta funcion con un char* y liberar este puntero
// al final del main    Requiere de stdio y stdlib
char* scani()
{
  char* str = malloc(sizeof(char));
  int n = 0;
  while((str[n] = getchar()) != '\n' && str[n] != EOF){
    n++;
    char* temp = realloc(str, n + 1);
    if(temp == NULL){
      free(str);
      printf("\nError de memoria");
      return NULL;
    }
    str = temp;
  }
  str[n] = '\0';
  return str;
}

//Funcion split. Por el momento usar strtok. Mejorar despues
//
char** split(char str[], char lim[], int *nPalabras)
{
  char** array = malloc(sizeof(char*) * 2);
  *nPalabras = 1;

  array[0] = strtok(str, lim);
  while ((array[*nPalabras] = strtok(NULL, lim)) != NULL) {
    (*nPalabras)++;
    array = realloc(array, sizeof(char*) * (*nPalabras + 1));
  }
  return array;
}

//Funcion trim 
//
char* trim(char* str)
{
  if(str == NULL)
    return NULL;

  int fin = 0, inicio = 0, len = 0;
  
  while(str[len] != '\0')
    len++;
  while(str[inicio] == ' ' || str[inicio] == '\t')
    inicio++;
  fin = len - 1;
  while (str[fin] == ' ' || str[fin] == '\t') 
    fin--;

  char* nstr = malloc(sizeof(char) * (fin - inicio + 2));
  if(nstr == NULL)
    return NULL;

  for(int i = 0; i < fin - inicio + 1; i++)
    nstr[i] = str[inicio + i];

  nstr[fin - inicio + 1] = '\0';
  return nstr;
}
void asignarComp(char str[], vector** vec)
{
  //char* token;
  //strtok(str, *vec.comp[1]);
}

int main ()
{
  int n = 0, nPalabras;
  char* respuesta = NULL;
  char** palabras = NULL;
  vector* vectores = malloc(sizeof(vector));

  printf("Dame una cadena de texto: ");
  respuesta = trim(scani());
  palabras = split(respuesta, " ", &nPalabras);

  printf("\n");
  free(palabras);
  free(respuesta);
  free(vectores->comp);
  free(vectores);
  return 0;
}
