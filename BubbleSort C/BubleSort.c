#include <stdio.h>

void carga(int array[5]) {

    for (int i=0; i<5; i++) {

    printf("Ingrese un elemento: ");
    scanf("%d", &array[i]);

    }

    for (int i=0; i<5; i++) {

    printf("%d ", array[i]);
    }

}

void sort(int array[5]) {

    int aux;

    for (int j=0; j<4; j++) {

        for (int i=0; i<4; i++) {

            if (array[i] > array[i+1]) {

                aux = array[i];             // guardamos en aux el mayor
                array[i] = array[i+1];      // sobrescribimos el menor valor en la posicion i
                array[i+1] = aux;           // aux contiene a array[i], el elemento mayor! que se almacena en la proxima ubicacion

            }

        }

    }

    printf("El array ordenado: \n");

    for (int i=0; i<5; i++) {

    printf("%d ", array[i]);

    }

}
    

int main () {

int array[5];

carga(array);

printf("\n");

sort(array);

return 0;

}