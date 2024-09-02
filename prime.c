#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/*
* Compilation: gcc -o prime prime.c -lm
* To run the program: ./prime
* 
* Note: The -lm flag is needed for the math library.
*/
bool isPrime(int number) {
    double squareRoot = sqrt((double)number);
	int count = 0;
	int i;

    for (i = 1; i <= squareRoot; i++) {
        if (number % i == 0) {
            count++;
        }
    }

	return count < 2;
}

int main(int argc, char** argv) {
	int given_number;

	printf("Enter a number: ");
	scanf("%d", &given_number);

	if (isPrime(given_number))
		printf("The number is prime\n");
	else
		printf("The number is not prime\n");

	return 0;
}
