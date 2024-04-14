#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Matriz Ideal, osea la configuracion final en orden creciente para referenciar en cada movimiento
int matriz_ideal[4][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,0}};


// Coleccion de Matrices con Cofiguraciones Resolvibles

// x = columnas
// y = filas

/*                         y1              y2             y3              y4           */
/*                     x0 x1 x2 x3                                                     */
int matriz_1[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 0}, {13, 14, 15, 12}};   // facilita de prueba

int matriz_2[4][4] = {{3, 0, 12, 5}, {7, 8, 13, 11}, {6, 9, 15, 1}, {14, 10, 4, 2}};   // x=1 y=0

int matriz_3[4][4] = {{13, 1, 10, 2}, {9, 7, 4, 0}, {6, 3, 14, 15}, {5, 11, 8, 12}};

int matriz_4[4][4] = {{9, 0, 3, 11}, {12, 6, 5, 15}, {13, 14, 1, 4}, {10, 8, 2, 7}};

int matriz_5[4][4] = {{9, 7, 15, 2}, {4, 6, 0, 10}, {14, 11, 1, 8}, {3, 5, 13, 12}};    // x=2 y=1 

int matriz_6[4][4] = {{10, 14, 4, 8}, {1, 11, 3, 12}, {9, 0, 7, 2}, {13, 5, 6, 15}};    // x=1 y=2

int matriz_7[4][4] = {{6, 8, 12, 13}, {1, 5, 9, 15}, {3, 14, 4, 11}, {0, 7, 2, 10}};    // x=0 y=3

int matriz_8[4][4] = {{11, 8, 0, 9}, {3, 6, 5, 1}, {10, 4, 14, 15}, {12, 7, 13, 2}};    // x=2 y=0

int matriz_9[4][4] = {{1, 9, 11, 6}, {3, 7, 13, 14}, {0, 2, 8, 5}, {12, 15, 10, 4}};    // x=0 y=2

int matriz_10[4][4] = {{12, 2, 13, 4}, {6, 8, 7, 10}, {0, 15, 9, 14}, {5, 1, 3, 11}};   // x=0 y=2