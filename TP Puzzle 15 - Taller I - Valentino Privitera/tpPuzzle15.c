#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "baseDatosMatrices.h"

// Funcion que imprime la matriz en cada movimiento
void imprimir_matriz(int matriz[4][4]) {

printf("\n");

int i=0, j=0;

while(i < 4) {      // y

j = 0;

    while(j < 4) {      // x

        if (matriz[i][j] != 0) {            // Si el elemento es distinto del 0

            printf("[%2i]", matriz[i][j]);  // Tablero Simetrico
        }
        else {                  

            printf("[  ]");     // Transforma el 0 == ' '
        }
        j++;
    }
    printf("\n");
    i++;
}
}

// Funcion que detecta cuando un puzzle esta resuelto y calcula puntos partida
int compara_matriz_ideal(int matriz[4][4], int cant_mov, int bet) {

    int iguales = 1;        // Matrices ==
    int puntuacion = 0;     // Reinicio la puntuacion en cada invocacion

    for (int i = 0; i < 4; i++) {       // y

        for (int j = 0; j < 4; j++) {       // x

            if (matriz[i][j] != matriz_ideal[i][j]) {   // Compara cada elemento de la matriz actual con la ideal

                iguales = 0;    // Devuelve 0 si al menos un elemento de las matrices no coincide
                break;          // Dejamos de evaluar en ese caso.. (rompemos este for)
            }
        }

        if (!iguales) {         // Si iguales = 0 rompemos este for tambien si hubo un elemento distinto
        break;
        }
    }

    if (iguales) {         // Si matriz == 1

        printf("\nGANO LA PARTIDA!! FELICITACIONES!!\n\n");
        printf("Ud. realizo %i movimientos!\n", cant_mov);
        printf("Ud. aposto que lo resolveria en %i movimientos!\n", bet);

        // Comparamos la apuesta con los puntos
        if (cant_mov == bet) {

        puntuacion = 1000;
        printf("Obtuvo %i puntos en esta partida!!\n", puntuacion);

        } else if (cant_mov >= bet-10 && cant_mov <= bet) {

        puntuacion = 500;
        printf("Obtuvo %i puntos en esta partida!!\n", puntuacion);

        } else if (cant_mov > bet && cant_mov <= bet+10 ) {

        puntuacion = 100;
        printf("Obtuvo %i puntos en esta partida!!\n", puntuacion);

        } else if (cant_mov > bet+10 || cant_mov < bet-10) {

        puntuacion = 0;
        printf("Obtuvo %i puntos en esta partida!!\n", puntuacion);
        
        }
        printf("Pulse 'E' para volver al Menu\n");
    }
    return iguales;
}

// Funcion que mueve la ficha a traves del tablero
void consola_juego(int matriz[4][4], int cant_mov, int bet, int x, int y) {

char caracter;
char enter;     // La toma como sin uso pero evita que tome el enter como un char mas 

printf("\n");
printf("                         --- // GUIA DE CONTROLES \\ --- ");
printf("\n");
printf("\n");
printf("[W] - Arriba // [S] - Abajo // [A] - Izquierda // [D] - Derecha // [E] - Salir del Juego\n");
printf("\n");

imprimir_matriz(matriz);

printf("\nUd. debe apostar en cuantos movimientos resolvera el puzzle presentado,\nlos movimientos son entre 40 y 200, inclusive.\n");
printf("Si sus movimientos son exactos a los movimientos apostados: 1000 Puntos\n");
printf("Si Ud. resuelve el puzzle antes sus movimientos apostados menos 10 unidades: 500 Puntos\n");
printf("Si Ud. resuelve superando por menos de 10 unidades a los movimientos apostados: 100 Puntos\n");
printf("En otro caso, o si sale de la partida: 0 Puntos\n");

// Reiniciamos cada vez que se invoque la funcion
cant_mov = 0;   
bet = 0;

do {

printf("\nIngrese su apuesta: ");
scanf("%i", &bet);

    if (bet < 40 || bet > 200) {

        printf("La apuesta debe ser entre 40 y 200 movimientos!\n");
    }

} while (bet < 40 || bet > 200);

printf("\nVeremos.. ahora, a jugar!\n");

imprimir_matriz(matriz);

do {

enter = getchar();
caracter = toupper(getchar());

switch(caracter) {                                      

//-------------------------------------// -> ARRIBA
case 'W':   

    if (y >= 1) {   // Si el 0 no se sale del tablero..

        matriz[y][x] = matriz[y-1][x];          // Cambiamos al 0 por el elemento que queremos cambiar de lugara
        matriz[y-1][x] = 0;                     // Sustituimos el elemento intercambiado por 0 
        imprimir_matriz(matriz);
        y--;                                    // Movemos la posicion de movimiento en 1 unidad     
        printf("\n");
    }
    else {
        printf("Se desplaza fuera del limite..\n");
    }
break;


//-------------------------------------// -> ABAJO
case 'S':   

    if (y <= 2) {   

        matriz[y][x] = matriz[y+1][x];
        matriz[y+1][x] = 0;
        imprimir_matriz(matriz);
        y++;
        printf("\n");
    }    
    else {
        printf("Se desplaza fuera del limite..\n");
        // Si queremos ir hacia abajo, y superamos la fila 4 (y > 3), osea el final del tablero, no deja seguir
    }
break;

//-------------------------------------// -> IZQ
case 'A':

    if (x >= 1) {

        matriz[y][x] = matriz[y][x-1];
        matriz[y][x-1] = 0;
        imprimir_matriz(matriz);
        x--;
        printf("\n");
    }    
    else {
        printf("Se desplaza fuera del limite..\n");
    }
break;


//-------------------------------------// -> DER
case 'D':

    if (x <= 2) {

        matriz[y][x] = matriz[y][x+1];
        matriz[y][x+1] = 0;
        imprimir_matriz(matriz);
        x++;
        printf("\n");
    }    
    else {
        printf("Se desplaza fuera del limite..\n");
    }
break;


//-------------------------------------// -> EXIT - El jugador puede salir cuando quiera al menu apretando 'E' o 'e'
case 'E':   // OBTUVO 0 PUNTOS
return; 
break;

//-------------------------------------// -> Si no se introduce W, A, S, D o E..
default: 
printf("Caracter Incorrecto.");
break;

}

cant_mov++;                                 // Incrementa cada movimiento de tablero
printf("Movimientos: %i\n", cant_mov);      // Muestra la cantidad de movimientos realizados hasta el momento

// Funcion que en cada movimiento verifica si esta resuelto el puzzle
compara_matriz_ideal(matriz, cant_mov, bet);

} while (caracter != 'E');  // EXIT

}

// Main
int main () {

printf("\n\n                      BIENVENIDO AL JUEGO DEL PUZZLE 15!\n");
printf("          El jugador debera ordenar la tabla, en orden creciente, del 1 al 15\n");
printf("              solo moviendo una pieza vacia en vertical y horizontal!");
printf("\n");

int matriz_variable[4][4];      // Matriz auxiliar
int tablero;

int cant_movimientos, apuesta;

int x, y;

char sigue, enter;

do {

tablero++;

switch (tablero) {

case 1:
        for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_1[j][i];     // Sustituimos la variable por una configuracion ganadora
            }
        } 
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=3, y=2);
break;

case 2:
          for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_2[j][i];
            }
        }
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=1, y=0);
        // Pasamos como parametro la ubicacion del 0 para moverse a partir de ahi (0 = ' '), por ejemplo:
        //                    y=0:  x=1
        // int matriz_2[4][4] = {{3, 0, 12, 5}, {7, 8, 13, 11}, {6, 9, 15, 1}, {14, 10, 4, 2}};
break;

case 3:
          for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_3[j][i];
            }
        }
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=3, y=1);
break;

case 4:
        for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_4[j][i];
            }
        }
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=1, y=0);       
break;

case 5:
        for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_5[j][i];
            }
        }
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=2, y=1);
break;

case 6:
        for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_6[j][i];
            }
        }
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=1, y=2);       
break;

case 7:
        for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_7[j][i];
            }
        }
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=0, y=3);
break;

case 8:
        for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_8[j][i];
            }
        }
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=2, y=0);
        break;    

case 9:
        for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_9[j][i];
            }
        }
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=0, y=2); 
        break;

case 10:
        for (int j = 0; j < 4; j++) {

            for (int i = 0; i < 4; i++) {

            matriz_variable[j][i] = matriz_10[j][i];
            }
        }
        consola_juego(matriz_variable, cant_movimientos, apuesta, x=0, y=2);   

}

printf("\nDesea seguir jugando? [S]i / [N]o : \n");
enter = getchar();
sigue = toupper(getchar());

if (sigue == 'N') {

    printf("Gracias, vuelva prontos! ");
    exit(0);
}

} while (tablero < 10);

printf("Alcanzo el limite de 10 partidas.. lo siento!");

return 0;

}