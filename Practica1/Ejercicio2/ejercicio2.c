#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define length 20

int main(void){
    unsigned int results[length];
 
    pid_t pid1 = fork(); //Child 1
    pid_t pid2;

    if(pid1 == 0){
        printf("Im the first child %d from parent %d \n", getpid(), getppid());
        for(int i=0; i < length; i++){
            if((i%2) == 0){
                results[i] = i*i;
                printf("%d, ", i*i);
            }
        }
        printf("\n");
    }else if(pid1 == -1){
        perror("Error creating child 1 \n");
        exit(1);
    }else{
        pid2 = fork();
        if(pid2 == 0){
            printf("Im the second child %d from parent %d\n", getpid(), getppid());
            for(int i=0; i < length; i++){
                if((i%2) != 0){
                    results[i] = i*i;
                    printf("%d, ", i*i);
                }
            }
            printf("\n");
        }else if(pid2 == -1){
            perror("Error creating child 2\n");
            exit(1);
        }else{
            printf("Im the parent. PID: %d. Waiting childs \n", getpid());
            pid2 = wait(0);
            pid1 = wait(0);
        }
        exit(0);
    }



    return 0;
}