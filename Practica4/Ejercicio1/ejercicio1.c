#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define length 12

pthread_t thread1, thread2, thmain;
pthread_attr_t attr;   
pthread_mutex_t lock;  
pthread_cond_t bufferLleno;
pthread_cond_t bufferVacio;
int buffer[length];

void *producer(void *agr){
    for (int i = 0; i < length; i++){
        pthread_mutex_lock(&lock);
        while (buffer[i] == 12){ 
            pthread_cond_wait(&bufferLleno, &lock);
        }
        buffer[i] = i + 1;
        printf("Dato producido: %d\n", buffer[i]);
        for (int i = 0; i < length; i++){
            printf("%d ", buffer[i]);
        }
        printf("\n");
        pthread_cond_signal(&bufferVacio);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg){
    for (int i = 0; i < length; i++){
        pthread_mutex_lock(&lock);
        while (buffer[i] == 0){
            pthread_cond_wait(&bufferVacio, &lock);
        }
        int data = buffer[i];
        buffer[i] = 0;
        printf("Dato consumido: %d\n", data);
        for (int i = 0; i < length; i++){
            printf("%d ", buffer[i]);
        }
        printf("\n");

        pthread_cond_signal(&bufferLleno);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    thmain = pthread_self();
    pthread_attr_init(&attr);
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&bufferLleno, NULL);
    pthread_cond_init(&bufferVacio, NULL);
    pthread_create(&thread1, &attr, producer, NULL);
    pthread_create(&thread2, &attr, consumer, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&bufferLleno);
    pthread_cond_destroy(&bufferVacio);
    pthread_exit(NULL);
}

/*
    Condicionales son más o menos condiciones.
    Si se cumplen las condiciones. Se hace algo que todavía no se con el mutex.

    Si se cumple la condición. El mutex de desbloquea.
    Si se cumple la condición. El mutex de bloquea.

    Polling -> Que es un metodo secuencial donde el código se bloquea totalmente hasta que se deja o se cumple la condición.
    Interrupciones -> Es un metodo no secuencial en el que el código se ejecuta en un bucle infinito que salta a otras funciones mientras el resto del código
    sigue en ejecución.
*/