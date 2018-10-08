/*esta forma de import, es para indicar que vaya a buscar en 
encabezados de la biblioteca estandar*/
#include <stdio.h>
#include <stdlib.h>//Para usar malloc
#include <string.h>//Para usar strlen
/*Para importar un archivo dentro del mismo directorio*/
//#include "nombre_archivo"

/*Pra declarar una constante inmutable(no cambia de valor)*/
#define PI 3.14159 //float

/*Para declarar una macro*/
#define CUBO(a) a*a*a

/*C posee 32 palabras reservadas, las cuales no pueden ser usadas
para declarar una variable

char
int
float
double
long
short
signed
unsigned
void
if
else
do
while
for
switch
case
default
break
continue
goto
struct
union
enum
typedef
return
auto
extern
register
const
static
volatile
sizeof

*/

/*Asi se hace un comentario
de varios parrafos*/

//Un comentario breve

int main(){
	/*Operadores Logicos

	Operadores de igualdad
	==
	!=

	Operadores de relacion
	>
	<
	>=
	<=

	if(condicion){
	
	}
	else if (condicion){
	
	}
	else{
	
	}

	*/
	/*Ciclo for*/
	int contador;
	for( contador = 1 ; contador <= 10 ; contador++ ){
		printf("El pivote del for va en %i\n", contador);
	}
	printf("\n");
	/*Ciclo while*/
	int contador2;
	while(contador2<=10){
		printf("El pivote del while va en %i\n", contador2);
		contador2++;	
	}
	printf("\n");
	/*Ciclo do while*/
	int contador3=1;
	do{
		printf("El pivote del do while va en %i\n", contador3);
		contador3++;
	}while(contador3<=10);
	printf("\n");
	/*Switch*/
	int casos;
	printf("Ingresa un caso: ");
	scanf("%i", &casos);

	switch(casos){
		/*case int or case 'char'*/
		case 1:
			printf("Caso 1\n");
			break;
		case 2:
			printf("Caso 2\n");
			break;
		case 3:
			printf("Caso 3\n");
			break;
		case 4:
			printf("Caso 4\n");
			break;
		case 5:
			printf("Caso 5\n");
			break;

		default:
		printf("Opcion no valida\n");
		break;
	}
	
	printf("\nEL valor de pi es %f \n",PI);//variable de tipo float
	printf("El cubo de 2 es %i\n",CUBO(2));

	/*Direcciones de memoria*/
	int var = 5;
	int *apt = &var;
	printf("\nEL valor que aloja la direccion(%p) de memoria es %i\n", apt,*apt);

	/*Operador SIZEOF*/
	float array[20];
	printf("\nEl numero de bytes en el arreglo es de %lu \n", sizeof(array));//lu = long unsigned
	
	/*Asignacion dinamica de memoria*/
	char* p;
	p =(char*)malloc(5*sizeof(char));
	if (NULL== p){
		printf("Error al asignar memoria\n");
	}else{
		printf("Memoria asignada: %lu %lu \n", sizeof(p[0]),sizeof(&p));
	}

	char x1='4';
	int x2=(int)x1 -48;
	char x3=x2+'0';
	printf("%c %i %c\n",x1,x2,x3);

	free(p);//Liberacion de memoria usada y creada de forma dinamica
	return 0;
} /*Fin funcion main*/