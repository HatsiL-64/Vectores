#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

//Esta funcion basicamente te hace toda la entrada en la suma de componentes. Solo requiere el array con los vectores y la str de donde sacar los datos.
//Ya incluye la validacion y creacion de los vectores. Solo llamala despues de recibir una cadena con scani
bool sumaCompEntrada(char str[], vector** vec)
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
      return false;
    }
  }
  if(componentes == NULL)
  {
    printf("Entrada invalida\n");
    return false;
  }

  *vec = realloc(*vec, sizeof(vector) * vez);
  (*vec)[vez - 1].comp = realloc((*vec)[vez - 1].comp, sizeof(double) * dUnica);
  (*vec)[vez - 1].dimensiones = dUnica;
  for(int i = 0; i < dUnica; i++)
  {
    if(!digito(componentes[i]) )
    {
      printf("Caracteres Invalidos\n");
      return false;
    }
  }
  for(int i = 0; i < dUnica; i++)
  {
    (*vec)[vez - 1].comp[i] = atof(componentes[i]);
  }

  vez++;
  free(componentes);
  return true;
}

int main ()
{
  int cont, ceros;
  bool salir;
  char opcion, *respuesta = NULL;
  vector* vectores = NULL;

  printf("Hola este programa tiene como objetivo facilitar ciertas operaciones con vectores y calculos con matrices. Estas son las opciones:\n\n");

inicio: //Etiqueta :)
  do{
    printf("1-Suma de vectores(componentes)\n2-Suma de vectores(magnitud )\n3-Multiplicacion por escalar\n4-Producto escalar\n5-Producto vectorial\npresiona '?' para mas informacion\n\nQue te gustaria hacer? ");
    if( (respuesta = scani() ) != NULL && strlen(respuesta) == 1){
      opcion = respuesta[0];
      respuesta = NULL;
    }
  }while ( !(opcion > 49 || opcion < 53) && opcion != 63);
  
  switch (opcion) {
    case '1':
      cont = 0;
      salir = true;
      
      //Entrada de datos
      while (salir) {
        printf("Dame los componentes del vector %i\t", cont + 1);
        respuesta = trim(scani());
        if(!sumaCompEntrada(respuesta, &vectores)){
          printf("Ingresa de nuevo los datos\n");
        }
        else {
          ceros = 0;
          printf("%i\n", vectores[cont].dimensiones);
          while (vectores[cont].comp[ceros] == 0){
            printf("%i \t%lf\n", ceros, vectores[cont].comp[ceros]);
            ceros++;
          }
          if(ceros == vectores[0].dimensiones)
            salir = false;
          cont++;
        }
      }

      //Suma de componentes
      for(int i = 0; i < vectores[0].dimensiones; i++){
        for(int j = 0; j < cont - 1; j++)
          vectores[cont-1].comp[i] += vectores[j].comp[i];
      }

      //Salida de datos
      for(int i = 0; i < cont; i++){
        if(i < cont - 1)
          printf("Vector %i", i + 1);
        if(i == cont - 1)
          printf("vector R");
        for(int j = 0; j < vectores[0].dimensiones; j++)
          printf("\t%0.3lf", vectores[i].comp[j]);
        printf("\n");
      }
    break;

    case '2':

    break;
    case '3':
    
      break;
    
    case '4':
    
      break;
    
    case '5':
    
      break;
    
    case '?':
      printf("En este programa la entrada de datos se solicita que sea de la siguiente manera:\nx y z\na b c\n0 0 0\nRequiere de una cadena que contenga la informacion del vector separada por espacios");
      printf("\nPara terminar con la entrada de datos introduce una cadena donde todos los valores sean 0.\nSolicito que todos los vectores tengan la misma cantidad de datos.\n");
      getchar();
      goto inicio;
      break;
  }

  printf("\n");
  free(respuesta);
  free(vectores->comp);
  free(vectores);
  return 0;
}
