#include <stdio.h>
#include <stdlib.h>

int char_to_int(char c){
	return (int)c-48;
}
/*Funcion que imprime por terminal la lista con las combinaciones posibles
entradas:
- combinaciones: una matriz con la informacion de la sopa de letras 
- largo: cantidad de combinaciones existentes
salida: void
*/
void imprimir_combinaciones(char** combinaciones, int largo){
	/*Funcion que nos ayuda a listar los elemenos de una lista,
	mas el numero de la fila en la que se encuentra*/
	for (int fila = 0; fila < largo; fila++){
		printf("%i| ", fila+1);
		for (int columna = 0; columna < 5; columna++){
			printf("%c ", combinaciones[fila][columna]);
		}
		printf("\n");
	}
}

void imprimir_combinacion(char* combinacion, int numero){
	printf("%i |", numero);
	for (int columna = 0; columna < 5; columna++){
		printf("%c ", combinacion[columna]);
	}
	printf("\n");
}
/*Funcion que genera un arreglo con combianciones de 5 digitos
entradas:
-dimension: valor que usa para el numero de filas y columnas, es el mismo en ambos
salida:
-char**: una matriz que en cada uno de sus Aij tiene combinaciones de numeros
*/
char** agregar_combinacion(int dimension, char** old_tablero, char* combinacion){
	
	char** new_combinaciones = (char**)malloc(dimension*sizeof(char*));

	if(dimension==1){
		for (int fila = 0; fila < 1; fila++){	
			new_combinaciones[fila] = (char*)malloc(5*sizeof(char*));
			for (int columna = 0; columna < 5; columna++){
				new_combinaciones[fila][columna] = combinacion[columna];
			}
		}
	}else{
		for (int fila = 0; fila < dimension-1; fila++){	
			new_combinaciones[fila] = (char*)malloc(5*sizeof(char*));
			for (int columna = 0; columna < 5; columna++){
				new_combinaciones[fila][columna] = old_tablero[fila][columna];
			}
		}
		new_combinaciones[dimension-1] = (char*)malloc(5*sizeof(char*));
		new_combinaciones[dimension-1][0]=combinacion[0];
		new_combinaciones[dimension-1][1]=combinacion[1];
		new_combinaciones[dimension-1][2]=combinacion[2];
		new_combinaciones[dimension-1][3]=combinacion[3];
		new_combinaciones[dimension-1][4]=combinacion[4];
	}
	return new_combinaciones;
}

/*Funcion que a base de un numero genera un arreglo de 5 digitos que contiene este numero
entradas:
largo: numero de undides del numero
combinacion: el numero generado
salida:
new_combinacion: arreglo de cinco elementos con numero en forma de
*/
char* crear_combinacion(int largo, int combinacion){
	char* new_combinacion = (char*)malloc(5*sizeof(char*));
	int introducir= 5-largo;
	int unidad=100000;

	for (int i = 0; i < 5; i++){
		unidad = unidad/10;
		if(i>=introducir){
			new_combinacion[i] = '0'+combinacion/unidad;
			combinacion=combinacion%unidad;
		}else{
			new_combinacion[i]='0';
		}
	}
	return new_combinacion;
}

/*Funcion que  solicita al jugador la clave
entrada: 
- largo: direccion de memoria
salida: void
*/
void solicitar_clave(int *largo){
	/*Se solicita y valida que el largo cumpla con los requisitos del juego*/
	int dimension=0;
	while(dimension<11111 || dimension>100000){
		printf("Ingrese la clave(debe tener 5 digitos): ");
		scanf("%i",&dimension);
	}printf("\n");
	*largo=dimension;
}

/*
Hay 'A' pares de numeros consecutivos que suman 'B'
entrada: 
salida:
*/
int primer_filtro(char* combinacion, int A, int B){

	int numero_de_pares = A;
	int pares_encontrados = 0;
	int suma = B;

	for (int columna = 0; columna < 4; columna++){
		if( (char_to_int(combinacion[columna])+char_to_int(combinacion[columna+1]))==suma ){
			pares_encontrados=pares_encontrados+1;
		}
	}
	if(pares_encontrados==numero_de_pares){
		return 1;
	}else{
		return 0;
	}
}
/*
Al menos 'C' numeros son par
entrada: 
salida:
*/
int segundo_filtro(char* combinacion, int C){
	int cantidad_necesaria=C;
	int cantidad_encontrada=0;

	for (int columna = 0; columna < 5; columna++){
		if( char_to_int(combinacion[columna])!=0 && char_to_int(combinacion[columna])%2 == 0){
			cantidad_encontrada=cantidad_encontrada+1;
		}
	}
	if(cantidad_necesaria<=cantidad_encontrada){
		return 1;
	}else{
		return 0;
	}
}
/*
Hay exactamente 'D' numeros primos
entrada: 
salida:
*/
int tercer_filtro(char* combinacion, int D){
	int cantidad_necesaria=D;
	int cantidad_encontrada=0;

	for (int columna = 0; columna < 5; columna++){

		int numero = char_to_int(combinacion[columna]);
		int divisores=0;

		for(int x=1 ;x<10 ;x++){
			if(numero%x==0){
				divisores=divisores+1;	
			}
		}
		if(divisores==2){
			cantidad_encontrada=cantidad_encontrada+1;
		}
	}
	if(cantidad_necesaria==cantidad_encontrada){
		return 1;
	}else{
		return 0;
	}
}
/*
Hay 'E' pares de numeros seguidos en la secuencia que son consecutivos
entrada: 
salida:
*/
int cuarto_filtro(char* combinacion, int E){

	int columna_1 = combinacion[0];
	int columna_2 = combinacion[1];
	int columna_3 = combinacion[2];
	int columna_4 = combinacion[3];
	int columna_5 = combinacion[4];

	int cantidad_necesaria=E;
	int cantidad_encontrada=0;

	for (int columna = 0; columna < 3; columna=columna+2){
		if( char_to_int(combinacion[columna]) == char_to_int(combinacion[columna+1]) ){
			cantidad_encontrada=cantidad_encontrada+1;
		}
	}

	if(cantidad_necesaria==cantidad_encontrada){
		return 1;
	}else{
		return 0;
	}
}

int main(){

	int A=1;  //Hay 'A' pares de numeros consecutivos que suman 'B'
	int B=11; //Hay 'A' pares de numeros consecutivos que suman 'B'
	int C=2;  //Al menos 'C' numeros son par
	int D=1;  //Hay exactamente 'D' numeros primos
	int E=2;  //Hay 'E' pares de numeros seguidos en la secuencia que son consecutivos

	char** todas_las_combinaciones;
	int combinaciones_encontradas=0;

	int filtro1_encontradas=0;
	int filtro2_encontradas=0;
	int filtro3_encontradas=0;
	int filtro4_encontradas=0;

	int contador=0;
	int password=0;


	while(contador<100000){
		char* combinacion;

		if(contador>=0 && contador<10 ){
			combinacion = crear_combinacion(1, contador);
			combinaciones_encontradas=combinaciones_encontradas+1;
			//todas_las_combinaciones = agregar_combinacion(combinaciones_encontradas, todas_las_combinaciones, combinacion);
			//printf(" combinacion de 1 cifra\n");
		}
		if(contador>=10 && contador<100){
			combinacion = crear_combinacion(2, contador);
			combinaciones_encontradas=combinaciones_encontradas+1;
			//todas_las_combinaciones = agregar_combinacion(combinaciones_encontradas, todas_las_combinaciones, combinacion);
			//printf(" combinacion de 2 cifra\n");
		}
		if(contador>=100 && contador<1000){
			combinacion = crear_combinacion(3, contador);
			combinaciones_encontradas=combinaciones_encontradas+1;
			//todas_las_combinaciones = agregar_combinacion(combinaciones_encontradas, todas_las_combinaciones, combinacion);
			//printf(" combinacion de 3 cifra\n");
		}
		if(contador>=1000 && contador<10000){
			combinacion = crear_combinacion(4, contador);
			combinaciones_encontradas=combinaciones_encontradas+1;
			//todas_las_combinaciones = agregar_combinacion(combinaciones_encontradas, todas_las_combinaciones, combinacion);
			//printf(" combinacion de 4 cifra\n");
		}
		if(contador>=10000 && contador<100000){
			combinacion = crear_combinacion(5, contador);
			combinaciones_encontradas=combinaciones_encontradas+1;
			//todas_las_combinaciones = agregar_combinacion(combinaciones_encontradas, todas_las_combinaciones, combinacion);
			//printf(" combinacion de 5 cifra\n");
		}
		contador=contador+1;

		if(primer_filtro(combinacion, A, B)==1){
			filtro1_encontradas=filtro1_encontradas+1;
			if(segundo_filtro(combinacion, C)==1){
				filtro2_encontradas=filtro2_encontradas+1;
				if(tercer_filtro(combinacion, D)==1){
					filtro3_encontradas=filtro3_encontradas+1;
					if(cuarto_filtro(combinacion, E)==1){
						filtro4_encontradas=filtro4_encontradas+1;

						imprimir_combinacion(combinacion, filtro4_encontradas);
						//todas_las_combinaciones = agregar_combinacion(combinaciones_encontradas, todas_las_combinaciones, combinacion);
					}
				}
			}
		}

	}
	//imprimir_combinaciones(todas_las_combinaciones, combinaciones_encontradas);
	//Primer filtro

	printf("\n");
	printf("1.- Hay %i pares de numeros consecutivos que suman %i\n", A, B);
	printf("2.- Al menos %i numeros son par\n", C);
	printf("3.- Hay exactamente %i numeros primos\n", D);
	printf("4.- Hay %i pares de numeros seguidos en la secuencia que son consecutivos\n", E);
	printf("5.- Si hay mas de una solucion, se debe tomar la del medio\n");
	printf("(En caso de ser un numero par, la mayor de las del medio)\n\n\n");
	

	printf("Resumen:\n");
	printf("Total: %i\n", combinaciones_encontradas);
	printf("Filtro 1: %i\n", filtro1_encontradas);
	printf("Filtro 2: %i\n", filtro2_encontradas);
	printf("Filtro 3: %i\n", filtro3_encontradas);
	printf("Filtro 4: %i\n", filtro4_encontradas);

	//solicitar_clave(&password);
	//free(todas_las_combinaciones);
	return 0;
}