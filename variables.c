#include <stdio.h>

int main()
{
	/*Variables y tipo de datos*/

	/*Caracter - es de tipo alfanumerico*/
	//tamanio 1 byte
	//rango entre 0...255
	char c ='c';
	printf("Char %c\n", c);

	/*Numerico*/
	//tamanio 2 byte
	//rango -32768 a 32767
	int n =1;
	printf("Int %i\n", n);

	/*Numerico corto*/
	//tamanio 2 byte
	//rango -128 a 127
	short s = -8;
	printf("Short %i\n", s);

	/*Numerico solo positivo*/
	//tamanio 2 byte
	//rango 0..65535
	unsigned int u=20;
	printf("Unsigned int %i\n", s);

	/*Numerico largo*/
	//tamanio 4 byte
	//rango -2.147.483.648 .. 2.147.483.648
	long l = 56989;
	printf("Long %li\n", l);

	/*Numerico Real*/
	//tamanio 4 byte
	//rango todos
	float f = 79.036;
	printf("Float %f\n", f);
	printf("Float redondeado a 2 decimales %.2f\n", f);
	printf("Float redondeado a 3 decimales %.3f\n", f);

	/*Numerico doblemente largo*/
	//tamanio 8 byte
	//rango Muy amplio
	double d = 56989656.5456445;
	printf("Double %f\n", d);
	printf("Double %lf\n", d);
	printf("Double redondeado %.2f\n", d);

	return 0;
}