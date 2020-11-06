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
#include<stdlib.h>
#include<string.h>
#include <limits.h>

#define TABLE_SIZE 6

int contadorGeneral = 1;

typedef struct NodoLink
{
	int numeroRegistro;
	int visitas;
	char alias;
	char link[50];
	char linkCodificado[50];
	size_t size;
	struct NodoLink *siguiente;
	struct NodoLink *anterior;
};

typedef struct ListaSimple
{
	struct NodoLink *primerNodo;
	struct NodoLink *ultimoNodo;		
	
};struct ListaSimple *ListaGeneral;

typedef struct entradaT {
    char *llave;
    struct NodoLink *valor;
    struct entradaT *siguiente;
} entradaT;

typedef struct {
    entradaT **entradas;
} hashT;

unsigned int hash(const char *llave) {
    unsigned long int valor = 0;
    unsigned int i = 0;
    unsigned int llave_len = strlen(llave);

    for (; i < llave_len; ++i) {
        valor = valor * 37 + llave[i];
    }
    valor = valor % TABLE_SIZE;

    return valor;
}

entradaT *htMemoria(const char *llave, const char *valor) {
    entradaT *entrada = malloc(sizeof(entradaT) * 1);
    entrada->llave = malloc(strlen(llave) + 1);
    entrada->valor = malloc(strlen(valor) + 1);

    strcpy(entrada->llave, llave);
    strcpy(entrada->valor, valor);

    entrada->siguiente = NULL;

    return entrada;
}

hashT *htCrear(void) {
    hashT *hashtable = malloc(sizeof(hashT) * 1);

    hashtable->entradas = malloc(sizeof(entradaT*) * TABLE_SIZE);

    int i = 0;
    for (; i < TABLE_SIZE; ++i) {
        hashtable->entradas[i] = NULL;
    }

    return hashtable;
}

void ht_set(hashT *hashtable, const char *llave, const char *valor) {
    unsigned int campo = hash(llave);

    entradaT *entrada = hashtable->entradas[campo];

    if (entrada == NULL) {
        hashtable->entradas[campo] = htMemoria(llave, valor);
        return;
    }

    entradaT *aux;

    while (entrada != NULL) {
        if (strcmp(entrada->llave, llave) == 0) {
            free(entrada->valor);
            entrada->valor = malloc(strlen(valor) + 1);
            strcpy(entrada->valor, valor);
            return;
        }

        aux = entrada;
        entrada = aux->siguiente;
    }

    aux->siguiente = htMemoria(llave, valor);
}

char *ht_get(hashT *hashtable, const char *llave) {
    unsigned int campo = hash(llave);

    entradaT *entrada = hashtable->entradas[campo];

    if (entrada == NULL) {
        return NULL;
    }

    while (entrada != NULL) {
        if (strcmp(entrada->llave, llave) == 0) {
            return entrada->valor;
        }

        entrada = entrada->siguiente;
    }

    return NULL;
}

void ht_del(hashT *hashtable, const char *llave) {
    unsigned int bucket = hash(llave);

    entradaT *entrada = hashtable->entradas[bucket];

    if (entrada == NULL) {
        return;
    }

    entradaT *aux;
    int x = 0;

    while (entrada != NULL) {
        if (strcmp(entrada->llave, llave) == 0) {
            if (entrada->siguiente == NULL && x == 0) {
                hashtable->entradas[bucket] = NULL;
            }

            if (entrada->siguiente != NULL && x == 0) {
                hashtable->entradas[bucket] = entrada->siguiente;
            }

            if (entrada->siguiente == NULL && x != 0) {
                aux->siguiente = NULL;
            }

            if (entrada->siguiente != NULL && x != 0) {
                aux->siguiente = entrada->siguiente;
            }

            free(entrada->llave);
            free(entrada->valor);
            free(entrada);

            return;
        }

        aux = entrada;
        entrada = aux->siguiente;

        ++x;
    }
}

void ht_dump(hashT *hashtable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        entradaT *entrada = hashtable->entradas[i];

        if (entrada == NULL) {
            continue;
        }

        printf("campo[%4d]: ", i);

        for(;;) {
            printf("%s=%s ", entrada->llave, entrada->valor);

            if (entrada->siguiente == NULL) {
                break;
            }

            entrada = entrada->siguiente;
        }

        printf("\n");
    }
}

void agregarListaGeneral(struct NodoLink *nuevo)
{
	if(ListaGeneral->primerNodo==NULL)
	{
		printf("\nPrimer elemento\n");
		ListaGeneral->primerNodo=nuevo;
		ListaGeneral->ultimoNodo=nuevo;
	}
	else
	{
		nuevo->anterior = ListaGeneral->ultimoNodo;
		ListaGeneral->ultimoNodo->siguiente=nuevo;
		ListaGeneral->ultimoNodo=nuevo;
	}
}


typedef struct NodoLinkTree
{
	char link[50];
	char nombre[50];
	struct ListaSimple *Lista;
	
};

//por ahora no se usa


int esPar(size_t num)
{
	if(num % 2 == 0)
	{
		return 1;//es par
	}
	return 0;
}

char escoger2(char a, char b)
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

int esVocal(char a)
{
	if(a == 97 || a == 101 || a == 105 || a == 111 || a == 117 || a == 65 || a == 69 || a == 73 || a == 79 || a == 85)
		return 1;
	return 0;
}

char escoger3(char a, char b, char c)
{

	if(a == 46 || b == 46 || c == 46)
		return 63;
	if(a == 47 || b == 47 || c == 47)
		return 95;
	

	//cuando solo hay letras
	if((esVocal(a) == 1) && (esVocal(b) == 1)&&(esVocal(c) == 1))
	{
		//las 3 son vocales
		return a+1;
	}
	if((esVocal(a) == 1) && (esVocal(b) == 1))
	{
		// a y b son vocales
		return c;
	}
	if((esVocal(a) == 1) && (esVocal(c) == 1))
	{
		// a y c son vocales
		return b;
	}	
	if((esVocal(b) == 1) && (esVocal(c) == 1))
	{
		//b y c son vocales
		return a;
	}
	if((esVocal(a) == 0) && (esVocal(b) == 0)&&(esVocal(c) == 0))
	{
		//todas con consonates
		if(a <= b && a<=c)
			return a;
		if(b <= a && b<=c)
			return b;
		if(c <= a && c<=b)
			return c;
	}
	if((esVocal(a) == 0) && (esVocal(b) == 0)&&(esVocal(c) == 1))
	{
		//a y b son consonantes
		if(a <= b)
			return a;
		return b;
	}
	if((esVocal(a) == 0) && (esVocal(b) == 1)&&(esVocal(c) == 0))
	{
		//a y c son consonantes
		if(a <= c)
			return a;
		return c;
	}
	if((esVocal(a) == 1) && (esVocal(b) == 0)&&(esVocal(c) == 0))
	{
		//c y b son consonantes
		if(b <= c)
			return b;
		return c;
	}
}

char escoger4(char a, char b, char c, char d)
{
	char ganador[4] = {a,b,c,d};
	 
	for(int x = 0; x <= 4; x++)
	{
		if(a < ganador[x])
		{
			a = ganador[x];
		}
			
	}
	return a;
}

void codificar10(char link[50],size_t len)
{
	//dog.gy
	//10 nodos de 1 dato cada uno
	
	char nuevoLink[50];
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
	struct NodoLink *nuevo;
	nuevo=(struct NodoLink*)malloc(sizeof(struct NodoLink));
	if(nuevo==NULL)
		printf("No hay memoria disponible!\n");
	
	for(int x = 0; x< len; x++)
	{
		nuevo->link[x] = link[x];		
		nuevo->linkCodificado[x] = nuevoLink[x];
	}
	nuevo->numeroRegistro = contadorGeneral;
	contadorGeneral++;
	nuevo->size = len;
	nuevo->siguiente=NULL;
	nuevo->anterior = NULL;
	agregarListaGeneral(nuevo);
    //ht_set(ht, nuevo->linkCodificado, nuevo);
	printf("\nLink codificado10: dog.gy/%s\n",ListaGeneral->ultimoNodo->linkCodificado);
}

void codificar20(char link[50],size_t len)
{
	char nuevoLink[50];
	int x = 0;
	int y = 0;
	while(x != len/2)
	{
		//printf("\nUsando %d y %d\n",link[y],link[y+1]);
		nuevoLink[x] = escoger2(link[y],link[y+1]);
					
		x = x+1;
		y = y+2;
	
	}
	if(esPar(len) == 0)
		nuevoLink[x] = link[len-1];
	
	
	struct NodoLink *nuevo;
	nuevo=(struct NodoLink*)malloc(sizeof(struct NodoLink));
	if(nuevo==NULL)
		printf("No hay memoria disponible!\n");

	for(int x = 0; x< len; x++)
	{
		nuevo->link[x] = link[x];		
		nuevo->linkCodificado[x] = nuevoLink[x];
	}
	nuevo->size = len;
	nuevo->numeroRegistro = contadorGeneral;
	contadorGeneral++;
	nuevo->siguiente=NULL;
	nuevo->anterior = NULL;
    //ht_set(ht, nuevo->linkCodificado, nuevo);
	agregarListaGeneral(nuevo);
	printf("\nLink codificado20: dog.gy/%s\n",ListaGeneral->ultimoNodo->linkCodificado);
}

void codificar30(char link[50],size_t len)
{
	char nuevoLink[50];
	int x = 0;
	int y = 0;
	while(x != len/3)
	{
		//printf("\nUsando %d , %d y %d\n",link[y],link[y+1],link[y+2]);
		nuevoLink[x] = escoger3(link[y],link[y+1],link[y+2]);
					
		x = x+1;
		y = y+3;
	
	}
	//if(esPar(len) == 0)
	//	nuevoLink[x] = link[len-1];
	
	struct NodoLink *nuevo;
	nuevo=(struct NodoLink*)malloc(sizeof(struct NodoLink));
	if(nuevo==NULL)
		printf("No hay memoria disponible!\n");
	
	for(int x = 0; x< len; x++)
	{
		nuevo->link[x] = link[x];		
		nuevo->linkCodificado[x] = nuevoLink[x];
	}
	nuevo->size = len;
	nuevo->numeroRegistro = contadorGeneral;
	contadorGeneral++;
	nuevo->siguiente=NULL;
	nuevo->anterior = NULL;
    //ht_set(ht, nuevo->linkCodificado, nuevo);
	agregarListaGeneral(nuevo);
	printf("\nLink codificado30: dog.gy/%s\n",ListaGeneral->ultimoNodo->linkCodificado);
}

char codificar40(char link[50],size_t len)
{
	char nuevoLink[50];
	int x = 0;
	int y = 0;
	while(x != len/4)
	{
		printf("\nUsando %d , %d , %d y %d\n",link[y],link[y+1],link[y+2],link[y+3]);
		nuevoLink[x] = escoger4(link[y],link[y+1],link[y+2],link[y+3]);
					
		x = x+1;
		y = y+4;
	
	}
	//if(esPar(len) == 0)
	//	nuevoLink[x] = link[len-1];
	
	struct NodoLink *nuevo;
	nuevo=(struct NodoLink*)malloc(sizeof(struct NodoLink));
	if(nuevo==NULL)
		printf("No hay memoria disponible!\n");

	for(int x = 0; x< len; x++)
	{
		nuevo->link[x] = link[x];		
		nuevo->linkCodificado[x] = nuevoLink[x];
	}
	nuevo->size = len;
	nuevo->numeroRegistro = contadorGeneral;
	contadorGeneral++;
	nuevo->siguiente=NULL;
	nuevo->anterior = NULL;
    //ht_set(ht, nuevo->linkCodificado, nuevo);
	agregarListaGeneral(nuevo);
	printf("\nLink codificado40: dog.gy/%s\n",ListaGeneral->ultimoNodo->linkCodificado);
}

void codificar(char link[50])
{
	//sacamos su tamano para controles futuros
	size_t len = strlen(link);

	//saber la letra actual
	int x = 0;
	printf("\nEste link es de tamano: %ld",len);
	
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
				codificar30(link,len);
			}
			else	
				if(len <= 40)
				{
					codificar40(link,len);
				}
	
}

void digitarLink()
{
	printf("	  DIGITAR UN LINK");
	//definimos el link de entrada
	char link[50];
	gets();
	printf("\n\nDigite el link: ");
	gets(link);
	
	
	
	//ejemplos de pruebas
	printf("\nLink digitado: %s",link);
	//printf("\nLink digitado espacio 2: %c\n",link[2]);
	codificar(link);
}

void crearlinkTree()
{
	struct NodoLinkTree *nuevo;
	nuevo=(struct NodoLinkTree*)malloc(sizeof(struct NodoLinkTree));
	if(nuevo==NULL)
		printf("No hay memoria disponible!\n");
	
	printf("\n----------Crear Link Tree----------\n\n");
	gets(); //necesario para que funcione, creo
	
	printf("Nombre: ");
	fflush(stdout);
	gets(nuevo->nombre);
	
	printf("Link: ");
	fflush(stdout);
	gets(nuevo->link);	
	
	//struct ListaSimple *ListaGeneral;
	nuevo->Lista = (struct ListaSimple*)malloc(sizeof(struct ListaSimple));
	
	
	verTodo();
	
	int id = 0;
	printf("\nDigite el ID del link que quiere asociar");
	printf("\nDigite 0 para terminar");
	
	do //nuevo es el nodo tipo LinkTree
		//tmp es el nodo link que coincide con el id
	{
		printf("\nID de link: ");
		scanf("%d",&id);
		
		struct NodoLink *tmp;
		tmp=(struct NodoLink*)malloc(sizeof(struct NodoLink));
		if(tmp==NULL)
			printf("No hay memoria disponible!\n");
		
		tmp = ListaGeneral->primerNodo;
		
		while(tmp != NULL)
		{	
			
			if(id == tmp->numeroRegistro)
			{	
				if(nuevo->Lista->primerNodo==NULL)
				{   
					nuevo->Lista->primerNodo=tmp;
					nuevo->Lista->ultimoNodo=tmp;
					printf("\nPrimer link agregado\n");
					break;
				}
				else
				{
					tmp->anterior = nuevo->Lista->ultimoNodo;
					nuevo->Lista->ultimoNodo->siguiente=tmp;
					nuevo->Lista->ultimoNodo=tmp;
					printf("\nLink agregado\n");
					tmp->anterior = NULL;
					break;
				}
			}
			tmp = tmp->siguiente;		
		}
		
		
	}while(id !=0);
}

void verTodo()
{
	printf("		VER TODO\n\n");
	struct NodoLink *tmp;
	tmp=(struct NodoLink*)malloc(sizeof(struct NodoLink));
	if(tmp==NULL)
		printf("No hay memoria disponible!\n");
	tmp = ListaGeneral->primerNodo;
	while(tmp != NULL)
	{
		printf("\n\tLink: %s",tmp->link);
		printf("\n\tLink codificado: dog.gy/%s",tmp->linkCodificado);
		printf("\n\tNumero de registro: %d",tmp->numeroRegistro);
		tmp = tmp->siguiente;
		printf("\n_____________________________________________\n");
	}
}


int main()
{
	
	//struct ListaSimple *ListaGeneral;
	ListaGeneral = (struct ListaSimple*)malloc(sizeof(struct ListaSimple));
	
		
	
	int opcion;
	do
	{	printf("\n\n_____________________________________________");
		printf("\n\t        Menu\n");
		printf("\n\t1.Insertar un link");
		printf("\n\t3.Ver todos los links almacenados");
		printf("\n\t6.Crear un linkTree");
		printf("\n\t10.Salir");
		printf("\n\tDigite una opcion: ");
		scanf("%d",&opcion);
	 	printf("\n_____________________________________________\n\n");
		switch(opcion)
		{
			case 1:
				digitarLink();
				break;
			case 3:
				verTodo();
				break;
			case 6:
				crearlinkTree();
				break;
		}
	}while(opcion != 10);
}//cierre del main
