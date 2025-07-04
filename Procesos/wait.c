#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

    // Clonamos proceso main
    int pid = fork();


    if (pid) {

        wait(NULL);
        printf("Es el turno del proceso hijo...");
    
    } else {

        printf("Soy el hijo yo!!");
        char *args[] = {"sleep", "5", NULL};
        execv("/usr/bin/sleep", args);

    }

    return 0;
}