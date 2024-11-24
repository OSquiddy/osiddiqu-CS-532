#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define NUM_THREADS_P 3
#define NUM_THREADS_C 10
#define CHILD_THREAD_NUMBERS 150

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int childPid;
int sum, sum_check;
int pipefd[2];

void *randomGenerator(void *arg) {
    // int *thread_id = (int *)arg;
    srand(pthread_self());
    int array[500];

    for (int i = 0; i < 500; i++) {
        int random_number = rand() % 1001;
        array[i] = random_number;
        pthread_mutex_lock(&mutex);
        sum_check += random_number;
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    write(pipefd[1], array, sizeof(array));
    pthread_mutex_unlock(&mutex);

    // printf("[Parent] Finished thread %d\n", *thread_id);

    return NULL;

}

void *calculateSum (void *arg) {
    int local_sum = 0;
    int myArray[CHILD_THREAD_NUMBERS];

    // pthread_mutex_lock(&mutex);
    read(pipefd[0], myArray, sizeof(myArray));
    // pthread_mutex_unlock(&mutex);

    for (int i = 0; i < CHILD_THREAD_NUMBERS; i++) {
        printf("%d ", myArray[i]);
        local_sum += myArray[i];
    }


    pthread_mutex_lock(&mutex);
    sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

static void run_child_program(int signo) {
    pthread_t *tid_c;

    printf("SIGUSR1 signal has been received.\n");
    printf("Child process now running calculations.\n");

    tid_c = (pthread_t *)malloc(sizeof(pthread_t) * NUM_THREADS_C);

    for (int i = 0; i < NUM_THREADS_C; i++) {
        pthread_create(&tid_c[i], NULL, calculateSum, (void *)i);
    }

    for (int i = 0; i < NUM_THREADS_C; i++) {
        pthread_join(tid_c[i], NULL);
    }
}

int main (int argc, char *argv[]) {

    pid_t pid;
    // int status;
    double avg;
    pthread_t *tid_p;
    
    if (signal(SIGUSR1, run_child_program) == SIG_ERR) {
        printf("Something went wrong with capturing the signal.\n");
        exit(-1);
    }

    if (argc != 1) {
        printf("Usage: %s\n", argv[0]);
        exit(-1);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(-1);
    }
        
    // printf("Created pipe successfully\n");
    pid = fork();

    if (pid == 0) {


        childPid = getpid();
        close(pipefd[1]);
        // if (dup2(pipefd[0], 0) == -1) {
        //     perror("dup2");
        //     exit(-1);
        // }

        printf("Child processs waiting for signal...\n");
        pause();

        exit(0);

    } else if (pid > 0) {
        close(pipefd[0]);
        
        tid_p = (pthread_t *)malloc(sizeof(pthread_t) * NUM_THREADS_P);

        for (int i = 0; i < NUM_THREADS_P; i++) {
            // printf("Created thread %d\n", i);
            pthread_create(&tid_p[i], NULL, randomGenerator, (void *)i);
        }

        for (int i = 0; i < NUM_THREADS_P; i++) {
            pthread_join(tid_p[i], NULL);
            // printf("Thread %d finished\n", i);
        }

        avg = (double) sum_check / 1500;
        printf("\nExpected average: (%d / 1500) = %.2f\n", sum_check, avg);

        if (raise(SIGUSR1) == -1) {
            printf("Raise failed");
            perror("raise");
            exit(-1);
        };
        
        // wait(&status);
        // if (WIFEXITED(status)) {
        //     printf("Child process exited with status = %d\n", WIFEXITED(status));
        // }

        double result = (double) sum / 1500;
        printf("Calcuated avg: (%d / 1500) = %.2f\n", sum, result);


    } else {
        printf("Something went wrong: %d\n", pid);
        perror("fork");
        exit(-1);
    }


    return 0;
}