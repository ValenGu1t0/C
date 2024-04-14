#include <stdio.h>
#include "Privitera_Archivos.h"

int main() {

    printf("\n VOTACION LEGISLADORES \n");
    menu();

    return 0;
}

void menu() {

    lista *primero = NULL;  // RAIZ
    char opcion = ' ';
    while (opcion != 'E')   // FINAL DEL ARCHIVO
    {
        printf("\nI = Insertar nombre y voto del legislador.");
        printf("\nL = Corrobora si el legislador ya se encuentra en algun archivo.");
        printf("\nM = Muestra el historial de votos y transcribe los de esta sesion.");
        printf("\nS = Recibe nombre, voto y lo elimina de la lista.");
        printf("\nH = Para mostrar lista en esta sesion de sistema.\n\n");
        opcion = toupper(getchar());
        getchar();
        switch (opcion)
        {
        case 'I':
            printf("Ingrese el nombre del legislador: ");
            scanf("%s", nombre);  
            
            convertirAMayusculas(nombre);   // Transforma nombre de legislador a mayus

            getchar();
            printf("\nIngrese el voto para %s (Favor: 'F', Contra: 'C'): ", nombre);
            scanf("%c", &voto);
            getchar();
            voto = toupper(voto);
            while (voto != 'F' && voto != 'C')  // Verificamos que el char sea el indicado
            {
                printf("Voto inválido. Intente nuevamente: ");
                scanf(" %c", &voto);
                getchar();
                voto = toupper(voto); 
                
            }
            inserta(nombre, voto, &primero);    // Funcion que graba nombre y voto en archivo
            break;

        case 'M':
            escribe (primero,voto);
            mostrar();
            break;

        case 'L':
            miembro(nombre,voto);
            break;

        case 'S':
            printf("\nIngrese legislador:");
            scanf("%s",nombre);

            convertirAMayusculas(nombre);

            getchar();
            printf("\nIngrese voto:");
            scanf(" %c",&voto);
            voto = toupper(voto);
            getchar();
            suprime(nombre, voto,&primero);
            break;
            
        case 'H':
            mostrarLista(primero);
            break;
        }
    }
}

void inserta (char nombre[25], char voto, lista **l) {   // Inserta legisladores y sus votos en los achivos.

    lista *nuevo_Nodo = (lista *)malloc(sizeof(lista));
    strncpy(nuevo_Nodo->nombre_legisladores, nombre, 25);
    nuevo_Nodo->voto = voto;
    nuevo_Nodo->Siguiente = *l;
    *l = nuevo_Nodo;
}

void miembro (char nombre[25],char voto) {   // Recibe nombre, voto y dice si ya esta en el archivo o no.
    bool encontrado;
    char lineas_de_txt[100];

    printf("\nIngrese el nombre:  ");
    scanf("%s",nombre);
    getchar();
    printf("\nIngrese el voto:  ");
    scanf(" %c",&voto);
    getchar();

    FILE *archivo_buenos = fopen("chicos_buenos.txt", "r");
    FILE *archivo_malos = fopen("chicos_malos.txt", "r");

        if (archivo_buenos == NULL || archivo_malos == NULL) {      // Si NO existen los archivos...
        printf("\nNo existen los archivos\n");
        } 
        else {                                                      // Si encuentra los archivos...

            while (fgets(lineas_de_txt, sizeof(lineas_de_txt), archivo_buenos) != NULL) {

                if (strstr(lineas_de_txt, nombre) != NULL){                          // Primera coincidencia
            printf("\n ¡%s YA SE ENCUENTRA en chicos buenos!\n", nombre);
            encontrado = true;
            break;                                                  // Finalizamos verificador de legisladores
        }
    }

    if (!encontrado) {              // Si no fue encontrado el legislador...
        
        rewind(archivo_malos);      // Volvemos al principio del archivo para su analisis
        
        while (fgets(lineas_de_txt, sizeof(lineas_de_txt), archivo_malos) != NULL) {

            if (strstr(lineas_de_txt, nombre) != NULL) {
                printf("\n ¡%s YA SE ENCUENTRA  en chicos malos!\n", nombre);
                encontrado = true;
                break;
            }
        }
    }

    if (!encontrado) {

        printf("¡%s NO ESTA en ninguna lista!\n", nombre);
    }

    fclose(archivo_buenos);
    fclose(archivo_malos);
    }
}

void mostrar() {   // Lee el archivo y devuelve la informacion 

    FILE *archivoBuenos;
    FILE *archivoMalos;
    char nombre_leido [25];

    archivoBuenos = fopen("chicos_buenos.txt", "r");
    archivoMalos = fopen("chicos_malos.txt", "r");

    if (archivoBuenos != NULL && archivoMalos != NULL) {
        printf("\nA favor\n");      
        while (fscanf(archivoBuenos, "%s", nombre_leido) == 1) {

            printf("Legislador: %s\n", nombre_leido);
        }  
        printf("\nEn contra\n");
        
        while (fscanf(archivoMalos, "%s", nombre_leido) == 1) {

            printf("Legislador: %s\n", nombre_leido);
        }
        
        fclose(archivoBuenos);
        fclose(archivoMalos);
    }
    else {

        printf("No existen los archivos.\n");
    }
}

void escribe (lista *l, char voto) {  // Imprime las listas de los legisladores con sus votos a favor o en contra

    FILE *archivoBuenos = fopen("chicos_buenos.txt","a");
    FILE *archivoMalos = fopen("chicos_malos.txt","a");
    
        if (voto == 'F') {
            fprintf(archivoBuenos, "%s\n", l->nombre_legisladores);     // Lee el txt
            l = l->Siguiente;                                           // Avanza al proximo nombre
        }
        else 
        
            if (voto == 'C') {
            fprintf(archivoMalos, "%s\n", l->nombre_legisladores);      // Igual para votos en contra
            l = l->Siguiente;
        }
        
    fclose(archivoBuenos);
    fclose(archivoMalos);
}

void suprime (char nombre[25], char voto, lista **l) {  // Elimina legisladores de la lista

    lista *actual = *l;
    lista *anterior = NULL;

    // Recorre lista
    while (actual != NULL) {
        if (strcmp(actual->nombre_legisladores, nombre) == 0 && actual->voto == voto) {
            // El miembro coincide, eliminarlo de la lista
            if (anterior == NULL) {
                // El miembro a eliminar es el primer nodo de la lista
                *l = actual->Siguiente;
            } 
            else {
                // El miembro a eliminar está en medio o al final de la lista
                anterior->Siguiente = actual->Siguiente;
            }
            free(actual);
            printf("¡%s eliminado de la lista!\n", nombre);
            return;
        }

        anterior = actual;
        actual = actual->Siguiente;
    }

    // Si se llega a este punto, el miembro no se encontró en la lista
    printf("¡%s no encontrado en la lista!\n", nombre);
}

void mostrarLista(lista *l) {   // Imprime por pantalla el listado completo de legisladores y votos

    if (l == NULL) {
        printf("\n¡La lista en este sistema esta vacia!\n");
        return;
    }

    lista *nodoActual = l;

    while (nodoActual != NULL) {

        printf("\nNombre: %s", nodoActual->nombre_legisladores);
        printf(", Voto: %c\n", nodoActual->voto);
        printf("-----------------------\n");

        nodoActual = nodoActual->Siguiente;
    }
}