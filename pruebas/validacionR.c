#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double magnitud;
  double angulo;
  double* comp;
  int dimensiones;
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
  if(array[0] == NULL)
    return NULL;
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

bool digito(char str[])
{
  int n = 0;
  while (str[n] != '\0') {
    if((str[n] >= 48 && str[n] <= 57) || str[n] == 46)
      n++;
    else 
      return false;
  }
  return true;
}

void validaCrea(char str[], vector** vec)
{
  int n = 0;
  char** componentes = NULL;
  static int vez = 1, dUnica;
  if(vez == 1)
  {
    componentes = split(str, " ", &dUnica);
  }
  else
  {
    int dimensiones;
    componentes = split(str, " ", &dimensiones);
    if(dimensiones != dUnica)
    {
      printf("La cantidad de dimensiones difieren entre los vectores\n");
      return;
    }
  }
  if(componentes == NULL)
  {
    printf("Entrada invalida\n");
    return;
  }

  *vec = realloc(*vec, sizeof(vector) * vez);
  (*vec)[vez - 1].comp = realloc((*vec)[vez - 1].comp, sizeof(double) * dUnica);
  (*vec)[vez - 1].dimensiones = dUnica;
  for(int i = 0; i < dUnica; i++)
  {
    if(!digito(componentes[i]) )
    {
      printf("Caracteres Invalidos\n");
      return;
    }
  }
  for(int i = 0; i < dUnica; i++)
  {
    (*vec)[vez - 1].comp[i] = atof(componentes[i]);
  }
  vez++;
  free(componentes);
}

int main ()
{
  int n = 0;
  char* respuesta = NULL;
  vector* vectores = NULL;

  printf("Dame los componentes de un vector");
  respuesta = trim(scani());
  validaCrea(respuesta, &vectores);
  printf("Tu vector tiene componentes:\n");
  for (int i = 0; i <  vectores[0].dimensiones; i++) {
    printf("%0.3f\t", vectores->comp[i]);
  }
  
  printf("\n");
  free(respuesta);
  free(vectores->comp);
  free(vectores);
  return 0;
}
