#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/*
* To compile and run this code, paste the commands inside the double quotes into your terminal.
* DO NOT copy the double quotes as well.
* 	- Compilation: "gcc -o prime prime.c -lm"
* 	- Execution: "./prime"
* 
* Note: The -lm flag is needed for the math library	as per the the accepted answer on https://stackoverflow.com/questions/10409032/why-am-i-getting-undefined-reference-to-sqrt-error-even-though-i-include-math.
*/
bool isPrime(int number) {

	if (number == 0 || number == 1) {
		return false;
	}

	// The syntax for the sqrt function was taken from https://www.programiz.com/c-programming/library-function/math.h/sqrt
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
