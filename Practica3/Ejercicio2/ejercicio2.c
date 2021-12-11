#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdlib.h>


#define length 12

int buffer[length]; //Declaramos el buffer
pthread_t thread1, thread2 ,thmain; //Declaramos los futuros threads
pthread_attr_t attr; //Declaramos los atributos que más tarde incializaran los threads.
sem_t semC, semP; //Declaramos los semaforos.

void *producer(void *arg){
    for(int i=0; i < length; i++){ //for 12
        sem_wait(&semP); //semp--
        if(buffer[i] == 0){ // Si no hay elemento en buffer[i].
            buffer[i] = i+1; //inicializa con i+1. -> rango 1-12. 
            int aux = buffer[i]; //Esto no sirve para nada. Es copia y pega de la función consumer.
            printf("Dato producido: %d \n", aux); //Decimos que dato hemos producido.
            for(int i=0; i < length; i++){ //Sacamos el buffer modificado.
                printf("%d ", buffer[i]);
            }
            printf("\n");
        }
        sem_post(&semC); //semC++
    }
    //Al terminar el for. semP = 0; semC = 12.
    pthread_exit(NULL); //Cerramos el thread.
}

void *consumer(void *arg){
    for(int i=length; i > 0; i--){ //Recorremos el buffer pero al reves.
        sem_wait(&semC); //semC--
        if(buffer[i] != 0){ //Solo podemos consumir si el buffer en esa posición está lleno.
            int aux = buffer[i]; //Guardamos el valor antes de consumirlo, para más tarde sacarlo por pantalla.
            buffer[i] = 0; //Consumimos el valor. Antes buffer[i] = 3 -> Ahora buffer[i] = 0;
            printf("Dato consumido %d \n", aux); //Sacamos por pantalla el elemento que hemos consumido usando la variable aux.
            for(int i=0; i < length; i++){ //Imprimimos por pantalla el nuevo buffer con el elemento consumido.
                printf("%d ", buffer[i]);
            }
            printf("\n");
        }
        sem_post(&semP); //SemP++;
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    thmain = pthread_self(); //Especificamos el thread princial.
    pthread_attr_init(&attr); //Inicializamos los atributos de los threads.
    sem_init(&semP, 0, 12); //semP -> Local y empieza en el valor 12. 
    sem_init(&semC, 0, 0); //SemC -> Local pero empieza en 0.
    pthread_create(&thread1, &attr, *producer, NULL); //Creamos los threads con los atributos y las funciones.
    pthread_create(&thread2, &attr, *consumer, NULL);
    pthread_join(thread1, NULL); //Esperamos a que las funciones de los threads se terminen de ejecutar y los juntamos el thread principal.
    pthread_join(thread2, NULL);
    sem_destroy(&semP); //Ponemos en blanco los semaforos. Los quitados de los espacios de memoria reservados.
    sem_destroy(&semC);
    pthread_exit(NULL); //Cerramos el thread principal.
}








/*
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 12

int buffer[SIZE];
pthread_t h1, h2, thmain;
pthread_attr_t attr;
sem_t sem;
int cont = 0;

//TODO: Funciones esta vacio o lleno el buffer
int is_empty(int b[]){
    for( int i=0; i<SIZE; i++){
        if(b[i] != 0){
            return -1; // Return false
        }
    }
    return 0; // Return true
}

int is_full(int b[]){
    for( int i=0; i<SIZE; i++){
        if(b[i] == 0){
            return -1; // Return false
        }
    }
    return 0; // Return true
}

//TODO: Funciones producir info en buffer y consumir info en buffer
int produce_info(int b[]){
    for(int i=0; i<SIZE; i++){
        if(is_empty){
            b[i] = i;
        }
    }
}

int consume_info(int b[]){
    for(int i=0; i<SIZE; i++){
        if(is_full){
            b[i] = 0;
        }
    }
}


//TODO: Funciones productor-consumidor
void *productor(void * arg){
    for(int i=0; i<SIZE; i++){
        sem_wait(&sem);
        if(is_empty){
            //! Produce informacion
            produce_info(buffer);
            printf("Info added to the buffer.\n");
        }
        sem_post(&sem);
    }
    pthread_exit(NULL);
}

void *consumidor(void * arg){
    for(int i=0; i<SIZE; i++){
        sem_wait(&sem);
        if(is_full){
            //! Consume informacion
            consume_info(buffer);
            printf("Info was consumed.\n");
        }
        sem_post(&sem);
    }
    pthread_exit(NULL);
}




int main(void){
    thmain = pthread_self();
    pthread_attr_init(&attr);
    sem_init(&sem, 0, 1);
    pthread_create(&h1, NULL, *productor, NULL);
    pthread_create(&h2, NULL, *consumidor, NULL);
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    sem_destroy(&sem);
    pthread_exit(NULL);

    return 0;
}
*/

/*
    Semaforos: Sincronizan.
    Unix tenemos varias funciones, pero primariamente 2.
    sem_wait() y sem_post().
    sem_wait() -> reduce en 1 el semaforo.
    sem_post() -> Aumenta en 1 el semoforo.
    sem_init() -> inicializa el semaforo, con el tipo de localidad y el valor inicical.

*/
