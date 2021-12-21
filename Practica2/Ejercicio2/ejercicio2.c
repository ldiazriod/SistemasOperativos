#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>

#define length 1000

pthread_t thread1, thmain;
pthread_attr_t attr;

void *cuenta (void *nombre){
    int counter = 0, numC;
    char buffer[length];
    char *name = (char *)nombre;
    int fd;
    fd = open(name, O_RDONLY);
    while((numC=read(fd, buffer, length)) != 0){
        for(int pos=0; pos < numC; pos++){
            if((buffer[pos]=='a') || (buffer[pos]=='A')){
                counter++;
            }
        }
    }
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados \n", name, counter);
    close(fd);
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Indica el nombre de un fichero. \n");
        exit(0);
    }
    thmain = pthread_self();
    pthread_attr_init(&attr);
    pthread_create(&thread1, &attr, cuenta, (void *)argv[1]);
    pthread_join(thread1, NULL);
    pthread_exit(NULL);
    return 0;
}

