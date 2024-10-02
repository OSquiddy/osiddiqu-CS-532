#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* To compile and run this code, paste the commands inside the double quotes into your terminal.
* DO NOT copy the double quotes as well.
* 	- Compilation: "gcc -o stringInsertionSort stringInsertionSort.c"
* 	- Execution: "./stringInsertionSort"
*/

void displayArray(char **arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        i < (size - 1) ? printf("%s, ", arr[i]) : printf("%s]\n", arr[size-1]);
    }
}


void insertionSort(char **array, int size) {

	int current;
    char *temp;

    for (int i=1; i<size; i++) {
        current = i;
        while (current > 0 && strcmp(array[current - 1], array[current]) > 0) {
            temp = array[current];
            array[current] = array[current - 1];
            array[current - 1] = temp;
            current--;
        }
    }
}

int main(int argc, char** argv) {
	int size;
    char **array, string[25];

	printf("\nEnter array size: ");
    
	scanf("%d", &size); 
    array = (char**) malloc(size * sizeof(char*));

    for (int i=0; i<size; i++) {
        printf("Enter value for index %d: ", i);
        scanf("%s", string);
        array[i] = malloc(strlen(string));
        strcpy(array[i], string);
    }

    printf("\nInput array: ");
    displayArray(array, size);

    insertionSort(array, size);

    printf("Sorted array: ");
    displayArray(array, size);
    printf("\n");

	return 0;
}
