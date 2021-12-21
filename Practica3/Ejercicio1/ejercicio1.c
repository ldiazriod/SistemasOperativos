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

    pid = fork();

    if(pid == -1){
        printf("No se pudo crear al hijo");
        exit(-1);
    }else if(pid == 0){
        close(p[0]);
        printf("El hijo escribe en el PIPE \n"); 
        sleep(3);
        sprintf(buffer, "Hola mundo!");
        write(p[1], buffer, length);
        close(p[1]); 
    }else{
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

/*
    Pipes -> Las pipes en Unix tienen solo lectura y escritura, y se activan mediante integers.
    pipe[0] -> Lectura.
    pipe[1] -> Escritura.
*/
