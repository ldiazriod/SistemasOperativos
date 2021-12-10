#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_t thread1, thread2, thmain;
pthread_mutex_t lock;
pthread_attr_t attr;

void *thread1Msg(void *args){
    pthread_mutex_lock(&lock);
    char *msg = "Hola Mundo! Soy el thread 1 \n";
    printf("%s", msg);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *thread2Msg(void *args){
    pthread_mutex_lock(&lock);
    char *msg = "Hola Mundo! Soy el thread 2 \n";
    printf("%s", msg);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    thmain = pthread_self();
    pthread_attr_init(&attr);
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread1, &attr, thread1Msg, NULL);
    pthread_create(&thread2, &attr, thread2Msg, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock);
    pthread_exit(NULL);
    return 0;
}
