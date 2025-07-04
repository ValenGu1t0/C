#include <stdio.h>


/* 1. a) Escribir una función que ordene un array de n números enteros 
(n es un unsigned ingresado) mediante el algoritmo quicksort. */


// Función para intercambiar dos elementos
void intercambiar(int* a, int* b) {
    
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Función que encuentra el pivote y divide el array
int particion(int arr[], int bajo, int alto) {

    int pivote = arr[alto]; // Tomamos el último elemento como pivote
    int i = (bajo - 1); // Índice del menor elemento

    for (int j = bajo; j <= alto - 1; j++) {

        if (arr[j] <= pivote) {

            i++; 
            intercambiar(&arr[i], &arr[j]);
        }
    }
    intercambiar(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

// Función que implementa el algoritmo Quicksort
void quickSort(int arr[], int bajo, int alto) {

    if (bajo < alto) {
        // `pi` es el índice del pivote
        int pi = particion(arr, bajo, alto);

        // Ordenamos los elementos antes y después de la partición
        quickSort(arr, bajo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

// Función para imprimir el array
void imprimirArray(int arr[], unsigned n) {

    for (unsigned i = 0; i < n; i++) {

        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {

    unsigned n;
    
    printf("Ingrese el tamaño del array: ");
    scanf("%u", &n);

    int arr[n]; // Array de tamaño n

    printf("Ingrese los elementos del array:\n");

    for (unsigned i = 0; i < n; i++) {

        scanf("%d", &arr[i]);
    }

    printf("Array original: ");
    imprimirArray(arr, n);

    // Llamada a quickSort
    quickSort(arr, 0, n - 1);

    printf("Array ordenado: ");
    imprimirArray(arr, n);


return 0;

}

