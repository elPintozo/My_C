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
	        			//su una de las palabras supera el numero permitodo, el juego se termina
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
	        existe_archivo=1;
	    }
	}
	*encontrada=*encontrada+1;//actualizo el numero de palabras a buscar
	*comenzar=1;//si todo anda bien comenzar tendra valor 1, de no ser asi tendra un valor distinto
	return listado;
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
	palabras = solicitar_palabras(&palabras_a_buscar, largo-1, &comenzar);

	if(comenzar==0){
		printf("\nFinalizo el juego\n");
	}else{
		printf("\nComencemos, hay %i palabras por encontrar\n", palabras_a_buscar);
		for (int i = 0; i < palabras_a_buscar; ++i){
			int largo = (int)palabras[i][0]-48 +1;
			for (int c =1; c < largo; c++)
			{
				printf("%c",palabras[i][c] );
			}
			printf("\n");
		}
	}

	//Libero la memoria solicitada
	free(tablero);
	return 0;
}