#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct nodo {

    char nombre_legisladores[15];   // Hasta 15 char por las dudas
    char voto;                      // F ( FAVOR) / C (CONTRA)
    struct nodo* Siguiente;

} lista;

typedef struct lista *pnodo;
pnodo primero, ultimo;

char nombre[15];
char voto;
char F, C;

void menu();

void inserta (char nombre[25], char, lista **l);

void suprime(char nombre[25], char voto,lista **l);

void escribe (lista *l, char);

void miembro(char nombre[25],char voto) ;

void mostrar();

void mostrarLista(lista *l);

void convertirAMayusculas(char *cadena) {
    int i = 0;
    while (cadena[i] != '\0') {
        cadena[i] = toupper(cadena[i]);
        i++;
    }
}