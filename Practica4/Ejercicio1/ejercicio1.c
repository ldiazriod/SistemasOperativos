#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t thread1, thread2, thmain;
pthread_attr_t attr;

pthread_mutex_t my_lock;

pthread_cond_t bufferLleno;
pthread_cond_t bufferVacio;

int buffer[12];

void *productor(void *agr)
{
    for (int i = 0; i < 12; i++)
    {
        pthread_mutex_lock(&my_lock);
        while (buffer[i] == 12)
            pthread_cond_wait(&bufferLleno, &my_lock);

        buffer[i] = i + 1;
        int data = buffer[i];
        printf("Dato producido: %d\n", data);
        for (int i = 0; i < 12; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");

        pthread_cond_signal(&bufferVacio);
        pthread_mutex_unlock(&my_lock);
        sleep(random() % 2);
    }
    pthread_exit(NULL);
}

void *consumidor(void *arg)
{
    for (int i = 0; i < 12; i++)
    {
        pthread_mutex_lock(&my_lock);
        while (buffer[i] == 0)
            pthread_cond_wait(&bufferVacio, &my_lock);

        int data = buffer[i];
        buffer[i] = 0;
        printf("Dato consumido: %d\n", data);
        for (int i = 0; i < 12; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");

        pthread_cond_signal(&bufferLleno);
        pthread_mutex_unlock(&my_lock);
        sleep(random() % 3);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    thmain = pthread_self();

    pthread_attr_init(&attr);
    pthread_mutex_init(&my_lock, NULL);
    pthread_cond_init(&bufferLleno, NULL);
    pthread_cond_init(&bufferVacio, NULL);

    pthread_create(&thread1, &attr, productor, NULL);
    pthread_create(&thread2, &attr, consumidor, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&my_lock);
    pthread_cond_destroy(&bufferLleno);
    pthread_cond_destroy(&bufferVacio);
    pthread_exit(NULL);
}