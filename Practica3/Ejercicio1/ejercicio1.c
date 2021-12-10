#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define length 512

int main(int argc, char **argv){
    pid_t pid;
    int p[2];
    char buffer[length];

    pipe(p);

    pid = fork(); // fork() Duplica el código -> 2 procesos. 1 padre, 1 hijo. 2^n -> n = número de forks.

    if(pid == -1){ //Comprueba si se ha creado el hijo. 
        printf("No se pudo crear al hijo");
        exit(-1);
    }else if(pid == 0){ //Si se crea y es el hijo
        close(p[0]);
        printf("El hijo escribe en el PIPE \n");
        sleep(3);
        sprintf(buffer, "Hola mundo!");
        write(p[1], buffer, length);
        close(p[1]);
    }else{ //Si es el padre.
        close(p[1]);
        wait(NULL);
        printf("Padre leyendo en el PIPE \n");
        sleep(3);
        read(p[0], buffer, length);
        printf("Mensaje: %s \n", buffer);
        close(p[0]);
    }
    exit(0);
}
