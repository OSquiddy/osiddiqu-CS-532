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
int sum = 0, sum_check = 0;
int pipefd[2];

void *randomGenerator(void *arg) {

    srand(pthread_self());

    for (int i = 0; i < 500; i++) {
        int random_number = rand() % 1001;
        pthread_mutex_lock(&mutex);
        sum_check += random_number;
        if (write(pipefd[1], &random_number, sizeof(random_number)) == -1) {
            perror("write");
            exit(-1);
        };
        pthread_mutex_unlock(&mutex);
    }

    return NULL;

}

void *calculateSum (void *arg) {
    int local_sum = 0;
    int number;

    for (int i = 0; i < CHILD_THREAD_NUMBERS; i++) {
        read(pipefd[0], &number, sizeof(number));
        local_sum += number;
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
    int status;
    double avg;
    pthread_t *tid_p;

    if (argc != 1) {
        printf("Usage: %s\n", argv[0]);
        exit(-1);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(-1);
    }

    pid = fork();

    if (pid == 0) {
        if (signal(SIGUSR1, run_child_program) == SIG_ERR) {
            printf("Something went wrong with capturing the signal.\n");
            exit(-1);
        }

        childPid = getpid();
        close(pipefd[1]);


        printf("Child processs waiting for signal...\n");
        pause();

        double result = (double) sum / 1500;
        printf("Calcuated avg = %.2f\n", result);

        exit(0);

    } else if (pid > 0) {
        close(pipefd[0]);
        
        tid_p = (pthread_t *)malloc(sizeof(pthread_t) * NUM_THREADS_P);

        for (int i = 0; i < NUM_THREADS_P; i++) {
            pthread_create(&tid_p[i], NULL, randomGenerator, (void *)i);
        }

        for (int i = 0; i < NUM_THREADS_P; i++) {
            pthread_join(tid_p[i], NULL);
        }

        if (kill(pid, SIGUSR1) == -1) {
            perror("kill");
            exit(-1);
        }
        
        wait(&status);

        avg = (double) sum_check / 1500;
        printf("Expected average = %.2f\n", avg);


    } else {
        printf("Something went wrong: %d\n", pid);
        perror("fork");
        exit(-1);
    }


    return 0;
}