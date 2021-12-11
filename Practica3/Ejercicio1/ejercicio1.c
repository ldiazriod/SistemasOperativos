#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define length 512

int main(int argc, char **argv){
    pid_t pid; //Process iden
    int p[2]; //Declaramos el futuro pipe
    char buffer[length]; //Un buffer de lectura/escritura para el pipe.

    pipe(p); //Decimos que el p va a ser un pipe.

    pid = fork(); // fork() Duplica el código -> 2 procesos. 1 padre, 1 hijo. 2^n -> n = número de forks.

    if(pid == -1){ //Comprueba si se ha creado el hijo. 
        printf("No se pudo crear al hijo");
        exit(-1);
    }else if(pid == 0){ //Si se crea y es el hijo
        close(p[0]); //Cerramos la lectura en el pipe.
        printf("El hijo escribe en el PIPE \n"); 
        sleep(3);
        sprintf(buffer, "Hola mundo!"); //Guardamos en el buffer un mensaje.
        write(p[1], buffer, length); //write() -> p[1] (escritura), buffer con el mensaje, con tamaño length.
        close(p[1]); //Cerrar la escritura.
    }else{ //Si es el padre.
        close(p[1]); //Cerramos la escritura.
        wait(NULL); //Esperamos a que termine el proceso hijo.
        printf("Padre leyendo en el PIPE \n");
        sleep(3);
        read(p[0], buffer, length); //Leemos de p[0] y guardamos el mensaje dentro del buffer con tamaño length.
        printf("Mensaje: %s \n", buffer); //Sacamos buffer
        close(p[0]); //Cerramos lectura.
    }
    exit(0); //Terminamos.
}

/*
    Pipes -> Las pipes en Unix tienen solo lectura y escritura, y se activan mediante integers.
    pipe[0] -> Lectura.
    pipe[1] -> Escritura.
*/
