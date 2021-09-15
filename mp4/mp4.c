//worked on by davidrs3 airra2 and nroger5
// code below takes two inputs from the user and then
//finds semiprime values of the first input from those two inputs
#include <stdlib.h>
#include <stdio.h>


int is_prime(int number); //declares the function is_prime
int print_semiprimes(int a, int b); //declares the print_semiprimes function


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   print_semiprimes(a, b); //calls the print_semiprimes function
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number) //the definition of the is_prime function
{

  for (int i = 2; i < number; i++){ //for loop that will check all possible factors of the input
    if(number % i == 0){ //if the number can be divided by an values it is not prime
      return 0; //This means the number is NOT prime
    }
  }
  return 1; //The number is prime
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b){ //definition of the print_semiprimes function
  int check = 0; //declares a check variable that will see whether or not there are semiprimes
  for (int n = a; n <= b; n++){ //for loop that will iterate through all values between the two inputs inclusive
    int minus = (n-1); //this variable is to make the following for loop easier to read
    for (int k = 2; k <= minus; k++){ //allows for each possible value lower then n to be tested for prime status
      int factor; //used to find whether or not k is a factor of n
      int quotient; 
      factor = (n%k); //see if k is a factor of n
	quotient = (n/k); //find the value of the input divided by the counter
	if ( factor == 0){ //function can only be semiprime if the current value of the counter is a factor of the input a
		if ((is_prime(k) == 1) && (is_prime(quotient) == 1)){ //if counter and quotient are prime then value within the range is semiprime
			printf("%d ",n); // print the value we have found to be semiprime
			check = 1; //states that semiprimes exist
			break; //now that a semiprime has been found to exist the loob must be exited to find another one
		}
	}
    }
  }
  printf("\n"); //a new line
  if (check == 1){
	return 1; //return 1 if semiprimes exist
  }
  else{
	return 0; //return 0 if semiprimes do not exist
  }

}