#include <stdio.h>
#include <stdlib.h>

 int ID=0;

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


/*
Funcion que imprime todo un struc con sus "ramas"
entradas:
-tablero: struct con informacion
salidas: void
*/
void imprimir_struc(Tablero *tablero){
	Tablero *sig = tablero;

	while(sig!=NULL){
		printf("----Struct[ID]: %i\n", sig->ID);
		printf("----Struct[movimiento_realizado]: %i\n", sig->movimiento_realizado);
		printf("----Struct[movimiento_bloqueado]: %i\n", sig->movimiento_bloqueado);
		printf("----Struct[Padre]: %d\n\n", sig->anterior);

		imprimir_tablero(sig->mesa_juego, sig->largo);

		if (sig->anterior != NULL){sig = sig->anterior;}
		else if (sig->arriba != NULL){sig = sig->arriba;}
		else if (sig->abajo != NULL){sig = sig->abajo;}
		else if (sig->izquierda != NULL){sig = sig->izquierda;}
		else if (sig->derecha != NULL){sig = sig->derecha;}
		else {sig=NULL;}
		
		printf("----\n");
	}
}

/*
Funcion que valida que la matriz tenga todos sus elementos
ordenados de forma ascendente
entradas:
- tabla: matriz de largo x largo
- largo: cantidad de filas o columnas totales

salidas:
 -int: 0|1 para indicar que esta desordenado|ordenado

*/
int tablero_terminado(int** tabla, int largo){

	int comparador=1, igualdad=0;

	for(int f=0 ; f<largo ; f++){
		for(int c=0 ; c<largo ; c++){
			
			int elemento = tabla[f][c];

			if(f+1!=largo || c+1!=largo){

				if ((elemento == comparador)){
					igualdad=1;
				}else{
					igualdad=0;
				}
			}else{
				igualdad=0;
			}


			printf("[%i,%i] (%i|%i){%i} ", f, c, elemento, igualdad, comparador);
			comparador=comparador+1;
		}
		printf("\n");	
	}

	return igualdad;
}

int puedo_mover(int** tabla, int movimiento, int movimiento_bloqueado, int largo){

	//Los movimientos son:
	//1 -> arriba
	//2 -> abajo
	//3 -> izquierda
	//4 -> derecha
	int mover=1;

	for(int f=0 ; f<largo ; f++){
		for(int c=0 ; c<largo ; c++){
			int elemento = tabla[f][c];
			if(elemento==0){

				if(movimiento==1){//intenta subir
					printf("movimiento(1): %i|%i\n",c-1,c);
					if((c-1)>=0){
						mover=0;
					}
				}else if(movimiento==2){//intenta bajar
					printf("movimiento(2): %i|%i\n",c+1,c);
					if((c+1)<largo){
						mover=0;
					}
				}else if(movimiento==3){//intenta izquierda
					printf("movimiento(3): %i|%i\n",f-1,f);
					if((f-1)>=0){
						mover=0;
					}
				}else{//intenta derecha
					printf("movimiento(4): %i|%i\n",f+1,f);
					if((f+1)<largo){
						mover=0;
					}
				}

			}
		}
		printf("\n");	
	}

	return igualdad;
}
/*
entradas:
salidas:
*/
Tablero *generar_traza(Tablero *actual_tablero){

	if(tablero_terminado(actual_tablero->mesa_juego,actual_tablero->largo)==1){
		printf("Tablero ordenado %i \n", actual_tablero->ID);
		return actual_tablero;
	}
	else{
		/*mover arriba - bloquear movimiento abajo*/
		if(puedo_mover(actual_tablero->mesa_juego,actual_tablero->largo,1,new_tablero->movimiento_bloqueado, actual_tablero->largo)==1){

			Tablero *new_tablero;
			new_tablero = (Tablero*)malloc(sizeof(Tablero));
			ID = ID + 1;
			new_tablero->ID = ID;
			new_tablero->movimiento_realizado = 1;
			new_tablero->movimiento_bloqueado = 2;

			new_tablero->largo = actual_tablero->largo;
			new_tablero->mesa_juego = tablero;

			new_tablero->anterior = actual_tablero;//actualizar
			new_tablero->arriba = NULL;
			new_tablero->abajo = NULL;
			new_tablero->izquierda = NULL;
			new_tablero->derecha = NULL;
			
			actual_tablero->arriba = new_tablero;

			return actual_tablero->arriba;
		}
		/*mover abajo - bloquear movimiento arriba*/
		if(puedo_mover(actual_tablero->mesa_juego, actual_tablero->largo, 2, new_tablero->movimiento_bloqueado, actual_tablero->largo)==1){

			Tablero *new_tablero;
			new_tablero = (Tablero*)malloc(sizeof(Tablero));
			ID = ID + 1;
			new_tablero->ID = ID;
			new_tablero->movimiento_realizado = 2;
			new_tablero->movimiento_bloqueado = 1;

			new_tablero->largo = actual_tablero->largo;
			new_tablero->mesa_juego = tablero;//actualizar

			new_tablero->anterior = actual_tablero;
			new_tablero->arriba = NULL;
			new_tablero->abajo = NULL;
			new_tablero->izquierda = NULL;
			new_tablero->derecha = NULL;
			
			actual_tablero->abajo = new_tablero;

			return actual_tablero->abajo;
		}
		/*mover izquierda - bloquear movimiento derecha*/
		if(puedo_mover(actual_tablero->mesa_juego, actual_tablero->largo, 3, new_tablero->movimiento_bloqueado, actual_tablero->largo)==1){

			Tablero *new_tablero;
			new_tablero = (Tablero*)malloc(sizeof(Tablero));
			ID = ID + 1;
			new_tablero->ID = ID;
			new_tablero->movimiento_realizado = 3;
			new_tablero->movimiento_bloqueado = 4;

			new_tablero->largo = actual_tablero->largo;
			new_tablero->mesa_juego = tablero;//actualizar

			new_tablero->anterior = actual_tablero;
			new_tablero->arriba = NULL;
			new_tablero->abajo = NULL;
			new_tablero->izquierda = NULL;
			new_tablero->derecha = NULL;
			
			actual_tablero->izquierda = new_tablero;

			return actual_tablero->izquierda;
		}
		/*mover derecha - bloquear movimiento izquierda*/
		if(puedo_mover(actual_tablero->mesa_juego, actual_tablero->largo, 4, new_tablero->movimiento_bloqueado, actual_tablero->largo)==1){

			Tablero *new_tablero;
			new_tablero = (Tablero*)malloc(sizeof(Tablero));
			ID = ID + 1;
			new_tablero->ID = ID;
			new_tablero->movimiento_realizado = 4;
			new_tablero->movimiento_bloqueado = 3;

			new_tablero->largo = actual_tablero->largo;
			new_tablero->mesa_juego = tablero;//actualizar

			new_tablero->anterior = actual_tablero;
			new_tablero->arriba = NULL;
			new_tablero->abajo = NULL;
			new_tablero->izquierda = NULL;
			new_tablero->derecha = NULL;
			
			actual_tablero->derecha = new_tablero;

			return actual_tablero->derecha;
		}
		return actual_tablero;
	}
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
	
	mi_tablero=generar_traza(mi_tablero);

	return 0;
}