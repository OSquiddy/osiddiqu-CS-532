#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>

int main (int argc, char *argv[]) {
    pid_t pid;
    int status;

    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    // char *saveptr, *token;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(-1);
    }

    stream = fopen(argv[1], "r");
    if (stream == NULL) {
        perror("fopen");
        exit(-1);
    }

    while ((nread = getline(&line, &len, stream)) != -1) {
        // printf("\nRetrieved line of length: %zd:\n", nread);
        // printf("\nLine: %s\n", line);

        char *token = strtok(line, " ");
        char **arguments;
        arguments = (char **)calloc(1, sizeof(char *));
        int token_count = 0;
        char *executable = strdup(token);
        while (token != NULL) {
            token = strtok(NULL, " ");
            // printf("Token: %s\n", token);
            if (token != NULL) {
                // arguments[token_count] = realloc(arguments[token_count], sizeof(char *));
                free(arguments[token_count]);
                arguments[token_count] = strdup(token);
                // printf("Hello\n", token_count);
                // printf("%s\n", arguments[token_count]);
                token_count++;
                arguments = realloc(arguments, token_count * sizeof( char *));
            }
            
        }
        arguments[token_count] = (char *)NULL;


        for (int i = 0; i <= token_count; i++) {
            printf("Arguments[%d]: %s\n", i, arguments[i]);
        } 

        printf("\n");

        time_t start_time, end_time;
        start_time = time(NULL);
        if (start_time < 0) {
            fprintf(stderr, "Start time could not be recorded\n");
            perror("time");
            exit(-1);
        }
        pid = fork();
        if (pid == 0) {
            // printf("Executable: %s\n", executable);
            execvp(executable, arguments);
            printf("If you see this statement, then execvp failed\n");
            perror ("execvp");
            exit(-1);
        } else if (pid > 0) {
            // printf("Waiting for the child process to terminate\n");
            wait(&status);
            if (WIFEXITED(status)) {
                // printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                end_time = time(NULL);
                if (end_time < 0) {
                    fprintf(stderr, "End time could not be recorded\n");
                    perror("time");
                    exit(-1);
                }
                printf("Start Time %s,     End Time %s", ctime(&start_time), ctime(&end_time));
            }
        } else {
            printf("Child process did not terminate normally\n");
        }

        free(arguments);
    }

    free(line);
    fclose(stream);
    
    return 0;
}
