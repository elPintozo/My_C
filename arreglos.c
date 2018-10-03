#include <stdio.h>

/*Comentarios*/
int main(){

	/*Arreglo dimensional*/
	//int arreglo [largo]
	int tamanio;
	printf("Ingresa el largo del arreglo: ");//solicito el tamanio
	scanf("%i", &tamanio);//ingreso el tamanio

	int arreglo[tamanio];//creo el arreglo correspondiente

	for( int i=0 ; i < tamanio; i++){//relleno el arreglo con valores
		printf("EL valor de la posicion %i es: ",i+1);
		scanf("%i", &arreglo[i]);
	}

	for( int i=0 ; i < tamanio; i++){

		if(i==0){//primer elemento
			printf("[ %i ", arreglo[i]);	
		}
		else if  (i==tamanio-1){//elementos interiores
			printf(", %i ]\n", arreglo[i]);	
		}
		else{//ultimo elemento
			printf(", %i", arreglo[i]);	
		}
		
	}

	printf("\n");
	/*Arreglo multidimensional*/
	//int matriz[filas][columnas]
	int fila =2;
	int columna =3;
	int matriz[2][3]={{1,2,3},{4,5,6}};

	for(int f=0 ; f<fila ; f++){
		for(int c=0 ; c<columna ; c++){
			printf("[%i,%i] %i ",f,c, matriz[f][c]);
		}
		printf("\n");	
	}
	return 0;
} /*Fin funcion main*/