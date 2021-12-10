#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
	FILE* file;
	char buffer[100];
	file = fopen("ejemplo", "r");
	if(file == NULL){
		exit(1);
	}else{
		printf("Content is: \n\n");
		while(fgets(buffer, 100, file)){
			printf("%s", buffer);
		}
		fclose(file);
	}
	return 0;
}	
