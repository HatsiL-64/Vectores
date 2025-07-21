#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
  double magnitud;
  double angulo;
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
    if((str[n] >= 48 && str[n] <= 57) || str[n] == 46 || str[n] == 45)
      n++;
    else 
      return false;
  }
  return true;
}

//Esta funcion basicamente te hace toda la entrada en la suma de componentes. Solo requiere el array con los vectores y la str de donde sacar los datos.
//Ya incluye la validacion y creacion de los vectores. Solo llamala despues de recibir una cadena con scani
//Todas las funciones siguientes tienen el mismo fin, validar y la entrada de los datos
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
      free(componentes);
      return false;
    }
  }
  if(componentes == NULL)
  {
    printf("Entrada invalida\n");
    return false;
  }

  *vec = realloc(*vec, sizeof(vector) * vez);
  (*vec)[vez - 1].comp = malloc(sizeof(double) * dUnica);
  (*vec)[vez - 1].dimensiones = dUnica;
  for(int i = 0; i < dUnica; i++)
  {
    if(!digito(componentes[i]) )
    {
      printf("Caracteres Invalidos\n");
      return false;
    }
    (*vec)[vez - 1].comp[i] = atof(componentes[i]);
  }

  vez++;
  free(componentes);
  return true;
}

bool sumaMagnitudEntrada(char str[], vector** vec)
{
  char** magnitudDeg = NULL;
  static int vez = 1;
  int dimensiones;

  magnitudDeg = split(str, " ", &dimensiones);
  if(dimensiones != 2)
  {
    printf("Solo se requieren dos datos\n");
    free(magnitudDeg);
    return false;
  }
  if(magnitudDeg == NULL)
  {
    printf("Entrada invalida\n");
    free(magnitudDeg);
    return false;
  }

  *vec = realloc(*vec, sizeof(vector) * vez);
  (*vec)[vez - 1].comp = malloc(sizeof(double) * 2);
  (*vec)[vez - 1].dimensiones = 2;
  
  if(!digito(magnitudDeg[0]) || !digito(magnitudDeg[1])){
    printf("Caracteres invalidos\n");
    free(magnitudDeg);
    return false;
  }
  else {
    (*vec)[vez - 1].magnitud = atof(magnitudDeg[0]);
    (*vec)[vez - 1].angulo = atof(magnitudDeg[1]);
  }
  
  vez++;
  free(magnitudDeg);
  return true;
}

bool vectorComp(char str[], vector** vec)
{
  char** componentes = NULL;
  int dimensiones;

  componentes = split(str, " ", &dimensiones);
  if(dimensiones != 2){
    printf("Solo se requieren dos datos\n");
    free(componentes);
    return false;
  }
  if(componentes == NULL){
    printf("Entrada invalida\n");
    free(componentes);
    return false;
  }

  *vec = malloc(sizeof(vector));
  (*vec)[0].comp = malloc(sizeof(double) * 2);

  if(!digito(componentes[0]) && !digito(componentes[1])){
    printf("Caracteres invalidos\n");
    free(componentes);
    return false;
  }
  else {
    (*vec)[0].comp[0] = atof(componentes[0]);
    (*vec)[0].comp[1] = atof(componentes[1]);
  }

  free(componentes);
  return true;
}

bool multEscalar(char str[], vector** vec)
{
  char** componentes = NULL;
  int dimensiones;

  componentes = split(str, " ", &dimensiones);
  if(componentes == NULL)
  {
    printf("entrada invalida\n");
    free(componentes);
    return false;
  }
  
  *vec = malloc(sizeof(vector));
  (*vec)[0].comp = malloc(sizeof(double) * dimensiones);
  (*vec)[0].dimensiones = dimensiones;

  for(int i = 0; i < dimensiones; i++)
  {
    if(!digito(componentes[i])){
      printf("Caracteres invalidos\n");
      free(componentes);
      return false;
    }
    else
      (*vec)[0].comp[i] = atof(componentes[i]);
  }

  free(componentes);
  return true;
}

bool productoEscalar(char str[], vector** vec)
{
  char** temp = NULL;
  static int vez = 0, dimensiones;
  int pruDim;

  if(vez == 0)
    temp = split(str, " ", &dimensiones);
  else{
    temp = split(str, " ", &pruDim);
    if(pruDim != dimensiones){
      printf("Las dimensiones difieren entre los vectores\n");
      free(temp);
      return false;
    }
  }
  if(temp == NULL)
  {
    printf("Entrada invalida\n");
    free(temp);
    return false;
  }
 
  if(vez == 0)
    *vec = malloc(sizeof(vector) * 2);
  (*vec)[vez].comp = malloc(sizeof(double) * dimensiones);
  (*vec)[vez].dimensiones = dimensiones;
  (*vec)[vez].magnitud = 0;

  for(int i = 0; i < dimensiones; i++){
    if(!digito(temp[i])){
      printf("Caracteres invalidos\n");
      free(temp);
      return false;
    }
    else
      (*vec)[vez].comp[i] = atof(temp[i]);
  }
  vez++;
  free(temp);
  return true;
}

bool productoVectorial(char str[], vector** vec)
{
  char** temp = NULL;
  static int vez = 0, dimensiones;
  int pruDim;

  if(vez == 0){
    temp = split(str, " ", &dimensiones);
    if(dimensiones != 3 && dimensiones != 2){
      printf("Se requiere unicamente de 2 - 3 componentes");
      free(temp);
      return false;
    }
  }
  else {
    temp = split(str, " ", &pruDim);
    if(pruDim != dimensiones){
      printf("Las dimensiones difieren entre los vectores\n");
      free(temp);
      return false;
    }
  }
  if(temp == NULL){
    printf("Entrada invalida");
    free(temp);
    return false;
  }

  if(vez == 0){
    *vec = malloc(sizeof(vector) * 3);
    for(int i = 0; i < 3; i++)
      (*vec)[i].comp = malloc(sizeof(double) * 3);
  }
  (*vec)[vez].dimensiones = dimensiones;
  (*vec)[vez].magnitud = 0;

  for(int i = 0; i < dimensiones; i++){
    if(!digito(temp[i])){
      printf("Caracteres invalidos\n");
      free(temp);
      return false;
    }
    else
      (*vec)[vez].comp[i] = atof(temp[i]);
  }
  if(dimensiones == 2)
    (*vec)[vez].comp[2] = 0;
  vez++;
  free(temp);
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
        if(!sumaCompEntrada(respuesta, &vectores)){
          printf("Ingresa de nuevo los datos\n");
        }
        else {
          ceros = 0;
          while (ceros < vectores[0].dimensiones && vectores[cont].comp[ceros] == 0)
            ceros++;
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
