#include <stdio.h>
#include <stdlib.h>

/*Funcion que genera una matriz llenada con -
entradas:
-dimension: valor que usa para el numero de filas y columnas, es el mismo en ambos
salida:
-char**: una matriz que en cada uno de sus Aij tiene un -
*/
char** generar_matriz(int dimension){

	char** tablero = (char**)malloc(dimension*sizeof(char*));

	for (int i = 0; i < dimension; i++){
		tablero[i]=(char*)malloc(dimension*sizeof(char));
		for (int c = 0; c < dimension; c++){
			tablero[i][c]='-';
		}
	}

	return tablero;
}

/*Funcion que imprime por terminal la matriz actual
entradas:
- tablero: una matriz con la informacion de la sopa de letras 
- largo: dimension del numero de filas o columnas, es el mismo valor para ambas
salida: void
*/
void imprimir_matriz(char** tablero, int largo){

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
				printf("  %c", tablero[f][c]);
			}else{
				if(c<10){
					printf("  %c", tablero[f][c]);	
				}else{
					printf("   %c", tablero[f][c]);
				}
				
			}
			
		}
		printf("\n");
	}
}

/*Funcion que  solicita al jugador el largo de la matriz de juego
entrada: 
- largo: direccion de memoria
salida: void
*/
void solicitar_largo(int *largo){
	/*Se solicita y valida que el largo cumpla con los requisitos del juego*/
	int dimension=0;
	while(dimension<4){
		printf("Ingresa el valor del largo de la sopa de letras,\n(recuerda que debe ser mayor o igual a 4): ");
		scanf("%i",&dimension);
	}printf("\n");
	*largo=dimension;
}

/*Funcion que solicita el nivel de juego al usuario
entradass:
- nivel: direccion de memoria
salida: void
*/
void solicitar_nivel(char *nivel){

	int nivel_seleccionado=0;
	char teclado;

	while(nivel_seleccionado<=0){
		printf("Selecciona un nivel de dificultas\n(F - Facil)\n(M - Medio)\n(A - Alto)\nNivel: ");
		scanf(" %c", &teclado);
		switch(teclado){
			/*case int or case 'char'*/
			case 'F':
				nivel_seleccionado=1;
				break;
			case 'f':
				teclado='F';
				nivel_seleccionado=1;
				break;
			case 'M':
				nivel_seleccionado=1;
				break;
			case 'm':
				teclado='M';
				nivel_seleccionado=1;
				break;
			case 'A':
				nivel_seleccionado=1;
				break;
			case 'a':
				teclado='A';
				nivel_seleccionado=1;
				break;

			default:
			printf("\nOpcion no valida, vuelve a intentarlo\n\n");
			break;
		}
	}
	*nivel = teclado;
}
void solicitar_palabras(){
	FILE *archivo;
	char ch;
	char nombre_archivo[1000];
	int existe_archivo=0;
	while(existe_archivo<=0){
		printf("Ingresa el nombre del archivo\n(recuerda que el archivo debe \nestar en el mismo directorio,\ndonde esta este programa): ");
		scanf("%s", nombre_archivo);
		
		archivo=fopen(nombre_archivo,"r");

	    if(archivo==NULL){
	        printf("\nEl nombre esta mal escrito o no se puede abrir, intentalo nuevamente.\n\n");
	    } 
	    else{ 
	    	printf("\nLas palabras contenidas en el archivo '%s' son: \n\n", nombre_archivo);
	        while((ch=fgetc(archivo))!=EOF){
	        	if(ch!='\n'){
        			printf("%c",ch);
	        	}else{
	        		printf(".\n- ");
	        	}
	            
	        }printf("\n");
	        existe_archivo=1;
	    }
	}
}

/*Inicio del programa*/
int main()
{
	printf("-- Bienvenido --\n\n");


	int largo=0;
	//solicito al usuario ingresar el largo de matriz de juego
	solicitar_largo(&largo);

	//Declaro la variable del tablero
	char** tablero;

	//creo la matriz
	tablero = generar_matriz(largo);

	//imprimo la variable, es opcional
	//imprimir_matriz(tablero, largo);
	
	/*Se solicita el nivel con el que el usuario quiere comenzar a jugar*/
	char nivel;
	solicitar_nivel(&nivel);

	/*Se solicita el nombre del archivo de donde se extraeran las palabras*/
	solicitar_palabras();

	printf("\nFinalizo el juego\n");

	//Libero la memoria solicitada
	free(tablero);
	return 0;
}