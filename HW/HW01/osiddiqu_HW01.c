#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

/*
* To compile and run this code, paste the commands inside the double quotes into your terminal.
* DO NOT copy the double quotes as well.
* 	- Compilation: "gcc -o osiddiqu_HW01 osiddiqu_HW01.c -lm"
* 	- Execution: "./osiddiqu_HW01"
*/


// Helper Function for main
void printArray(int *arr, int size) {
    printf("[");
    for (int i=0; i<size; i++) {
        (i < size - 1) ? printf("%d, ", arr[i]) : printf("%d]\n", arr[i]);
    }
}

bool primeOrFactorial(int n) {

    double squareRoot = sqrt((double) n);
    int count = 0;
    unsigned int factorial = 1;

    if (n <= 1) {
        printf("Invalid Input\n");
        return 0;
    }

    for (int i = 1; i <= squareRoot; i++) {
        if (n % i == 0) {
            count++;

            if (count >= 2) {
                break;
            }
        }
    }

    if (count < 2) {
        printf("Prime Number\n");
        return 1;
    } else {
        for (int j = 1; j <= n; j++) {
            factorial = factorial * j;
        }

        printf("%d\n", factorial);
        return factorial;
    }
}

// Found the answer to why I need to pass the size of array as a param at: 
// https://stackoverflow.com/questions/25680014/find-the-size-of-integer-array-received-as-an-argument-to-a-function-in-c
int UABIndexSum(int arr[], int array_size) {
    int total = 0;

    for (int i = 0; i <= array_size; i++) {
        if (i == arr[i]) {
            total = total + i;
        }
    }

    printf("%d\n", total);
    return total;
}

int* replaceEvenWithZero(int arr[], int array_size) {
    int *new_array;
    new_array = malloc(array_size);

    for (int i = 0; i < array_size; i++) {
        if (arr[i] % 2 == 0) {
            new_array[i] = 0;
        } else {
            new_array[i] = arr[i];
        }
    }

    return new_array;
}

void evenSquare(int n) {
    double squareRoot = sqrt((double) n);
    double threshold = 0.00001;

    ((int)squareRoot % 2 == 0) && (squareRoot - (int)squareRoot <= threshold) ? printf("True\n") : printf("False\n");
}

int countVowels(char s[]) {
    int size = strlen(s);
    char vowels[] = {'A', 'E', 'I', 'O', 'U'};
    int count = 0;

    for (int i=0; i<size; i++) {
        for (int j = 0; j < 5; j++) {
            if (s[i] == vowels[j] || s[i] == (char)(vowels[j] + 32)) {
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char** argv) {

    printf("=================================================\n");
    printf("1. Prime/Factorial Check\n");
    printf("=================================================\n");
    
    printf("Input: 5, Output: ");
    primeOrFactorial(5);
    printf("Input: 4, Output: ");
    primeOrFactorial(4);
    printf("Input: 1, Output: ");
    primeOrFactorial(1);
    printf("Input: 7, Output: ");
    primeOrFactorial(7);
    printf("Input: -3, Output: ");
    primeOrFactorial(-3);

    printf("\n=================================================\n");
    printf("2. UAB Index Sum\n");
    printf("=================================================\n");

    int arr1[] = {0, 2, 2, 4};
    int arr2[] = {3, 1, 0, 4};
    int arr3[] = {1, 2, 3, 3};
    int arr4[] = {1, 2, 3, 4};

    int sizeOfArray1 = sizeof(arr1) / sizeof(arr1[0]);
    int sizeOfArray2 = sizeof(arr2) / sizeof(arr2[0]);
    int sizeOfArray3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Eg 1: ");
    printArray(arr1, sizeOfArray1);
    printf("Output: ");
    UABIndexSum(arr1, sizeOfArray1);

    printf("\nEg 2: ");
    printArray(arr2, sizeOfArray2);
    printf("Output: ");
    UABIndexSum(arr2, sizeOfArray2);

    printf("\nEg 3: ");
    printArray(arr3, sizeOfArray3);
    printf("Output: ");
    UABIndexSum(arr3, sizeOfArray3);
    printf("\n");

    printf("=================================================\n");
    printf("3. Replace Even with Zero\n");
    printf("=================================================\n");

    int input1[] = { 1, 2, 3, 4 };
    int sizeOfInput1 = sizeof(input1) / sizeof(input1[0]);
    int input2[] = { 2, 4, 6 };
    int sizeOfInput2 = sizeof(input2) / sizeof(input2[0]);
    int input3[] = { 1, 3, 5 };
    int sizeOfInput3 = sizeof(input3) / sizeof(input3[0]);
    


    int *result = replaceEvenWithZero(input1, sizeOfInput1);
    printf("Input 1: [1, 2, 3, 4], Output: ");
    printArray(result, sizeOfInput1);
    result = replaceEvenWithZero(input2, sizeOfInput2);
    printf("Input 2: [2, 4, 6], Output: ");
    printArray(result, sizeOfInput2);
    printf("Input 3: [1, 3, 5], Output: ");
    result = replaceEvenWithZero(input3, sizeOfInput3);
    printArray(result, sizeOfInput3);
    

    printf("\n=================================================\n");
    printf("4. Even Square Check\n");
    printf("=================================================\n");
    
    printf("Input 1: 16, Output: ");
    evenSquare(16);
    printf("Input 2: 15, Output: ");
    evenSquare(15);
    printf("Input 3: 25, Output: ");
    evenSquare(25);
    printf("Input 4: 36, Output: ");
    evenSquare(36);


    printf("\n=================================================\n");
    printf("5. Count Vowels\n");
    printf("=================================================\n");

    char s1[] = "Hello World";
    printf("Input 1: \"%s\", Output: %d", s1, countVowels(s1));
    char s2[] = "UAB CS";
    printf("\nInput 2: \"%s\", Output: %d", s2, countVowels(s2));
    char s3[] = "Python";
    printf("\nInput 3: \"%s\", Output: %d", s3, countVowels(s3));
    char s4[] = "aeiou";
    printf("\nInput 4: \"%s\", Output: %d", s4, countVowels(s4));

    printf("\n\n");
    return 0;
}

