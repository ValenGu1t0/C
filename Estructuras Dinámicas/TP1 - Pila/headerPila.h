#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definicion de Nodo y Raiz
struct nodo
{
    int info;               // lleva la data del nodo
    struct nodo *sig;       // apuntador del nodo
};

struct nodo *root = NULL;

// Funcion Menú (Insertar / Extraer / Leer)
char menuOpciones() {

    char opcion;

    printf("\n");
    printf("Elementos de la Pila: [I]nsertar / [E]liminar / [L]eer / [C]ontar / [N]odo: ");
    scanf(" %c", &opcion);

    switch(opcion) {

        case 'I':   inserta();
                    break;

        case 'E':   printf("\n");
                    printf("Acaba de eliminar el nodo con informacion: %d\n", eliminar());
                    break;

        case 'L':   imprimir();
                    break;

        case 'C':   printf("\n");
                    cuentaNodos();
                    break;
        case 'N':   printf("\n");
                    leeNodo();
                    break;
        
        }
        menuOpciones();
}

// Funcion Insertadora de Nodos en Pila

void inserta() {         

    struct nodo *nuevo;                     // se declara un nuevo nodo apuntado por nuevo
    nuevo = malloc(sizeof(struct nodo));    // se reserva espacio para el nodo que apunta *nuevo, ahora si en la memoria hasta que se libere
    
    printf("Ingrese el dato: ");
    scanf("%d", &nuevo->info);

    if (root == NULL) {     // SI NO HAY NODOS

        root = nuevo;       // Raiz apunta al nuevo nodo
        nuevo->sig = NULL;  // El nuevo y ultimo nodo apunta al final de la cola, pila a NULL

        // IMPORTANTE: el nodo tiene un apuntador, *sig, que HAY QUE USAR PARA APUNTAR justamente
        // IMPORTANTE: tenemos la raiz, que es una variable global apuntadora, y otra el nodo, que posee campos como info y el APUNTADOR, que hay que aclarar a donde apunta

    }
    else {                  // SI YA HAY NODOS

        nuevo->sig = root;       // el nuevo nodo apunta a donde apuntaba la raiz (el nodo preexistente en la pila)
        root = nuevo;       // ademas, la raiz vuelve a apuntar al nuevo nodo ingresado

    }
    menuOpciones();

}

// Funcion Extractora de Nodos en Pila

int eliminar() {

    if (root != NULL) {                     // SI LA PILA TIENE ELEMENTOS ADENTRO: 

        int informacion = root->info;       //GUARDAMOS LA INFO que llevaba el ultimo nodo que ingreso, el mismo al que apunta raiz siempre
                                            // raiz->info puede almacenar la informacion del nodo al que esta apuntando
       
        struct nodo *borra = root;          // creamos un nuevo apuntador que eliminara lo que apunta raiz, osea el ultimo nodo ingresado

        root = root->sig;                   // Ahora raiz se sobrescribe a si misma con el nodo al que apuntaba el nodo borrado, el siguiente en la lista

        free(borra);                      // Y aca se elimina de la memoria el nodo al que apuntaba raiz mediante *borra

        return informacion;

        printf("\n");
        menuOpciones();

    } else {           // SI LA PILA SI ESTA VACIA:

    printf("No hay elementos en la Pila!\n");   // Osea, la lista esta vacia! El nro que se use no debe estar nunca en la info de algun nodo
    menuOpciones();

    }
}

// Funcion Impresora de Nodos en Pila

void imprimir() {

    if (root != NULL) {

    struct nodo *reco = root;       // Definimos un punt auxiliar recoRRER que va a ir viendo cada valor que apunto raiz desdeel comienzo hasta NULL

    printf("\n");
    printf("Pila Completa en Orden de Ingreso: ");

    while (reco != NULL) {          // Mientras reco sea distinto de cola vacia..

        printf("%d ", reco->info);   // Muestra la informacion que llevaba cada puntero

        reco = reco->sig;           // Asi avanza sobre los nodos el puntero recoRRER
    }
    printf("\n");

    }
    else {
        
        printf("\n");
        printf("No hay elementos en la Pila!\n");
    }
}

// Funcion Contadora de Nodos en Pila

int cuentaNodos() {

    struct nodo *recorre = root;

    int contador = 0;

    if (root != NULL){

        while (recorre != NULL) {

        contador++;
        recorre = recorre->sig;
    }
    printf("La lista cuenta actualmente con %d nodos\n", contador);
    //return contador;
    }
    else {

        printf("La lista esta vacia.\n");
    }
}

// Lee y devuelve la Data de un Nodo sin eliminarlo

int leeNodo() {

    if (root != NULL) {

        printf("El siguiente nodo lleva cargado el dato: %d\n", root->info);
    }
    else {

        printf("La lista esta vacia! No hay data que mostrar..\n");
    }
}