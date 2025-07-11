#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

typedef struct {
  double magnitud;
  double angulo;
  double compX;
  double compY;
  double compZ;
} vector;

double rtd(double rad)
{
    return rad * (180.0 / PI);
}
double dtr(double deg)
{
    return deg * (PI / 180.0);
}
void obtieneComp(double magnitud, double angulo, double *compX, double *compY)
{
  *compX = magnitud * cos(dtr(angulo));
  *compY = magnitud * sin(dtr(angulo));
}

int main ()
{
  char opc;
  int dimenciones, cantidad = 1, cont = 1;
  vector* vectores = NULL;
  
  printf("Hola, este programa incluye una serie de opciones para trabajar con vectores, como: \n1-Suma de vectores\n2-Vector en base a componentes \nSelecciona la opcion: ");
  scanf("%c", &opc);
  switch (opc) {
    case '1':
      for(int x = 0; x < cont; x++)
      {
        vector* temp = realloc(vectores, cantidad * sizeof(vector));
        if (temp == NULL) {
          printf("Error al asignar memoria.\n");
          free(vectores);
          return 1;
        }
        vectores = temp;
        cantidad++;

        printf("Dame la magnitud y angulos del vector %i separadas por un espacio: ", x + 1);
        scanf("%lf %lf", &vectores[x].magnitud , &vectores[x].angulo);
        obtieneComp(vectores[x].magnitud, vectores[x].angulo, &vectores[x].compX, &vectores[x].compY);
        if(vectores[x].magnitud != 0 || vectores[x].angulo != 0)
          cont++;
      }
      
      printf("\nMagnitud\tAngulo\tCompX\tCompy");
      
      for(int i = 0; i < cont - 1; i++)
      {
        printf("\nV%i= %0.3f\t%0.3f\t%0.3f\t%0.3f", i + 1, vectores[i].magnitud, vectores[i].angulo, vectores[i].compX, vectores[i].compY);
        if(i > 0)
        {
          vectores[0].compX += vectores[i].compX;
          vectores[0].compY += vectores[i].compY;
        }
      }
      
      vectores[0].magnitud = sqrt(pow(vectores[0].compX, 2) + pow(vectores[0].compY, 2));
      vectores[0].angulo = rtd(atan(vectores[0].compY / vectores[0].compX));
      
      printf("\n\nVector Resultante\nMagnitud\tAngulo\tCompX\tCompY\n%0.3lf\t\t%0.3lf\t%0.3lf\t%0.3lf", vectores[0].magnitud, vectores[0].angulo, vectores[0].compX, vectores[0].compY);
      break;
    case '2':

      break;
  }
  free(vectores);
  printf("\n");
  return 0;
}
