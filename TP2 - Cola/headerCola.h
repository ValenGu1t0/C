#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definicion de Nodo, Raiz y Fondo*/
struct nodo
{
    int info;
    struct nodo *sig;
};

struct nodo *root = NULL;       // Puntero auxiliar que apuntara al frente de la Cola

struct nodo *bottom = NULL;     // Puntero auxiliar que apuntara al fondo de la Cola

/* Funcion Menú (Insertar / Extraer / Leer / Liberar) */
char menuOpciones() {

    char opcion;

    printf("\n");
    printf("Elementos de la Pila: [I]nsertar / [E]liminar / [L]eer / [C]lean Cola: ");
    scanf(" %c", &opcion);

    switch(opcion) {

        case 'I':   inserta();
                    break;

        case 'E':   printf("\n");
                    printf("Acaba de eliminar el nodo con informacion: %d\n", eliminar());
                    break;

        case 'L':   printf("\n");
                    imprimir();
                    break;

        case 'C':   printf("\n");
                    libera();
                    break;
        }
        menuOpciones();
}

/* Funcion Insertadora de Nodos en Pila */
void inserta() {         

    struct nodo *nuevo;                     // se declara un nuevo nodo apuntado por nuevo
    nuevo = malloc(sizeof(struct nodo));    // se reserva espacio para el nodo que apunta *nuevo, ahora si en la memoria hasta que se libere

    printf("Ingrese el dato: ");
    scanf("%d", &nuevo->info);

    nuevo->sig = NULL;                      // El nuevo nodo apuntara a NULL, donde raiz

    if (root == NULL) {                     // SI NO HAY NODOS..

        root = nuevo;           // Raiz apunta al nuevo y unico nodo
        bottom = nuevo;         // Bottom (Fondo) tambien apuntará al nuevo y unico nodo 

    }
    else {                                  // SI YA HAY NODOS..

        bottom->sig = nuevo;    // Ahora el *sig del nodo previo apunta al nuevo nodo { [2oN] -> [1erN] }    
        bottom = nuevo;         // Y el fondo apunta al nuevo y ultimo nodo

    }
    menuOpciones();
}

/* Funcion Extractora de Nodos en Pila */
int eliminar() {

    if (root != NULL) {                     /* Si hay elementos en la Cola: */

        int informacion = root->info;       // Guardamos la info del nodo por borrar

        struct nodo *borra = root;          // Creamos un nuevo * que apunta a donde raiz, osea el primer nodo que se ingreso en la Cola

        if (root == bottom) {                // SI SOLO HAY 1 NODO..

            root = NULL;                    // Ambos auxiliares vuelven a apuntar a NULL
            bottom = NULL;                   // Para que cuando se elimine el UNICO nodo, estas vuelvan al inicio NULL
        }
        else {                              // SI HAY MAS DE UN NODO..
            root = root->sig;               // La raiz apunta al nodo siguiente al que vamos a borrar, osea al mas "nuevo"
        }

        free (borra);                       // Eliminamos
        return informacion;                 // Devolvemos info borrada
    }
    else {                                  /* Y si no habian elementos en cola.. */    
        printf("La cola esta vacía!\n");    
    }
    menuOpciones();
}

/* Funcion Impresora de Nodos en Pila */
void imprimir() {

    if (root != NULL) {

    struct nodo *reco = root;       // Definimos un punt auxiliar recoRRER que va a ir viendo cada valor que apunto raiz desdeel comienzo hasta NULL

    printf("Pila Completa en Orden de Ingreso: ");

    while (reco != NULL) {              // Mientras reco sea distinto de cola vacia..

        printf(" %d -> ", reco->info);   // Muestra la informacion que llevaba cada puntero
        reco = reco->sig;               // Asi avanza sobre los nodos el puntero recoRRER
    }
    printf("\n");
    }
    else {
        printf("\n");
        printf("No hay elementos en la Pila!\n");
    }
}

/* Funcion Liberadora de la Cola (Elimina todos los Nodos)*/
void libera(){

    if (root != NULL) {

    struct nodo *recorre = root;
    struct nodo *borra;

    while (recorre != NULL) {

        borra = recorre;
        recorre = recorre->sig;
        free(borra);
    }
    printf("La Cola fue liberada, no quedan elementos en ella.\n");
    }
    else {

        printf("No quedaron elementos por limpiar!! \n");

    }


}