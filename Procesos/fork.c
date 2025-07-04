#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/*  fork()

Es la función que permite de crear nuevos procesos, los cuales se "clonan" de su proceso padre. Clona los 3 tipos de segmento, excepto
el segmento system (perteneciente a los PID y PPID); los demas segmentos son una copia exacta hasta que se mute con exec().

La region de memoria del padre es distinta de la del hijo, aunque se clonen; los recursos y el usuario son los mismos. 

pid_t fork(void);

SI SALE BIEN, la cant_procesos_sistema se incrementa en 1; si sale mal, se actualiza el errno, y devuelve DOS valores int(retorna); 
la causa de muerte al padre, y una para el hijo (osea output oara nosotros). Al padre le retorna el PID del proceso que creó. 
*/

int main() {

    // pid_t es un tipo !
    pid_t pid_hijo = fork();     // el PID del hijo es el retorno de fork()

    int var = 5;     // Segmento de datos del proceso Padre - Si bien clona el Text y Data Segment cuando crea el proceso Hijo, despues su data segment cambia

    switch(pid_hijo) {

        //Si hubo éxito, devuelve 0 al hijo
        case 0: {  

            var = 10;                   // Cambia la memoria del proceso hijo de 5 a 10 ! - asi muta el segmento de usuario 
            printf("Proceso hijo\n");
            printf("Hijo: PID=%d, PPID=%d Variable=%d\n", getpid(), getppid(), var);
            break; 
        }

        // Si fork falla...
        case -1: {  

            printf("errno = %d\n", errno);  perror("fork: ");
            break;
        } 

        // Pertenece al proceso padre ! - cualquier entero positivo que será el PID del hijo
        default: {  

            printf("Proceso padre\n");
            printf("Padre: PID=%d, PPID=%d variable=%d\n", getpid(), getppid(), var);
            break; 
        }
    }

    return 0;       // indica que hubo exito 
}