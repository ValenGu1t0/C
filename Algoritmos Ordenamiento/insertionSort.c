#include <stdio.h>

int main() {


    int array[10] = {5, 3, 1, 7, 4, 8, 10, 6, 9, 2};

    int save = 0;   // var pivot


    for (int i=0; i < 10; i++) {

        printf("%d ", array[i]);

    }

    // Insertion Sort

    for (int i=0; i < 10; i++) {

        for (int j=0; j < i; j++) {

            if ( array[i] < array[j] ) {        // Si cambiamos a ( array[i] > array[j] )  lo ordena descendiente

                save = array[i];

                array[i] = array[j];

                array[j] = save;

            }
        }
    }

    printf("\n");

    // Volvemos a mostrar el array ordenado

    for (int i=0; i < 10; i++) {

        printf("%d ", array[i]);

    }

    return 0;
}