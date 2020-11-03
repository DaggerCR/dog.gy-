/*
	proyecto
	hay que usar una de estaspila, cola, lista simple o doble.
	
	cuando se pase de url a codigo, ese codigo debe meterse a una tabla hash
	
	dicha tabla hash deberá almacenar varios datos:
	código generado, URL completo, un contador de visitas, un campo para
	nombre o alias y una descripción.
	
	llevar el control de los registros conforme fueron ingresados por
	el usuario, cada uno será referenciado con un número consecutivo a partir de
	1 y hasta el último ingresado.
	


*/

#include<stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Nodo
{
	char dato1[1];
	char dato2[1];
	char dato3[1];
	char dato4[1];
	char dato5[1];
	int size;
	struct Nodo *siguiente;
	struct Nodo *anterior;
};
//por ahora no se usa
typedef struct ListaSimple
{
	struct Nodo *primerNodo;
	struct Nodo *ultimoNodo;		
	
};struct ListaSimple *Lista;

// A = 65
// M = 77
// Z = 90
// a = 97
// m = 109
// z = 122

int esPar(size_t num)
{
	if(num % 2 == 0)
	{
		return 1;//es par
	}
	return 0;
}

char escoger(char a, char b)
{
	//creo que falta arreglar cuando le mandan : - 

	//tranforma caracteres especiales
	// . ?
	// / _
	if(a == 46)
		return 63;
	if(a == 47)
		return 95;
	if(b == 46)
		return 63;
	if(b == 47)
		return 95;

	//quita prioridad a vocales
	if(a == 97 || a == 101 || a == 105 || a == 111 || a == 117 )
		return b;
	if(b == 97 || b == 101 || b == 105 || b == 111 || b == 117 )
		return a;
	if(a == 65 || a == 69 || a == 73 || a == 79 || a == 85 )
		return b;
	if(b == 65 || b == 69 || b == 73 || b == 79 || b == 85 )
		return a;
	
	//retorna si mismo
	if(a == b)
		return a;
	
	if(a > b)
		return b;
	if(a < b)
		return a;
	
	//return 61;
}

void codificar10(char link[50],size_t len)
{
	//dog.gy
	//10 nodos de 1 dato cada uno
	
	char nuevoLink[10];
	int x = 0;
	while(x != len)
	{
		if( (link[x] < 77 && link[x] > 64) || (link[x] > 96 && link[x] < 109)) //ascii antes de la M, o entre a y m
		{
			nuevoLink[x] = link[x]+1;		
		}
		else
		{
			if((link[x] >= 77 && link[x] <= 90) || (link[x] > 108 && link[x] < 123))
			{
				nuevoLink[x] = link[x]-1;	
			}
			else
			{
				if(link[x] == 46)
					nuevoLink[x] = 63;
				else
					if(link[x] == 47)
						nuevoLink[x] = 95;
			}
		}
		x++;
	}
	printf("\nLink codificado10: dog.gy/%s\n",nuevoLink);
}

void codificar20(char link[50],size_t len)
{
	char nuevoLink[50];
	int x = 0;
	int y = 0;
	//if(esPar(len) == 1)
	//{
		while(x != len/2)
		{
			printf("\nUsando %d y %d\n",link[y],link[y+1]);
			nuevoLink[x] = escoger(link[y],link[y+1]);
					
			x = x+1;
			y = y+2;
		}
	//}
	/*
	else
	{
	
		while(x != len/2)
		{
			printf("\nUsando %d y %d\n",link[y],link[y+1]);
			nuevoLink[x] = escoger(link[y],link[y+1]);
					
			x = x+1;
			y = y+2;
		}
	}
	*/
	printf("\nLink codificado20: dog.gy/%s\n",nuevoLink);	
}



void codificar(char link[50])
{
	//sacamos su tamano para controles futuros
	size_t len = strlen(link);

	//saber la letra actual
	int x = 0;
	printf("\nEste link es de tamano: %d",len);
	
	/*
	while(x != len)
	{
		printf("\nCaracter: %c\n",link[x]);
		x++;
	}
	*/
	
	if(len <=10)
	{
		codificar10(link,len);
	}
	else
		if(len <=20)
		{
			codificar20(link,len);
		}
		else
			if(len <= 30)
			{
				//codificar30(link,len);
			}
	
}

int main()
{
	//definimos el link de entrada
	char link[50];
	
	printf("Digite el link: ");
	gets(link);
	
	
	
	//ejemplos de pruebas
	printf("\nLink digitado: %s",link);
	printf("\nLink digitado espacio 2: %c\n",link[2]);
	codificar(link);
	
	
	
	
	
	
}//cierre del main








