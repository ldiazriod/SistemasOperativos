#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define length 12

pthread_t thread1, thread2, thmain; //Declaramos los threads.
pthread_attr_t attr; //Declaramos los atributos que más tarde inicializarán los threads.

pthread_mutex_t lock; //Declaramos el mutex. aka Lock.

pthread_cond_t bufferLleno; //Declaramos dos condicionales. bufferLleno y bufferVacio.
pthread_cond_t bufferVacio;

int buffer[length]; //declaramos el buffer.

void *producer(void *agr)
{
    for (int i = 0; i < length; i++) //For 0 - 11. Pero cuando producimos, producimos i+1 -> rango 1-12
    {
        pthread_mutex_lock(&lock); //Bloqueamos el proceso mediante mutex para sincronizar.
        while (buffer[i] == 12){ //Polling. buffer[i] = 12. Significa el buffer está lleno. Si buffer[i] = 12 hemos recorrido todo el for.
            printf("Quiero saber que está pasando\n");
            pthread_cond_wait(&bufferLleno, &lock);
        }

        buffer[i] = i + 1;
        int data = buffer[i];
        for (int i = 0; i < length; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");

        pthread_cond_signal(&bufferVacio);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    for (int i = 0; i < length; i++)
    {
        pthread_mutex_lock(&lock);
        while (buffer[i] == 0){
            pthread_cond_wait(&bufferVacio, &lock);
        }
            
        int data = buffer[i];
        buffer[i] = 0;
        printf("Dato consumido: %d\n", data);
        for (int i = 0; i < length; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");

        pthread_cond_signal(&bufferLleno);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
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