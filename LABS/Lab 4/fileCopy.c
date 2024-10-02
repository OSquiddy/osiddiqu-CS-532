#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFSIZE 10

int main (int argc, char **argv) {
    if (argc != 3){
        printf("Usage: %s <source> <destination>\n", argv[0]);
        exit (-1);
    }

    int readFileDesc, writeFileDesc;
    long int n;
    char buffer[BUFFSIZE];

    if (strcmp(argv[1], argv[2]) == 0) {
        printf("Error: Files cannot have the same name.\n");
        exit(-1);
    }

    readFileDesc = open(argv[2], O_RDONLY);
    if(readFileDesc == -1) {
        printf("Error opening source file '%s'\n", argv[2]);
        exit(-1);
    }

    writeFileDesc = open(argv[1],   O_WRONLY | O_APPEND | O_CREAT, 0700);
    if (writeFileDesc == -1) {
        printf("Error opening destination file '%s'\n", argv[1]);
        close(readFileDesc);
        exit(-1);
    }
    
    while ((n = read(readFileDesc, buffer, sizeof(buffer))) > 0) {
        if (write(writeFileDesc, buffer, n) != n) {
            printf("Error writing to destination file '%s'\n", argv[1]);
            close(readFileDesc);
            close(writeFileDesc);
            exit(-1);
        }
    }

    if (n < 0) {
        printf("Error reading from source file\n");
    } else {
        printf("File copied successfully\n");
    }

    close(readFileDesc);
    close(writeFileDesc);
    


    return 0;
}