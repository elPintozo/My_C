#include <stdio.h>
#include <stdlib.h>
#define largo_personas 1
#define largo_marcas 1
#define largo_autos 1

struct Persona{
	char nombre[20];
	int edad;
};

struct Marca
{
	char nombre[20];
};
struct Auto
{
	char nombre[20];
	struct Marca mi_marca;
};

typedef struct Nodo
{
	char *nombre;
	struct Nodo *sig;

}Libro;

Libro *listaLibros(Libro *Lista){
	Lista = NULL;
	return Lista;
}
Libro *agregarLibro(Libro *Lista, char* nombre){
	Libro *nuevoLibro, *aux;
	nuevoLibro = (Libro*)malloc(sizeof(Libro));
	nuevoLibro->nombre = nombre;
	nuevoLibro->sig = NULL;
	if(Lista==NULL){
		Lista = nuevoLibro;
	}else{
		aux = Lista;
		while(aux->sig != NULL){
			aux=aux->sig;
		}
		aux->sig = nuevoLibro;
	}
	return Lista;
}
int main(){

	struct Persona personas[largo_personas];
	struct Marca marcas[largo_marcas];
	struct Auto autos[largo_autos];


	for (int x=0 ; x<largo_personas ; x++){
		printf("Ingresa el nombre de la %i° Persona :", x+1);
		scanf("%s", personas[x].nombre);
		printf("Ingresa la edad de la %i° Persona:", x+1);
		scanf("%i", &personas[x].edad);
	}
	printf("\n");
	for (int i = 0; i < largo_personas; i++)
	{
		printf("La %i° persona se llama %s y tienen %i anios\n", i+1, personas[i].nombre, personas[i].edad);
	}

	for (int x=0 ; x<largo_autos ; x++){
		printf("Ingresa el nombre del modelo del  %i° Auto: ", x+1);
		scanf("%s", autos[x].nombre);
		printf("Ingresa el nombre de la Marca del Auto: ");
		scanf("%s", autos[x].mi_marca.nombre);
	}
	printf("\n");
	for (int i = 0; i < largo_autos; i++)
	{
		printf("El %i° Auto de modelo %s es de Marca %s \n", i+1, autos[i].nombre, autos[i].mi_marca.nombre);
	}

	Libro *Lista = listaLibros(Lista);
	printf("1/ %p\n",Lista );
	Lista = agregarLibro(Lista, "Nombre_nuevo");
	printf("2.1/ %s\n",Lista->nombre );
	printf("2.2/ %p\n",Lista->sig );
	Lista = agregarLibro(Lista, "Nombre_nuevo2");
	if(Lista->sig !=NULL){
		printf("3.1/ %s\n",Lista->sig->nombre );
		printf("3.2/ %p\n",Lista->sig->sig );	
	}
	return 0;
}