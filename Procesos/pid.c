
#include <stdio.h>
#include <unistd.h> // Declara las fun del estandar POSIX como getpid

int main() {

// Imprime el PID del proceso actual
printf("PID = %d \n", getpid());

// Imprime el PID del proceso padre 
// printf("PPID = %d \n", getppid());  -> El parent pid no estaria andando
 

return 0;

}