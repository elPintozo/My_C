#include <stdio.h>

/*Comentarios*/
int main(){

	int a = 80;
	printf("Numero original int %i\n", a);

	/*int to float*/
	float f = (float)a;
	printf("Conversion de int %i a float %.2f \n", a, f);

	/*int to double*/
	double d = (double)a;
	printf("Conversion de int %i a double %.3f \n", a, d);

	/*int to char*/
	char c = (char)a;
	printf("Conversion de int %i a char %c \n", a, c);

	int i =45;
	float f2= 56.03;
	float suma = (float)i + f2;
	printf("La suma de int %i + el float %.2f es : %.2f\n",i,f2, suma);

	return 0;
} /*Fin funcion main*/