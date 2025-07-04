#include <unistd.h> // unix estandar
#include <stdio.h>
#include <errno.h>

/* Si este bloque de codigo se da, se muta
el proceso actual por el del programa de los argumentos
y jamás nos enteraremos de que tuvo exito 
porque no retorna nada */

// La idea es clonar un proceso ya en ejecución y modificar sus segmentos para que se convierta en un nuevo proceso
int main() {

    int ret;    // entero que guarda el retorno de esta funcion - solo se usa cuando FALLA el exec

    // Array de strings que son argumentos - ls se repite siempre porque es el nombre del programa por convencion
    char *args[] = {"ls", "-l", NULL};      // NULL indica que se terminan los argumentos de esa funcion

    // Es entonces que asignamos el retorno a la ejecución del programa
    ret = execv("/usr/bin/ls", args);   // path hacia el binario, y los argumentos del array - ese path se puede ver con el comando whereis

    /* Si el programa se muta efectivamente  */
    printf("Llegamos a este checkpoint, el proceso fue mutado");

    /* En cambio, si no se da el cambio de proceso,
    la syscall tira error y podemos capturarlo para 
    procesarlo o revisarlo con errno y perror */

    // un error podria estar en la ruta del exec, por ejemplo
    if (ret == -1) {

        // Printea el código del error
        printf("errno = %d\n", errno);

        // Mensaje de error de la libreria <errno.h>
        perror("Hubo un error con exec y la syscall...");

        return -1;
    }

    /* Si tiene exito el exec, nunca se llega a retornar el codigo */

    // Este codigo es inalcanzable pues o se retorna -1 o se cambia el proceso 
    printf("Código Inalcanzable");

    return 0;
}