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
				printf("Este nivel aun esta en desarrollo.\n\n");
				break;
			case 'a':
				teclado='A';
				printf("Este nivel aun esta en desarrollo.\n\n");
				break;

			default:
			printf("\nOpcion no valida, vuelve a intentarlo\n\n");
			break;
		}
	}printf("\n");
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
int fila_columna_random(int hasta, int* excluir, int n_excluir){
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

/*Una vez ya determinada la fila/columna destinada a la palabra,
se debe obtener la posicion inicial de la letra de la palbra,
se debe evitar que esta comience al final ,ya que podria faltar
letras de la palabra por aparecer
entradas:
- hasta: largo de la fila/columna menos el largo de la palabra
salidas:
- mi_random: numero aleatorio dentro del rango [0,hasta]*/
int posicion_random(int hasta){
	time_t t;
  	
  	/* Intializes random number generator */
	srand((unsigned) time(&t));
	int mi_random = rand() % hasta;
	return mi_random;
}

/*
Funcion que inserta una palabra dentro del tablero en alguna fila en particular
entradas:
-tablero:tablero de juego
-palabras: lista de palabras
-palabra: numero de la palabra en la lista
-fila: numero de la fila en donde comenzar a insertar la palabra caracter a caracter
-columna: numero de la columna en donde comenzar a insertar la palabra caracter a caracter
-filas_columnas: largo de la matriz
salidas:
-tablero: tablero con al palabra a agregar ya en ella*/
char** agregar_palabra_en_fila(char** tablero, char** palabras,int palabra, int fila, int columna, int filas_columnas){

	int len_palabra=(int)palabras[palabra][0]-48;
	int pivote_palabra=1;

	for (int c = columna; c < columna+len_palabra; c++)
	{
		tablero[fila][c]=palabras[palabra][pivote_palabra];
		pivote_palabra=pivote_palabra+1;
	}
	return tablero;
}

/*
Funcion que inserta una palabra dentro del tablero en alguna columna en particular
entradas:
-tablero:tablero de juego
-palabras: lista de palabras
-palabra: numero de la palabra en la lista
-fila: numero de la fila en donde comenzar a insertar la palabra caracter a caracter
-columna: numero de la columna en donde comenzar a insertar la palabra caracter a caracter
-filas_columnas: largo de la matriz
salidas:
-tablero: tablero con al palabra a agregar ya en ella*/
char** agregar_palabra_en_columna(char** tablero, char** palabras,int palabra, int fila, int columna, int filas_columnas){

	int len_palabra=(int)palabras[palabra][0]-48;
	int pivote_palabra=1;

	for (int f = fila; f < fila+len_palabra; f++)
	{
		tablero[f][columna]=palabras[palabra][pivote_palabra];
		pivote_palabra=pivote_palabra+1;
	}
	return tablero;
}

/*Funcion que rellena los espacios de la matriz sin las letras de las palabras en ella 
entradas:
-tablero: la matriz de juego
-filas_columnas: el largo de la fila/columna del tablero
salidas:
-tablero:matriz con las modificaciones correspondientes
*/
char** rellenar_tablero(char** tablero, int filas_columnas){

	int min=97; //Letra a en ASCII
	int max=122; //Letra z en ASCII

	for (int f = 0; f < filas_columnas; f++){
		for (int c = 0; c < filas_columnas; c++){

			int letra_rand = rand() % (max + 1 - min) + min;
			char letra = (char)letra_rand;

			if(tablero[f][c]=='-'){
				tablero[f][c]= letra;
			}
		}	
	}
	return tablero;
}
/*
Funcion que organiza la insercion de las palabras dentro del table, esto segun el nivel que halla seleccionado el jugador
entradas:
-tablero: matriz con el tablero de juego
-nivel: el el nivel que selecciono el usuario al comenzar el juego
-palabras: list con las palabras
-n_palabras: numero de palabras a insertar
-filas_columnas largo de la matriz
salidas:
-tablero: tablero con todas las palabras insertadas
*/
char** cargar_palabras_al_tablero(char** tablero, char nivel, char** palabras, int n_palabras, int filas_columnas){
	int palabras_insertadas=0;
	int* reservar=(int*)malloc(n_palabras*sizeof(int));
	int n_reservar=0;

	//Armo una lista vacia que sera usada pasa saber que filas/columnas ya estan ocupadas
	//y no pueden ser ocupadas para el random
	for (int i = 0; i < filas_columnas; i++){
		reservar[i]=-1;
	}

	if(nivel=='F'){
		for (int i = 0; i <n_palabras; i++){
			int columna = fila_columna_random(filas_columnas, reservar, n_reservar);
			int len_palabra=(int)palabras[i][0]-48;
			int fila = posicion_random(filas_columnas-len_palabra);
			tablero = agregar_palabra_en_columna(tablero,palabras,i,fila, columna, filas_columnas);
			reservar[i]=columna;
			n_reservar=n_reservar+1;
		}
	}else if(nivel=='M'){
		for (int i = 0; i < n_palabras; i++){
			int fila = fila_columna_random(filas_columnas, reservar, n_reservar);
			int len_palabra=(int)palabras[i][0]-48;
			int columna = posicion_random(filas_columnas-len_palabra);
			tablero = agregar_palabra_en_fila(tablero,palabras,i,fila, columna, filas_columnas);
			reservar[i]=fila;
			n_reservar=n_reservar+1;
		}
	}else{
		printf("Palabras en diagonal\n");
	}

	return rellenar_tablero(tablero, filas_columnas);
}

/**/
char** encontrar_palabra(char** tablero, char** palabras, int n_palabra_a_buscar, int f_inicio, int c_inicio, int f_termino, int c_termino, int largo, int *estaba_palabra){
	int largo_palabra=(int)palabras[n_palabra_a_buscar][0]-48;
	int pivote_palabra=1;
	int iguales=0;


	for (int f = f_inicio; f <= f_termino; f++){
		for (int c = c_inicio; c <= c_termino; c++){
			if(pivote_palabra<=largo_palabra){
				if(tablero[f][c]==palabras[n_palabra_a_buscar][pivote_palabra]){
					iguales=iguales+1;
					pivote_palabra=pivote_palabra+1;
				}
			}
			else{
				iguales=iguales-1;
			}
		}
	}
	/**/
	if(iguales==largo_palabra){
		*estaba_palabra=1;
	}
	
	return tablero;
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
	//Si la variable termino_juego tiene el mismo valor que palabras_a_buscar has ganado
	int termino_juego=0;
	while(termino_juego!=palabras_a_buscar){
		system("clear");
		printf("\nComencemos, hay %i de %i palabras por encontrar\n", palabras_a_buscar-termino_juego,palabras_a_buscar);
		for (int i = 0; i < palabras_a_buscar; ++i){
			int largo = (int)palabras[i][0]-48 +1;
			//Si la palabra tiene largo cero, es porque ya fue encontrada
			if(largo!=1){
				printf("%i - ", i+1);
				for (int c =1; c < largo; c++)
				{
					printf("%c",palabras[i][c] );
				}
				printf("\n");
			}
		}printf("\n");
		tablero=cargar_palabras_al_tablero(tablero, nivel, palabras, palabras_a_buscar, largo);
		imprimir_matriz(tablero, largo);

		int n_palabra_a_buscar=0;
		int buscar_fila=0;
		int buscar_columna=0;

		int f_inicio=0;
		int f_termino=0;
		int c_inicio=0;
		int c_termino=0;

		/*Valido que el numero de la palabra a buscar este dentro de listado*/
		int n_palabra_valida=0;
		while(n_palabra_valida==0){
			printf("\nHas encontrado una palabra?, indica N° de la palabra encontrada:");
			scanf("%i", &n_palabra_a_buscar);
			if(n_palabra_a_buscar>0 && n_palabra_a_buscar<=palabras_a_buscar){
				n_palabra_valida=1;
			}else{
				printf("EL numero ingresado no esta dentro de las palabras\n");
			}
		}
		//variable que me ayuda a controlar las variables para encontrar una palabra
		//mientras no encuentre una palabra seguira pidiendo coordenadas
		int coordenadas=0;
		while(coordenadas==0){
			printf("\nN° de la fila en donde comienza la palabra: ");
			scanf("%i", &f_inicio);
			printf("\nN° de la columna en donde comienza la palabra: ");
			scanf("%i", &c_inicio);
			printf("\nN° de la fila en donde termina la palabra: ");
			scanf("%i", &f_termino);
			printf("\nN° de la columna en donde termina la palabra: ");
			scanf("%i", &c_termino);

			//En el nivel facil cada palabra esta contenida dentro de una sola columna, por ende de introducir columnas distintas ya no esta ahi
			//En el nivel medio cada palabra esta contenida dentro de una sola fila, por ende de introducir filas distintas ya no esta ahi
			if( (c_inicio!=c_termino && nivel=='F') || (f_inicio!=f_termino && nivel=='M')){
				printf("No esta la palabra en las coordenadas [%i,%i] [%i,%i], vuelve a intentarlo\n", f_inicio, c_inicio,f_termino,c_termino);
			}else{
				if(f_inicio>largo || f_termino>largo || c_inicio>largo || c_termino>largo ){
					printf("Uno de los valores de las coordenadas no es valido\n");
				}else{
					/*Si esta variable cambia su valor luego de la ejecucion de la funcion
					encontrar_palabra, es porque la encontro, por ende la palabra se elimina del listado
					*/
					int estaba_palabra=0;
					tablero =encontrar_palabra(tablero, palabras, n_palabra_a_buscar-1, f_inicio-1, c_inicio-1, f_termino-1, c_termino-1, largo, &estaba_palabra);
					if(estaba_palabra!=0){
						estaba_palabra=0;
						palabras[n_palabra_a_buscar-1][0]=0+'0';
						termino_juego=termino_juego+1;
						coordenadas=1;
					}else{
						printf("Lo siento la palabra no estaba en esas coordenadas, vuelve a intentarlo.\n");
					}
				}
			}
		}
	}
	printf("\n\nHas ganado el juego!!!\n");
	//Libero la memoria solicitada
	free(tablero);

	return 0;
		
}