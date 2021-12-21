#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define length 2500

int main(int argc, char **argv){
    char buffer[length];
    int fd = open("file1.txt", O_RDONLY, 444);
    if(fd == -1){
        perror("Error: File not found");
    }else{
        read(fd, buffer, length);
        for(int i=99; i < 109; i++){
            printf("%c", buffer[i]);
        }
        printf("\n");
    }
    close(fd);
    exit(0);
}
