#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	pid_t pid;
    int i;
    srandom(getpid());
    for(i=0; i < 2; i++){
        pid=fork();
        printf("Soy el proceso de PID %d y mi padre tiene %d de PID\n", getpid(), getppid());
		if(pid == 0){
			break;
		}
    }
    pid=fork();
    pid=fork();
    printf("1Soy el proceso de PID %d y mi padre tiene %d de PID\n", getpid(), getppid());
    
    if(pid == 0){
        sleep(random()%5);
    }else{
        for(i=0; i < 2; i++){
            printf("%d ", i);
            printf("Fin del proceso de PID %d\n", wait(NULL));
        }
    }
	return 0;
}