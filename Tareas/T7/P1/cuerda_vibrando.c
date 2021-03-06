/*
 ============================================================================
 Name        : cuerda_vibrando.c
 Author      : Maria Camila
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void copy(float *fuente, float *destino, int num_elementos);

int main(void) {

	//Archivo
	//primera linea: xs
	//resto lineas: us
	FILE *f = fopen("cuerda_vibrando.dat","w");

	float L = 100;
	float T = 0.01;
	float ro = 40;
	float c = sqrt(ro/T);
	
	int num_modulo=5;
	int n_points = 1000;
	int n_iter = 7000*num_modulo;

	float dx = (float) L/(n_points-1);
	float dt = 0.0005;
	float r = c*dt/dx;

	float *xs=malloc(sizeof(float)*n_points);
	float *us_initial=malloc(sizeof(float)*n_points);
	float *us_past=malloc(sizeof(float)*n_points);
	float *us_present=malloc(sizeof(float)*n_points);
	float *us_future=malloc(sizeof(float)*n_points);

	//Hago un linspace de xs, lleno us_initial con la funcion inicial, lleno us_future con 0's
	int i;
	float x;
	float u;

	for (i=0; i<n_points;i++){

		x = (float) i*dx;
		
		if(x <= 0.8*L){
			u=1.25*x/L;
		}
		else{
			u=5-5*x/L;
		}
		xs[i]=x;
		us_initial[i]=u;
		us_future[i]=0;
		fprintf(f, "%f\t",x);
	}
	fprintf(f, "\n");

	//Se arreglan las condiciones de frontera
	us_initial[0] = 0.0;
	us_initial[n_points-1] = 0.0;

	//Comienzo
	fprintf(f, "%f\t", 0.0);

	float future_val;

	for (i=1; i<n_points-1;i++){
	    future_val = us_initial[i] + (pow(r,2)/2.0)* (us_initial[i+1] - 2.0*us_initial[i] + us_initial[i-1]);
	    us_future[i] = future_val;
	    fprintf(f, "%f\t", future_val);
	}
	fprintf(f, "%f\t", 0.0);
	fprintf(f, "\n");

	copy(us_initial, us_past, n_points);
	copy(us_future, us_present, n_points);

	//Ciclo principal
	int j;
	for (j=0; j<n_iter;j++){
		
		if(j%num_modulo == 0){
		    fprintf(f, "%f\t", 0.0);
		}

	    for (i=1; i<n_points-1;i++){
	        future_val = (2.0*(1.0-pow(r,2)))*us_present[i] - us_past[i] + pow(r,2)*(us_present[i+1] +  us_present[i-1]);
	        us_future[i] = future_val;
		if(j%num_modulo == 0){
		        fprintf(f, "%f\t", future_val);
		}
	    }
	    
		if(j%num_modulo == 0){
            fprintf(f, "%f\t", 0.0);
	    fprintf(f, "\n");
		}
	    copy(us_present, us_past, n_points);
	    copy(us_future, us_present, n_points);
	}

	fclose(f);

	return 0;
}

void copy(float *fuente, float *destino, int num_elementos){

	int i;
	for (i=0;i<num_elementos;i++){
		destino[i]=fuente[i];
	}
}
