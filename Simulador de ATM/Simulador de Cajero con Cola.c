#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*  // CONSIGNA //
Desarrollar un programa para la simulacion de un cajero automatico: 
Se sabe que llegan clientes a la puerta del cajero cada 2 o 3 minutos, y que cada cliente tarda entre 2 y 4 minutos para ser atendido

Obtener la siguiente informacion:

1) Cantidad de clientes que se atendieron en 10 horas
2) Cantidad de clientes que hay en cola despues de 10 horas
3) Hora de llegada del primer cliente que que no es atendido luego de 10 horas (osea la primer persona en cola desp de las 10 hrs)
*/

struct nodo {

    int info;           // minuto en el que llego la persona
    struct nodo *sig;

};

struct nodo *raiz = NULL;   // principio lista
struct nodo *fondo = NULL;  // final de la lista

void insertar(int x){

    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));
    nuevo->info = x;

    nuevo->sig = NULL;

    if (raiz == NULL) {         

        raiz = nuevo;           
        fondo = nuevo;
    }
    else {                      

        fondo->sig = nuevo;     
        fondo = nuevo;          

    }
}

int eliminar(){

    if (raiz != NULL) {

        int informacion = raiz->info;   

        struct nodo *borra = raiz;

            if (raiz == fondo) {  

                raiz = NULL; 
                fondo = NULL;

            }
            else {

                raiz = raiz->sig;       

            }
    free(borra);
    return informacion;
    }
    else{
        printf("La cola esta vacia! \n");
    }
}

void imprimir(){

    struct nodo *recorre = raiz;
    printf("Listado de los elementos de la cola: \n");

    while  (recorre != NULL) {

        printf(" %d ", recorre->info);
        recorre = recorre->sig;
    }
    printf("\n");
}

int cantidad(){

    struct nodo *recorre = raiz;
    int cant = 0;

    while (recorre != NULL) {

        cant++;
        recorre = recorre->sig;

    }
    return cant;
}

void simulacion() {

    srand(time(NULL));  // Con esta funcion e invocando el rand(), nos dara un nro aleatorio cada vez

    int estado = 0;     // Estado del cajero: 0 es desocupado, 1 es ocupado

    int llegada = rand()%2 + 2;   // El resto de dividir rand entre 2, puede generar un 1 o un 0, que sumandole 2, obtenemos 2 o 3 minutos!!

    int salida = -1;            // Indica cuando va a salir una persona
    int cantAtendidas = 0;      // Contador de cantidad de gente atentida

    // Ahora viene la estructura de la simulacion, donde en cada minuto, pueden suceder dos cosas; o que entre gente o que se vaya

    for (int minuto = 0; minuto < 600; minuto ++) {     // ALGORITMO (600 MIN son 10 horas)

        if (llegada==minuto) {                      // Cuando alguien llego al cajero..

            if (estado == 0) {                      // Si viene alguien al cajero y ESTA DESOCUPADO:

                estado = 1;                         // OCUPAMOS EL CAJERO
                salida = minuto + 2 + rand() % 3;   // Minuto actual + 2 + el resto de un nro aleatorio div entre 3, osea, de 2 a 4 minutos
                                     // 0, 1 o 2
                                                
            }
            else {                                  // Si viene alguien al cajero, y ESTA OCUPADO:

                insertar(minuto);                   // Guardamos en cola el minuto en el cual empezo a esperar el usuario


            }
            llegada = minuto + 2 + rand() % 2;      // De esta manera, cada dos vueltas (min), va a llegar una nueva persona constamente
        }

        ///////////////////////////////////////////////////////////////////////////////////////////

        if (salida == minuto) {     // Cuando alguien se va del cajero..

            estado = 0;             // Desocupamos el cajero..
            cantAtendidas++;
            
            if (raiz != NULL) {     // Si no hay nadie esperando..

                eliminar();

                estado = 1;         // Ocupado
                
                salida = minuto + 2 + rand() % 3;

            }
        }
    }
    printf("Cantidad de Personas Atendidas en 10 Horas: %d\n", cantAtendidas);
    printf("Cantidad de Personas que quedaron en Cola: %d\n", cantidad());
    printf("Minuto de llegada del primer usuario en cola despues de 10 horas: %d\n", eliminar());
}

int main() {

simulacion();

return 0;

}