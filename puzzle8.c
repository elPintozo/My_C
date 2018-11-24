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
	tablero[0][0]=3;
	tablero[0][1]=1;
	tablero[1][0]=2;
	tablero[1][1]=0;
	return tablero;
}
/*
entradas:
salidas:
*/
 int** actualizar_puzzle(int** tablero_actual, int movimiento, int largo){
 	printf("actualizar puzzle\n");
 	imprimir_tablero(tablero_actual, largo);

 	//posicion del cero
 	int x_actual=0, y_actual=0, x_new=0, y_new=0;

 	//valor contenido en donde se pondra el cero
 	int trueque;

	for(int f=0 ; f<largo ; f++){
		for(int c=0 ; c<largo ; c++){
			int elemento = tablero_actual[f][c];
			if(elemento==0){
				x_actual =f;
				y_actual =c;
				printf("encontrado: %i (%i,%i)\n", elemento,f,c);
			}
		}
	}
	if(movimiento==1){//arriba
		x_new = x_actual -1;
		y_new = y_actual;
	}else if(movimiento==2){//abajo
		x_new = x_actual + 1;
		y_new = y_actual;
	}else if(movimiento==3){//izquierda
		y_new = y_actual-1;
		x_new = x_actual;
	}else{//derecha
		y_new = y_actual+1;
		x_new = x_actual;
	}
	printf("posicion actual: (%i,%i) | %i\n", x_actual, y_actual, tablero_actual[x_actual][y_actual]);
	printf("posicion nueva: (%i,%i) | %i\n", x_new, y_new, tablero_actual[x_new][y_new]);
	//realizar
	trueque = tablero_actual[x_new][y_new];
	tablero_actual[x_new][y_new] = 0;
	tablero_actual[x_actual][y_actual] =trueque;

	imprimir_tablero(tablero_actual, largo);
	return tablero_actual;
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
		printf("----Struct[Padre]: %d\n\n", sig->anterior->ID);

		imprimir_tablero(sig->mesa_juego, sig->largo);

		sig = sig->anterior;
		
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

	int comparador=1;
	int igualdad=1;

	for(int f=0 ; f<largo ; f++){
		for(int c=0 ; c<largo ; c++){
			
			int elemento = tabla[f][c];

			if(f+1!=largo || c+1!=largo){

				if ((elemento == comparador)){
					igualdad=1;
				}else{
					igualdad=0;
				}
			}

			printf(" comparador [%i,%i] (%i|%i){%i} ", f, c, elemento, igualdad, comparador);
			comparador=comparador+1;
		}
		printf("\n");	
	}
	printf("Tablero terminado: %i \n", igualdad);
	return igualdad;
}

/*
entradas:
- tabla:
- movimiento:
- movimiento_bloqueado:
- largo:
salidas:
*/
int puedo_mover(int** tabla, int movimiento, int movimiento_bloqueado, int largo){
	printf("Puedo mover: %i? |%i \n",movimiento, movimiento_bloqueado);
	//Los movimientos son:
	//1 -> arriba
	//2 -> abajo
	//3 -> izquierda
	//4 -> derecha

	if(movimiento==movimiento_bloqueado){
		return 0;//No
	}

	for(int f=0 ; f<largo ; f++){
		for(int c=0 ; c<largo ; c++){
			int elemento = tabla[f][c];
			if(elemento==0){

				if(movimiento==1){//intenta subir
					printf("movimiento(1): (%i,%i) %i|%i\n",f,c,f-1,f);
					if((f-1)<0){
						return 0;//No
					}
				}else if(movimiento==2){//intenta bajar
					printf("movimiento(2): (%i,%i) %i|%i\n",f,c,f+1,f);
					if((f+1)==largo){
						return 0;//No
					}
				}else if(movimiento==3){//intenta izquierda
					printf("movimiento(3): (%i,%i) %i|%i\n",f,c,c-1,c);
					if((c-1)<0){
						return 0;//No
					}
				}else{//intenta derecha
					printf("movimiento(4): (%i,%i) %i|%i\n",f,c,c+1,c);
					if((c+1)==largo){
						return 0;//No
					}
				}

			}
		}	
	}

	return 1;//Si
}

/*
entradas:
- actual_tablero:
salidas:
*/
Tablero *generar_traza(Tablero *actual_tablero){
	printf("Generar traza\n");

	if(tablero_terminado(actual_tablero->mesa_juego,actual_tablero->largo)==1){
		printf("Tablero ordenado %i \n", actual_tablero->ID);
	}
	else{
		/*mover arriba - bloquear movimiento abajo*/
		if(puedo_mover(actual_tablero->mesa_juego, 1, actual_tablero->movimiento_bloqueado, actual_tablero->largo)==1){
			printf("Puede mover 1 ID(%i)\n", actual_tablero->ID);
			Tablero *new_tablero;
			new_tablero = (Tablero*)malloc(sizeof(Tablero));
			ID = ID + 1;
			new_tablero->ID = ID;
			new_tablero->movimiento_realizado = 1;
			new_tablero->movimiento_bloqueado = 2;

			new_tablero->largo = actual_tablero->largo;
			new_tablero->mesa_juego = actualizar_puzzle(actual_tablero->mesa_juego, 1, actual_tablero->largo);

			new_tablero->anterior = actual_tablero;//actualizar
			new_tablero->arriba = NULL;
			new_tablero->abajo = NULL;
			new_tablero->izquierda = NULL;
			new_tablero->derecha = NULL;
			
			actual_tablero->arriba = new_tablero;
			printf("Padre: %i, Hijo: %i\n", actual_tablero->ID, new_tablero->ID);
			return generar_traza(actual_tablero->arriba);
		}
		/*mover abajo - bloquear movimiento arriba*/
		if(puedo_mover(actual_tablero->mesa_juego, 2, actual_tablero->movimiento_bloqueado, actual_tablero->largo)==1){
			printf("Puede mover 2 ID(%i)\n", actual_tablero->ID);
			Tablero *new_tablero;
			new_tablero = (Tablero*)malloc(sizeof(Tablero));
			ID = ID + 1;
			new_tablero->ID = ID;
			new_tablero->movimiento_realizado = 2;
			new_tablero->movimiento_bloqueado = 1;

			new_tablero->largo = actual_tablero->largo;
			new_tablero->mesa_juego = actualizar_puzzle(actual_tablero->mesa_juego, 2, actual_tablero->largo);//actualizar

			new_tablero->anterior = actual_tablero;
			new_tablero->arriba = NULL;
			new_tablero->abajo = NULL;
			new_tablero->izquierda = NULL;
			new_tablero->derecha = NULL;
			
			actual_tablero->abajo = new_tablero;
			printf("Padre: %i, Hijo: %i\n", actual_tablero->ID, new_tablero->ID);
			return generar_traza(actual_tablero->abajo);
		}
		/*mover izquierda - bloquear movimiento derecha*/
		if(puedo_mover(actual_tablero->mesa_juego, 3, actual_tablero->movimiento_bloqueado, actual_tablero->largo)==1){
			printf("Puede mover 3 ID(%i)\n", actual_tablero->ID);
			Tablero *new_tablero;
			new_tablero = (Tablero*)malloc(sizeof(Tablero));
			ID = ID + 1;
			new_tablero->ID = ID;
			new_tablero->movimiento_realizado = 3;
			new_tablero->movimiento_bloqueado = 4;

			new_tablero->largo = actual_tablero->largo;
			new_tablero->mesa_juego = actualizar_puzzle(actual_tablero->mesa_juego, 3, actual_tablero->largo);//actualizar

			new_tablero->anterior = actual_tablero;
			new_tablero->arriba = NULL;
			new_tablero->abajo = NULL;
			new_tablero->izquierda = NULL;
			new_tablero->derecha = NULL;
			
			actual_tablero->izquierda = new_tablero;
			printf("Padre: %i, Hijo: %i\n", actual_tablero->ID, new_tablero->ID);
			return generar_traza(actual_tablero->izquierda);
		}
		/*mover derecha - bloquear movimiento izquierda*/
		if(puedo_mover(actual_tablero->mesa_juego, 4, actual_tablero->movimiento_bloqueado, actual_tablero->largo)==1){
			printf("Puede mover 3 ID(%i)\n", actual_tablero->ID);
			Tablero *new_tablero;
			new_tablero = (Tablero*)malloc(sizeof(Tablero));
			ID = ID + 1;
			new_tablero->ID = ID;
			new_tablero->movimiento_realizado = 4;
			new_tablero->movimiento_bloqueado = 3;

			new_tablero->largo = actual_tablero->largo;
			new_tablero->mesa_juego = actualizar_puzzle(actual_tablero->mesa_juego, 4, actual_tablero->largo);//actualizar

			new_tablero->anterior = actual_tablero;
			new_tablero->arriba = NULL;
			new_tablero->abajo = NULL;
			new_tablero->izquierda = NULL;
			new_tablero->derecha = NULL;
			
			actual_tablero->derecha = new_tablero;
			printf("Padre: %i, Hijo: %i\n", actual_tablero->ID, new_tablero->ID);
			return generar_traza(actual_tablero->derecha);
		}
		return actual_tablero;
	}
	return actual_tablero;
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
	printf("%i--------\n", mi_tablero->ID);
	imprimir_struc(mi_tablero);
	
	return 0;
}