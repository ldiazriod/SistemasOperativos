#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdlib.h>


#define length 12

int buffer[length];
pthread_t thread1, thread2 ,thmain;
pthread_attr_t attr;
sem_t semC, semP;

void *producer(void *arg){
    for(int i=0; i < length; i++){
        sem_wait(&semP);
        if(buffer[i] == 0){ // Si no hay elemento en buffer[i].
            buffer[i] = i+1; //inicializa con i+1. -> rango 1-10. 
            int aux = buffer[i];
            printf("Dato producido: %d \n", aux);
            for(int i=0; i < length; i++){
                printf("%d ", buffer[i]);
            }
            printf("\n");
        }
        sem_post(&semC);
        sleep(random() % 3);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg){
    for(int i=12; i > 0; i--){
        sem_wait(&semC);
        if(buffer[i] != 0){
            int aux = buffer[i];
            buffer[i] = 0;
            printf("Dato consumido %d \n", aux);
            for(int i=0; i < length; i++){
                printf("%d ", buffer[i]);
            }
            printf("\n");
        }
        sem_post(&semP);
        sleep(random() % 3);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    thmain = pthread_self();
    pthread_attr_init(&attr);
    sem_init(&semP, 0, 12);
    sem_init(&semC, 0, 0);
    pthread_create(&thread1, &attr, producer, NULL);
    pthread_create(&thread2, &attr, consumer, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semP);
    sem_destroy(&semC);
    pthread_exit(NULL);
}
