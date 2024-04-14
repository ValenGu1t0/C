#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerKruskal.h"


int main() {

    printf("\n------------------------------------\n");
    printf("       Privitera, Valentino     ");
    printf("\n------------------------------------\n");
    printf("  < -- Algoritmo de Kruskal -- > \n");
    printf("------------------------------------\n");
    printf("Trabajaremos un Grafo de %i vertices!\n", VERTICES);
    printf("------------------------------------\n");

    printf("\nUd. debera ingresar manualmente los pesos de las aristas entre los vertices que forman el grafo.\n");
    printf("El programa tomara el grafo y devolvera el listado de las aristas que forman su arbol de expansion minimo.\n");


    int M_Costos[VERTICES][VERTICES] = {0};     // Matriz para almacenar los costos de aristas entre vertices
    rama *arbol = NULL;                         // Creamos la raiz del arbol apuntando a NULL

    printf("\nIngrese el costo de arista entre vertices... \n"); 

    // Mediante dos For, rellenamos la matriz con los costos, y a medida que avanza va cambiando los vertices tmb

    for (int i = 0; i <= VERTICES -1; i++) {

        for (int j = i + 1; j <= VERTICES -1; j++) {

            printf("%i", i); 
            printf(" y "); 
            printf("%i", j); 
            printf(": ");

            // Validamos que sea un costo > 0: 
            int ingreso = 0, salir = 0;

            while (salir == 0) {

                scanf("%d", &ingreso);

                if (ingreso <= 0) {

                    printf("Ingreso invalido.\n");
                    printf("Ingrese nuevamente: ");
                
                } else {

                    salir = 1;
                }
            }
            M_Costos[i][j] = ingreso;
        }
    }

    // La mitad inferior de la diagonal de la matriz;
    // Osea que vamos a cargar una arista que cumpla lo siguiente:
    // - No aparecio (incluye las aristas que tienen el origen y el final invertidos)
    // - El incio de la arista no coincide con el final de la misma

    for (int i = 0; i <= VERTICES -1; i ++) {

        for (int j = i + 1; j <= VERTICES -1; j++) 
        {
            if (M_Costos [i][j] != 0) {

                inserta(i, j, M_Costos[i][j], &arbol);  // Inserto en cola prioridad si cumple con los requisitos.
            }
        }
    }

    // Una vez poseemos nuestros vertices y aristas cargados en la lista enlazada, procedemos a llamar al algoritmo

    kruskal(&arbol);    // Llamamos al Algoritmo de Kruskal
    printf("\nA continuacion se detalla el arbol de expansion minimo obtenido: ");
    lista(arbol);       // Listamos el arbol de expansion minimo 
    return 0;
    // Termina el programa.
}

// Funcion que con los vertices de una arista y su peso, inserta la arista en la lista enlazada:
void inserta(int vA, int vB, int costo, rama **arbol) {

    rama *nuevaRama = (rama*) malloc(sizeof(rama));     // Reservamos espacio para un nuevo vertice

    arista nuevaArista; 
    nuevaArista.u = vA;             // Pasamos los campos de posicion, y coste
    nuevaArista.v = vB;
    nuevaArista.costo = costo;

    nuevaRama->a = nuevaArista;  
    nuevaRama->sig = NULL;          
    
    if (*arbol == NULL) {       // Si el grafo esta vacio..

        *arbol = nuevaRama;

    } else {                    // Si no lo esta, ingresamos nuevo vertice apuntando al previo

        rama *aux = *arbol;

        while (aux -> sig!= NULL) {

            aux = aux -> sig;
        }
        aux->sig = nuevaRama;
    }
}

// Funcion Algoritmo de Kruskal
void kruskal(rama **arbol) {

    int comp_n, comp_siguiente, comp_u, comp_v;
    tipo_elemento u, v;
    conjunto_CE *componentes = (conjunto_CE*) malloc(sizeof(conjunto_CE));
    rama *resultado = NULL;
    comp_siguiente = 0;
    comp_n = VERTICES;
    arista arista_minima;

    // Inicialmente, por cada vertice, generamos una nueva componente de un unico vertice y sin siguiente
    for (int i = 0; i<VERTICES; i++) {

        inicial(comp_siguiente, i, componentes);
        comp_siguiente++;
    }

    while (comp_n > 1) {
    
        arista_minima = sacar_min(arbol);
        u = arista_minima.u;
        v = arista_minima.v;
        comp_u = encuentra(u, componentes);
        comp_v = encuentra(v, componentes);

        if (comp_u != comp_v) {

            combina(comp_u, comp_v, componentes);
            comp_n--;
            inserta(arista_minima.u, arista_minima.v, arista_minima.costo, &resultado);
        }
    }

    // Se libera el arbol original
    rama *aux = *arbol;

    while(aux != NULL) {
        *arbol = aux;
        aux = (*arbol)->sig;
        free(*arbol);
    }

    // Se reasigna al nuevo reusltado del kruskal.
    *arbol = resultado;
}

// Funcion que recibe un nombre para una componenete y un nombre de vertice y lo agrega a el conjunto: 
void inicial(tipo_nombre componente, tipo_elemento x, conjunto_CE * conjunto) {

    /* 
    La idea de esta funcion es que vos primero metes a todos los vertices en el conjunto y, 
    como todavia no los conectaste, entonces el vertice suelto es una componente en si mimso.
    */

    (conjunto->nombres)[x].nombre_conjunto = componente;
    (conjunto->nombres)[x].siguiente_elemento = -1;     // Apenas se agrega la componente al grafo solo tiene un vertice y no existe el siguiente
    (conjunto->encabezamientos_conjunto)[componente].cuenta = 1;
    (conjunto->encabezamientos_conjunto)[componente].primer_elemento = x;
}

// Funcion que dada una lista enlazada de aristas, devuelve la arista de menor costo por cada tramo:
arista sacar_min(rama **arbol) {

    arista costo_min = (*arbol)->a;     // Buscamos la primer arista de la lista
    rama * auxiliar = *arbol;

    while (auxiliar != NULL) {

        if (auxiliar->a.costo < costo_min.costo) {
            costo_min = auxiliar->a;
        }
        auxiliar = auxiliar->sig;
    }
    auxiliar = *arbol;

    // Ahora buscamos el elemento previo a la arista de menor costo
    // En caso de que el primer elemento sea el de menor costo lo borramos sin realizar otro cambio

    if (auxiliar->a.costo == costo_min.costo) {
        *arbol = (*arbol)->sig;
        free(auxiliar);             // Contiene al primer elemento
    
    } else {

        while (auxiliar->sig->a.costo != costo_min.costo) {

            auxiliar = auxiliar->sig;
        }
        rama * borrar = auxiliar->sig;
        auxiliar->sig = auxiliar->sig->sig;     // El elemento previo del elemento a borrar lo anexamos con el siguiente al que se va a borrar
        free(borrar);
    }
    return costo_min;
}

// Funcion que recibe un vertice y un conjunto de componentes de aristas y devuelve el nombre de la componente a la que pertenece el vertice
tipo_nombre encuentra(int vertice, conjunto_CE *conjunto) {

    return ((conjunto->nombres)[vertice].nombre_conjunto);
}

/* Funcion que recibe los nombres de dos componenetes que pertencen a el tercer conjunto dado y
combina estas dos componenetes (el nombre de la nueva componente es el de la mayor de las dos fusionadas) */
void combina(tipo_nombre comp_A, tipo_nombre comp_B, conjunto_CE * conjunto) {

    int cant_a = (conjunto->encabezamientos_conjunto)[comp_A].cuenta;
    int cant_b = (conjunto->encabezamientos_conjunto)[comp_B].cuenta;

    if (cant_a > cant_b) {      // si la componente a tiene mas elementos que la componente b entonces mete el contenido de la b en la a

        fusionar(comp_A, comp_B, conjunto);

    } else {

        fusionar(comp_B, comp_A, conjunto);
    }
}

/* Funcion que dadas dos componentes de un conjunto, convierte todos los vertices de la segunda componente en vertices de la primera
Sobretodo evita reusar muchas veces la funcion combina() */
void fusionar(tipo_nombre comp_A, tipo_nombre comp_B, conjunto_CE *conjunto) {

    tipo_elemento elem = (conjunto->encabezamientos_conjunto)[comp_B].primer_elemento;

        // Mientras no se haya encontrado el último elemento de la lista B

        while((conjunto->nombres)[elem].siguiente_elemento != -1) {

            (conjunto->nombres)[elem].nombre_conjunto = comp_A;
            elem = (conjunto->nombres)[elem].siguiente_elemento;
        }

        // Ahora elem contiene el ultimo elemento de la nueva componente
        (conjunto->nombres)[elem].nombre_conjunto = comp_A;
        (conjunto->nombres)[elem].siguiente_elemento = (conjunto->encabezamientos_conjunto)[comp_A].primer_elemento;
        (conjunto->encabezamientos_conjunto)[comp_A].primer_elemento = (conjunto->encabezamientos_conjunto)[comp_B].primer_elemento;
        (conjunto->encabezamientos_conjunto)[comp_A].cuenta += (conjunto->encabezamientos_conjunto)[comp_B].cuenta;
}

/* Funcion que imprime y lista los vertices y los costos minimos necesarios para realizar el arbol de expansion minimo entre ellos */
void lista(rama *arbol) {

    printf("\n");
    rama *aux = arbol;
    while(aux != NULL) {        // Mientras la cola no este vacia..

        //printf("Arista: %i - %i: %i)", aux->a.u, aux->a.v, aux->a.costo);
        printf("(");
        printf("Arista: %i", aux->a.u);
        printf(" - ");
        printf("%i", aux->a.v);
        printf(" : ");
        printf("%i", aux->a.costo);
        printf(")");printf(" -> ");
        aux = aux -> sig;
    } 
    printf("(Fin)\n");
    printf("\n");
}
