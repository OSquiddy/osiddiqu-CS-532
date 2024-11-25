To compile:
    - make
  OR
    - gcc -Wall -o hw4 osiddiqu_HW04.c -lpthread

To execute:
    - ./hw4
To clean:
    - make clean

--------------------------------------------------

PROGRAM DESIGN:

The program calculates the average of 1500 numbers through the use of pipes, threads and multiple processes. The main (parent) process creates 3 threads,
which generate 500 random numbers each from 0 - 1000. These numbers are sent through a pipe to the child process, which spawns 10 threads, each of whom 
read 150 numbers from the pipe, find their sum, and then calculate the average. The output of the child process is redirected from the stdout channel to
the "output.txt" file.