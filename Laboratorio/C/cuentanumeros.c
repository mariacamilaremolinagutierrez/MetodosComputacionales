#include <stdio.h>
#include <stdlib.h>


int main(){
  FILE *in;
  float a[100];
  float b[100];
  float c[100];
  int i;
  
  in= fopen("numerosaleatorios.dat", "r");

  if (in==0){
    printf("Problemow \n");
    exit(1);
  }

  for(i=0; i<100; i++){
    fscanf(in, "%f %f  %f", &(a[i]), &(b[i]), &(c[i]));
  }
  
  float maxa=a[0];
  float maxb=b[0];
  float maxc=c[0];

  for(i=0; i<100; i++){
    float numa=a[i];
    float numb=b[i];
    float numc=c[i];
    
    if(numa>maxb){
      maxa=numa;
    }

    if(numb>maxb){
      maxb=numb;
    }

    if(numc>maxc){
      maxc=numc;
    }
  }

  printf("El maximo numero de cada columna respectivamente es: %f %f %f \n", maxa, maxb, maxc);

  fclose(in);

  return 0;
}
