#include <stdio.h>

/*FUncion sin retorno*/
void funcion1(){
	printf("Funcion void\n");
}
/*Funcion con return int sin parametros
solicitados*/
int suma(){
	int a = 1;
	int b = 2;

	return a+b;
}
/*Funcion con parametros*/
int multiplicacion(int x, int y){
	return x*y;
}
/*Funcion recursiva*/
int factorial(int numero){
	if(numero==0){
		return 1;
	}
	else{
		return numero*factorial(numero-1);
	}
}
/*Funcion llamada por valor*/
int cubo(int n){
	return n*n*n;
}
/*Funcion llamada por referencia*/
void quinta(int *m){
	*m = *m * *m * *m * *m * *m; 
}

size_t getSize(float *arr){
	return sizeof(arr);
}
/*Comentarios*/
int main(){
	funcion1();
	printf("La funcion suma me retorna %i\n", suma() );
	printf("La funcion multiplicacion entre 4 y 5 me retorna %i\n", multiplicacion(4,5) );
	printf("Factorial de 2 %i\n", factorial(2));
	printf("Factorial de 3 %i\n", factorial(3));
	printf("Factorial de 4 %i\n", factorial(4));
	printf("Factorial de 5 %i\n", factorial(5));

	int numero=3;
	printf("El cubo del numero %i es %i \n",numero,cubo(numero) );

	int numero_2 =2;
	printf("El numero %i sera elevado a la quinta\n", numero_2);
	quinta(&numero_2);
	printf("Resulta %i \n", numero_2);

	float arreglo[20];
	printf("El largo del arreglo es de %lu\n", getSize(arreglo));
	return 0;
} /*Fin funcion main*/