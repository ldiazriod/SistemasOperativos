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
        int fileSize = read(fd, buffer, length);
        close(fd);
        int fdCo = open("copiedFile1.txt", O_RDWR | O_CREAT, 0644);
        if(fdCo == -1){ 
            perror("Error: Something went wrong");
        }else{
            write(fdCo, buffer, fileSize);
        }
        close(fdCo);
    }
    exit(0);
}
