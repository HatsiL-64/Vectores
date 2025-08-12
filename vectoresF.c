#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
  double magnitud;
  double* angulo;
  double* comp;
  int dimensiones;
} vector;

double rtd(double rad)
{
    return rad * (180.0 / PI);
}
double dtr(double deg)
{
    return deg * (PI / 180.0);
}

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
  char* str2 = strdup(str);
  char** array = malloc(sizeof(char*) * 2);
  *nPalabras = 1;

  array[0] = strtok(str2, lim);
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
    if((str[n] >= 48 && str[n] <= 57) || str[n] == 46 || str[n] == 45)
      n++;
    else 
      return false;
  }
  return true;
}
//---------------------------------------------//

void creaVector(int numVector, int dimensiones, vector** vec){
  *vec = realloc(*vec, sizeof(vector) * numVector);
  (*vec)[numVector - 1].angulo = malloc(sizeof(double) * (dimensiones - 1));
  (*vec)[numVector - 1].comp = malloc(sizeof(double) * dimensiones);
  (*vec)[numVector - 1].magnitud = 0;
  (*vec)[numVector - 1].dimensiones = dimensiones;
}

bool validaEntrada(char input[], int* palabras){
  char** elementos = NULL;
  int cElementos;

  if((strcmp(input, "=")) == 0){
    return false;
  }

  elementos = split(input, " ", &cElementos);
  static int dimReferencia;
  static int init = 0;

  if(!init){
    dimReferencia = cElementos;
    init = 1;
  }
  if(elementos == NULL){
    printf("Entrada invalida\n");
    return false;
  }
  for(int i = 0; i < cElementos; i++){
    if(!digito(elementos[i])){
      printf("Caracteres invalidos\n");
      free(elementos);
      return false;
    }
  }
  if(cElementos != dimReferencia){
    printf("Las dimensiones entre los vectores no deben variar\n");
    free(elementos);
    return false;
  }

  *palabras = cElementos;
  free(elementos);
  return true;
}

//Tiene dos opciones, la 1 asigna valores a la magnitud y angulos, la segunda opcion asigna valor a los componentes
void asignaDatos(vector* vec, char input[], int opc){
  int nElementos;
  char** elementos = NULL;
  elementos = split(input, " ", &nElementos);
  if(opc == 1){
    vec->magnitud = atof(elementos[0]);
    for(int i = 1; i < nElementos; i++)
      vec->angulo[i-1] = atof(elementos[i]);
  }
  if(opc == 2){
    for(int i = 0; i < nElementos; i++)
      vec->comp[i] = atof(elementos[i]);
  }
  free(elementos);
}

int main ()
{
  int cont, dimensiones;
  bool salir;
  char opcion, *respuesta = NULL;
  vector* vectores = NULL;

  printf("Hola este programa tiene como objetivo facilitar ciertas operaciones con vectores y calculos con matrices. Estas son las opciones:\n\n");

inicio: //Etiqueta :)
  do{
    printf("1-Suma de vectores(componentes)\n2-Suma de vectores(magnitud)\n3-Multiplicacion por escalar\n4-Producto escalar\n5-Producto vectorial\n6-Vector en base a componentes\npresiona '?' para mas informacion\n\nQue te gustaria hacer? ");
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
        if(validaEntrada(respuesta, &dimensiones)){
          creaVector(cont + 1, dimensiones, &vectores);
          asignaDatos(&vectores[cont], respuesta, 2);
          cont++;
        }else {
          if(respuesta[0] == '='){
            creaVector(cont + 1, vectores[cont].dimensiones, &vectores);
            break;
          }
        }
      }

      //Suma de componentes
      for(int i = 0; i < vectores[0].dimensiones; i++){
        for(int j = 0; j < cont; j++)
          vectores[cont].comp[i] += vectores[j].comp[i];
      }

      //Salida de datos
      for(int i = 0; i <= cont; i++){
        if(i < cont)
          printf("Vector %i", i + 1);
        if(i == cont)
          printf("vector R");
        for(int j = 0; j < vectores[0].dimensiones; j++)
          printf("\t%0.3lf", vectores[i].comp[j]);
        printf("\n");
      }
    break;/*

    case '2':
      cont = 0;
      salir = true;

      while (salir) {
        printf("Dame la magnitud y angulo del vector %i\t", cont + 1);
        respuesta = trim(scani());
        if(!sumaMagnitudEntrada(respuesta, &vectores)){
          printf("Ingresa de nuevo los datos\n");
        }
        else {
          if(vectores[cont].angulo == 0 && vectores[cont].magnitud == 0)
            salir = false;
          cont++;
        }
      }

      //Suma y calculo 
      for(int i = 0; i < cont - 1; i++)
      {
        vectores[i].comp[0] = vectores[i].magnitud * cos(dtr(vectores[i].angulo));
        vectores[i].comp[1] = vectores[i].magnitud * sin(dtr(vectores[i].angulo));      
        vectores[cont - 1].comp[0] += vectores[i].comp[0];
        vectores[cont - 1].comp[1] += vectores[i].comp[1];
      }
      vectores[cont - 1].magnitud = sqrt(pow(vectores[cont - 1].comp[0], 2) + pow(vectores[cont - 1].comp[1], 2));
      vectores[cont - 1].angulo = rtd(atan(vectores[cont - 1].comp[1] / vectores[cont - 1].comp[0]));

      //Salida
      printf("Vector\t\tMagnitud\tAngulo\t\tCompX\t\tCompY\n");
      for(int i = 0; i < cont; i++){
        if(i < cont - 1)
          printf("Vector %i\t", i + 1);
        else 
          printf("Vector R\t");
        printf("%0.3lf\t\t%0.3lf\t\t%0.3lf\t\t%0.3lf\n", vectores[i].magnitud, vectores[i].angulo, vectores[i].comp[0], vectores[i].comp[1]);
      }

    break;
    
    case '3':
      int escalar;
      salir = true;
      
      do{
        printf("Dame los componentes de tu vector\t");
        respuesta = trim(scani());
        if(multEscalar(respuesta, &vectores))
          salir = false;
      }while(salir);
      salir = true;
      do{
        printf("Dame el escalar\t");
        respuesta = trim(scani());
        if(digito(respuesta)){
          escalar = atof(respuesta);
          salir = false;
        }
      }while(salir);

      //n3-Multiplicacion
      for(int i = 0; i < vectores[0].dimensiones; i++)
        vectores[0].comp[i] *= escalar;

      printf("Componentes: ");
      for(int i = 0; i < vectores[0].dimensiones; i++)
        printf("%0.3lf ", vectores[0].comp[i]);

    break;
    
    case '4':
      double suma = 0;
      for(int i = 0; i < 2; i ++)
      {
        printf("Dame el vector %i\t", i + 1);
        respuesta = trim(scani());
        if(!productoEscalar(respuesta, &vectores))
          i--;
      }

      // calculos
      for(int i = 0; i < 2; i++){
        for(int j = 0; j < vectores[0].dimensiones; j++)
          vectores[i].magnitud += pow(vectores[i].comp[j], 2);
        vectores[i].magnitud = sqrt(vectores[i].magnitud);
      }
      for(int i = 0; i < vectores[0].dimensiones;i++){  
        vectores[0].comp[i] *= vectores[1].comp[i];
        suma += vectores[0].comp[i];
      }
      vectores[0].angulo = rtd(acos(suma / (vectores[0].magnitud * vectores[1].magnitud)));

      printf("Producto punto: %0.3lf\nAngulo entre los vectores: %0.3lf\n", suma, vectores[0].angulo);
    break;
    
    case '5':
      for(int i = 0; i < 2; i++){
        printf("Dame el vector %i\t", i + 1);
        respuesta = trim(scani());
        if(!productoVectorial(respuesta, &vectores))
          i--;
      }

      //calculos
      vectores[2].comp[0] = (vectores[0].comp[1] * vectores[1].comp[2]) - (vectores[0].comp[2] * vectores[1].comp[1]);
      vectores[2].comp[1] = (vectores[0].comp[2] * vectores[1].comp[0]) - (vectores[0].comp[0] * vectores[1].comp[2]);
      vectores[2].comp[2] = (vectores[0].comp[0] * vectores[1].comp[1]) - (vectores[0].comp[1] * vectores[1].comp[0]);

      printf("Componentes VR:\t");
      for(int i = 0; i < 3; i++)
        printf("%0.3lf ", vectores[2].comp[i]);

    break;

    case '6':
      salir = true;
      do{
        printf("Dame los componentes de tu vector\t");
        respuesta = trim(scani());
        if(!vectorComp(respuesta, &vectores)){
          printf("Ingresa de nuevo los datos\n");
        }
        else {
          if(vectores[0].comp[0] == 0 && vectores[0].comp[1] == 0)
            salir = false;
        }
      }while (salir);

      //calculos 
      vectores[0].magnitud = sqrt(pow(vectores[0].comp[0], 2) + pow(vectores[0].comp[1], 2));
      vectores[0].angulo = rtd(atan(vectores[0].comp[1] / vectores[0].comp[0]));

      //salida 
      printf("Magnitud = %0.3lf\nAngulo = %0.3lf", vectores[0].magnitud, vectores[0].angulo);

    break;
    */
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
  free(vectores->angulo);
  free(vectores);
  return 0;
}
