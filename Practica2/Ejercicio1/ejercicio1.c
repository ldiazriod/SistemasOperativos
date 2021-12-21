#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_t thread1, thread2, thmain; 
pthread_attr_t attr;
 
void *factorial(void *arg){
    unsigned int auxReturn = 1;
    for(int i=1; i <= atoi((char *)arg); i++){
        auxReturn *= i;
    }
    printf("El factorial de %d es %d \n", atoi((char *)arg), auxReturn);
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    thmain = pthread_self();
    pthread_attr_init(&attr);
    pthread_create(&thread1, &attr, factorial, (void *)argv[1]); 
    pthread_create(&thread2, &attr, factorial, (void *)argv[2]);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_exit(NULL);
    return 0;
}
