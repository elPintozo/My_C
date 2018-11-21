#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
	int ID;
	int largo;
	int** mesa_juego;

	//Los movimientos son:
	//1 -> arriba
	//2 -> abajo
	//3 -> izquierda
	//4 -> derecha
	int movimiento_realizado;
	int movimiento_bloqueado;

	struct Nodo *anterior;
	struct Nodo *arriba;
	struct Nodo *abajo;
	struct Nodo *izquierda;
	struct Nodo *derecha;

}Tablero;

/*Funcion que imprime por terminal la matriz actual
entradas:
- tablero: una matriz con la informacion de la sopa de letras 
- largo: dimension del numero de filas o columnas, es el mismo valor para ambas
salida: void
*/
void imprimir_matriz(int** tablero, int largo){

	/*For que nos ayuda a enumerar e imprimir 
	las columnas de la matriz*/
	for (int f = 0; f < largo; f++){
		if(largo<10){
			if(f==0){
			printf("    %i", f+1);	
			}else{
				printf("  %i", f+1);
			}
		}else{
			if(f==0){
				printf("     %i", f+1);	
			}else{
				printf("  %i", f+1);
			}
			
		}		
	}printf("  <- Columnas\n");

	/*Funcion que nos ayuda a listar los elemenos de una lista,
	mas el numero de la fila en la que se encuentra*/
	for (int f = 0; f < largo; f++){

		if(largo<10){
			printf("%i|", f+1);
		}else{
			if(f+1<10){
				printf("%i |", f+1);	
			}else{
				printf("%i|", f+1);
			}
			
		}
		
		for (int c = 0; c < largo; c++){
			if(largo<10){
				printf("  %i", tablero[f][c]);
			}else{
				if(c<10){
					printf("  %i", tablero[f][c]);	
				}else{
					printf("   %i", tablero[f][c]);
				}
				
			}
			
		}
		printf("\n");
	}
}

/*FUncion que imprime por pantalla el tablero de juego 
en un punto determinado
entradas:
- tabla : matriz con la informacion 
- largo: numero de filas o columnas de la matriz
salidas: void
*/
void imprimir_tablero(int** tabla, int largo){

	for(int f=0 ; f<largo ; f++){
		for(int c=0 ; c<largo ; c++){
			printf("[%i,%i] %i ",f,c, tabla[f][c]);
		}
		printf("\n");	
	}
}

/*Funcion que genera una matriz llenada con ceros
entradas:
-dimension: valor que usa para el numero de filas y columnas, es el mismo en ambos
salida:
-char**: una matriz que en cada uno de sus Aij tiene un cero
*/
int** generar_matriz(int dimension){

	int** tablero = (int**)malloc(dimension*sizeof(int*));

	for (int i = 0; i < dimension; i++){
		tablero[i]=(int*)malloc(dimension*sizeof(int));
		for (int c = 0; c < dimension; c++){
			tablero[i][c]=0;
		}
	}

	return tablero;
}

int main(){

	printf("-- Bienvenido --\n\n");

	/*Antes de comenzar el juego se debe cargar los numeros en el puzzle,
	de ocurrir un problema con la carga, esta variable tendra un valor
	que indicara su por que del no comienzo*/
	int comenzar;

	int largo=2;

	//Declaro la variable del tablero
	int** tablero;

	//creo la matriz
	tablero = generar_matriz(largo);

	//imprimo la variable, es opcional
	//imprimir_matriz(tablero, largo);

	Tablero *mi_tablero;
	mi_tablero = (Tablero*)malloc(sizeof(Tablero));
	mi_tablero->ID = 0;
	mi_tablero->movimiento_realizado = 0;
	mi_tablero->movimiento_bloqueado = 0;

	mi_tablero->largo = largo;
	mi_tablero->mesa_juego = tablero;

	mi_tablero->anterior = NULL;
	mi_tablero->arriba = NULL;
	mi_tablero->abajo = NULL;
	mi_tablero->izquierda = NULL;
	mi_tablero->derecha = NULL;
	
	Tablero *sig = mi_tablero;

	while(sig!=NULL){
		printf("----Struct[ID]: %i\n", sig->ID);

		printf("----Struct[movimiento_realizado]: %i\n", sig->movimiento_realizado);
		printf("----Struct[movimiento_bloqueado]: %i\n", sig->movimiento_bloqueado);
		printf("----Struct[Padre]: %d\n", sig->anterior);

		imprimir_tablero(sig->mesa_juego, sig->largo);

		if (sig->anterior != NULL){sig = sig->anterior;}
		else if (sig->arriba != NULL){sig = sig->arriba;}
		else if (sig->abajo != NULL){sig = sig->abajo;}
		else if (sig->izquierda != NULL){sig = sig->izquierda;}
		else if (sig->derecha != NULL){sig = sig->derecha;}
		else {sig=NULL;}
		
		printf("----\n");
	}

	return 0;
}