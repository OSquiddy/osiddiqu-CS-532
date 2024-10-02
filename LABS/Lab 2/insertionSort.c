#include <stdio.h>
#include <stdlib.h>

/*
* To compile and run this code, paste the commands inside the double quotes into your terminal.
* DO NOT copy the double quotes as well.
* 	- Compilation: "gcc -o insertionSort insertionSort.c"
* 	- Execution: "./insertionSort"
*/

// Logic for the insertionSort was taken from the insertionSort.java file provided with the assignment
void insertionSort(int *array, int size) {

	int current, temp;

    for (int i=1; i<size; i++) {
        current = i;
        while (current > 0 && array[current - 1] > array[current]) {
            temp = array[current];
            array[current] = array[current - 1];
            array[current - 1] = temp;
            current--;
        }
    }
}

int main(int argc, char** argv) {
	int size, num;
    int *array;

	printf("\nEnter array size: ");
	scanf("%d", &size);

    array = malloc(size * sizeof(int));

    for (int i=0; i<size; i++) {
        printf("Enter value for index %d: ", i);
        scanf("%d", &num);
        array[i] = num;
    }

    printf("\nInput array: [");
    for (int i=0; i<size; i++) {
        (i < size - 1) ? printf("%d, ", array[i]) : printf("%d]\n", array[i]);
    }

    insertionSort(array, size);

    printf("\nSorted array: [");
    for (int i=0; i<size; i++) {
        (i < size - 1) ? printf("%d, ", array[i]) : printf("%d]\n\n", array[i]);
    }

	return 0;
}
