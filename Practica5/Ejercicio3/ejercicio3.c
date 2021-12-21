#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static long deepSearch(char *dirname){

    DIR *dir = opendir(dirname);
    if (dir == 0){
        exit(-1);
    }

    struct dirent *dit;
    struct stat st;
    long size = 0;
    long finalSize = 0;
    char filePath[NAME_MAX]; 

    while ((dit = readdir(dir)) != NULL){
        if ((strcmp(dit->d_name, ".") == 0) || (strcmp(dit->d_name, "..") == 0)){
            continue;
        }  
        sprintf(filePath, "%s/%s", dirname, dit->d_name);
        if (lstat(filePath, &st) != 0){
            continue;
        }
        size = st.st_size;
        if (S_ISDIR(st.st_mode)){
            long dirSize = deepSearch(filePath) + size;
            printf("DIR: %s\t", dit->d_name);
            printf("SIZE: %ld\n\n", dirSize);
            finalSize += dirSize;
        }else{
            finalSize += size;
            printf("FILE: %s\t", dit->d_name);
            printf("SIZE: %ld\n", size);
        }
    }
    return finalSize;
}

int main(int argc, char *argv[]){
    if (argc != 2){
        perror("Ninguno o demasiados argumentos");
    }
    long size = deepSearch(argv[1]);
    printf("Total size: %ld Bytes\n", size);

    return 0;
}
