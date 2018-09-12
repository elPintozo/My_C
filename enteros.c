#include <stdio.h>

/*Comentarios*/
int main(){
	/*Suma de numeros enteros*/

	/*Declaracion de variables*/
	int numero1;
	int numero2;
	int resultado;

	/*Peticion de variables*/
	printf("Ingrese el primer valor: ");
	scanf("%d", &numero1);/* %d =  entero decimal */
	printf("Ingrese el segundo valor: ");
	scanf("%d", &numero2);/* %d =  entero decimal */
	
	/*---------------------------*/
	/*Operadores aritmeticos*/

	/*Suma*/
	resultado = numero1+numero2;
	printf("El resultado de %d + %d es %d \n",numero1,numero2,resultado );

	/*Resta*/
	resultado = numero1-numero2;
	printf("El resultado de %d - %d es %d \n",numero1,numero2,resultado );

	/*Multiplicacion*/
	resultado = numero1*numero2;
	printf("El resultado de %d * %d es %d \n",numero1,numero2,resultado );

	/*Multiplicacion*/
	resultado = numero1/numero2;
	printf("El resultado de %d / %d es %d \n",numero1,numero2,resultado );
	return 0;
} /*Fin funcion main*/