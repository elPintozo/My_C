#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	while(dimension<5){
		printf("Ingresa el valor del largo de la sopa de letras,\n(recuerda que debe ser mayor a 4): ");
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
/*Funcion que agrega una letra a un arreglo que contiene parte de una palabra
entrada: 
- palabra: un arreglo que puede o no contener uno o varios caracteres previos
- letra: char que se agregara al final de la variable anterios
- largo: la posicion del caracter en la variable palabra*/
char* agregar_letra_a_palabra(char* palabra, char letra, int largo){

	int nuevo_largo = largo+1;//como la posicion 0 tiene su largo, se desplaza en uno la posicion de inicio
	char* palabra_nueva = (char*)malloc((nuevo_largo+1)*sizeof(char));

	if(largo>0){
		int len_actual = (int)palabra[0];//la posicion 0 es el largo de la palabra
		len_actual = len_actual-48; //Para convetir el c a int debo restarle el ASCII
		len_actual = len_actual+1;//incremento en uno el largo de la palabra
		palabra_nueva[0]=len_actual+'0';//almaceno el largo en formato char

		//el arreglo parte de la posicion 1, ya que, en la posicion 0 esta el largo
		for (int i =1; i < nuevo_largo; i++){
			palabra_nueva[i]=palabra[i];
		}
	}
	else{
		palabra_nueva[0]=1+'0';//la palabra parte con largo 1, ya que se agrego el primer caracter
	}
	//agrego alfinal el nuevo caracter
	palabra_nueva[nuevo_largo]=letra;
	
	return palabra_nueva;
}

/*Funcion que agrega una palabra a un listado en una posicion determinada
que siempre resulta ser la ultima posicion del listado anterior mas un nuevo
espacio resevado
entradas:
- listado: matriz que contiene las palabras obtenidas del txt
- palabra: list con la palabra ingresada
- fila: posicion que indica donde ira la nueva palabra, tambien se usa 
para saber el contenido de palabras actuales, para realizar una nueva
lista con mas espacio de memoria
salida;
-nueva_lista: lista que contiene las palabaras de listado, mas la palabra a ingresar*/
char** agregar_palabra(char** listado, char* palabra, int fila){

	char** nueva_lista = (char**)malloc((fila+1)*sizeof(char*));

	//replico el listado anterior pero con un espacio mas
	for (int i = 0; i < fila; ++i){

		//obtengo el largo desde la posicion cero del array con la palabra
		int largo_palabra = (int)listado[i][0]-48 +1;
		char* palabra_nueva = (char*)malloc((largo_palabra)*sizeof(char));
		for (int y = 0; y < largo_palabra; y++)
		{
			palabra_nueva[y]=listado[i][y];
		}
		nueva_lista[i]=palabra_nueva;
	}
	
	//inserto al final del listado la palabra nueva
	int largo_palabra = (int)palabra[0]-48 +1;
	char* palabra_nueva = (char*)malloc((largo_palabra)*sizeof(char));
	for (int i = 0; i < largo_palabra; i++)
	{
		palabra_nueva[i]=palabra[i];
	}

	nueva_lista[fila]=palabra_nueva;

	return nueva_lista;
}

/*Funcion que solicita al usuario el archivo txt con las palabras a poner en la
sopa de letras.
entradas:
-n_palabras: puntero con la variable que contiene la cantidad de palabras del txt
-maixmo: el maximo de palabras permitidas y el largo maximo de caracteres de cada una
salida:
- lista con las palabras*/
char** solicitar_palabras(int *encontrada,int maximo, int *comenzar){

	char** listado;
	FILE *archivo;
	char letra;
	char nombre_archivo[1000];
	int existe_archivo=0;

	while(existe_archivo<=0){
		printf("Ingresa el nombre del archivo\n(recuerda que el archivo debe \nestar en el mismo directorio,\ndonde esta este programa): ");
		scanf("%s", nombre_archivo);
		
		archivo=fopen(nombre_archivo,"r");

		//Si el archivo presenta errores
	    if(archivo==NULL){
	        printf("\nEl nombre esta mal escrito o no se puede abrir, intentalo nuevamente.\n\n");
	    } 
	    else{//de abrir el archivo sin problemas 
	    	int contador=0;//variable usada para leer las letras dentro de 
	    	char* palabra;

	        while((letra=fgetc(archivo))!=EOF){

	        	/*Si encuentra un caracter distinot de un salto de linea*/
	        	if(letra!='\n'){

	        		//mientras el largo de palabra es menor a la permitida se puede crear mas
	        		if(contador<maximo){
	        			palabra = agregar_letra_a_palabra(palabra, letra, contador);
	        			contador++;
	        		}
	        		else{
	        			//si una de las palabras supera el numero permitodo, el juego se termina
	        			*comenzar=0;
	        			return listado;
	        		}
	        	}else{
	        		listado = agregar_palabra(listado, palabra, *encontrada);
	        		contador=0;
	        		*encontrada=*encontrada+1;//actualizo el numero de palabras a buscar
	        	}
	            
	        }
	        listado = agregar_palabra(listado, palabra, *encontrada);//se debe llamar para ingresar la ultima palabra
	        *encontrada=*encontrada+1;//actualizo el numero de palabras a buscar
	        existe_archivo=1;//cambio el valor de la variable a 1 para cortar el while
	    }
	}
	*comenzar=1;//si todo anda bien comenzar tendra valor 1, de no ser asi tendra un valor distinto
	return listado;
}

/*Funcion que genera un numero aleatorio entre 0 y un numero determinado
entrada:
- hasta: el valor maximo que puede tener el numero al azar
- excluir: lista con las filas o columnas ya ocupadas 
- n_excluir: numero de elementos dentro de excluir
salida:
- mi_random: numero al azar entre 0 y numero de filas/columnas*/
int numero_random(int hasta, int* excluir, int n_excluir){
	int mi_random=0, encontrado=0;
  	time_t t;
  	/* Intializes random number generator */
	srand((unsigned) time(&t));

	while(encontrado==0){
		int pillado=0;
		mi_random = rand() % hasta;
		for (int i = 0; i < n_excluir; ++i){
			if(excluir[i]==mi_random){
				pillado=1;
			}
		}	
		if(pillado==0){
			encontrado=1;
		}
	}
	return mi_random;
}
/*
entradas:
-tablero:
*/
void cargar_palabras_al_tablero(char** *tablero, char nivel, char** *palabras, int n_palabras, int filas_columnas){
	int palabras_insertadas=0;
	int* reservar=(int*)malloc(n_palabras*sizeof(int));
	int n_reservar=0;

	//Armo una lista vacia que sera usada pasa saber que filas/columnas ya estan ocupadas
	//y no pueden ser ocupadas para el random
	for (int i = 0; i < filas_columnas; i++){
		reservar[i]=-1;
	}

	if(nivel=='F'){
		printf("Palabras de forma horizontal\n");
		*tablero[0][0]='F';
		for (int i = 0; i <n_palabras; i++){
			int posicion = numero_random(filas_columnas, reservar, n_reservar);
			printf("La palabra %i se alojara en la columna %i \n", i+1, posicion );
			reservar[i]=posicion;
			n_reservar=n_reservar+1;
		}
	}else if(nivel=='M'){
		printf("Palabras de forma vertical\n");
		*tablero[0][0]='M';
		for (int i = 0; i < n_palabras; i++){
			int posicion = numero_random(filas_columnas, reservar, n_reservar);
			printf("La palabra %i se alojara en la fila %i \n", i+1, posicion );
			reservar[i]=posicion;
			n_reservar=n_reservar+1;
		}
	}else{
		printf("Palabras en diagonal\n");
		*tablero[0][0]='A';

	}

}
/*Inicio del programa*/
int main()
{
	printf("-- Bienvenido --\n\n");

	/*Antes de comenzar el juego se deben cargar las palabras,
	de ocurrir un problema con la carga, esta variable tendra un valor
	que indicara su por que del no comienzo*/
	int comenzar;

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

	/*Se genera un arreglo que contendra las palabras,
	la cantidad de palabras quedara fijado por el largo menos 1*/
	char** palabras;
	int palabras_a_buscar=0;
	palabras = solicitar_palabras(&palabras_a_buscar, largo, &comenzar);

	//la funcion solicitar_palabras puede modificar el inicio del juego con cambiar 
	//el valor de la variable comenzar como es este caso 
	if(comenzar==0){
		printf("\nUna de de las palabras supera el largo permitido que es : %i \n", largo-1);
		free(tablero);
		return 0;
	}
	//la funcion solicitar_palabras realiza un conteo de las palabras a buscar
	//si supera el maximo permitido el juego no podra comenzar
	if((largo-1)<palabras_a_buscar){
		printf("\nLa cantidad de palabras es superior a lo permitido que son : %i y hay %i \n", largo-1, palabras_a_buscar);
		free(tablero);
		return 0;
	}
	
	printf("\nComencemos, hay %i palabras por encontrar\n", palabras_a_buscar);
	for (int i = 0; i < palabras_a_buscar; ++i){
		int largo = (int)palabras[i][0]-48 +1;
		for (int c =1; c < largo; c++)
		{
			printf("%c",palabras[i][c] );
		}
		printf("\n");
	}
	printf("Antes: \n");
	imprimir_matriz(tablero, largo);
	printf("Despues\n");
	cargar_palabras_al_tablero(&tablero, nivel, &palabras, palabras_a_buscar, largo);
	imprimir_matriz(tablero, largo);

	//Libero la memoria solicitada
	free(tablero);
	return 0;
}