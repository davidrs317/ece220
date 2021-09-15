/* This is a C program to print out Pascal's Triangle
* To do this the program takes a row input
* and sets up a for loop that is as long as the row + 1
* the for loop represents the number of coefficients
* The code then calculates the coefficient of k using the 
* fact that the coefficient is equal to 
* the number of rows +1 - the current coefficient
* divided by the current coefficient
* once the value is calculated the coefficient is then printed
* and once the for loop terminates a new line is printed
*/
//edited by davidrs3, airra2, and nroger5  
#include <stdio.h>
#include <stdlib.h>

int main()
{
 	int row, i; //declare row to hold input and i to iterate through loop
	unsigned long coef; // an unsigned long to hold all coefficients
 	printf("Enter a row index: "); //tells the user to input a value
 	scanf("%d",&row); //takes user input and stores it in row
	for(i = 0; i <= row; i++){ // for loop that will run for the number of coefficients needed
		if (i == 0){ // automatically print 1 on the first iteration
			coef = 1;
			printf("%ld ", coef);
		}
		else{ // run the factorial equations for finding the coefficient, value must multiply on itself to get the right value
			coef = coef*(row + 1 - i)/i;
			printf("%ld ", coef);
		}
	}
	printf("\n"); // prints a new line at the end of the code.

  return 0;
}
