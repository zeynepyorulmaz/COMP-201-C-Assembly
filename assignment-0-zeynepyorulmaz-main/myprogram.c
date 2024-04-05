#include "mylibrary.h"

int sum(int n)
{
	//This function sums the all natural integers until n and return the sum.
	// The for loop is used for summing each number and incrementing until reaching n
	int result = 0;
	

	//TODO: 1+2+...+
	for (int i= 0; i<n+1; i++){
		result +=i;
	}

	return result;
}

int product_of_even_numbers(int *array, int count)
{
	//This function checks every element of an array if the element is an even number they multiply all of the even numbers and returns the product.
	
	int product = 1;
	for (int i=0;i<count;++i) //for iterating
	{
		if (array[i]%2==0){ //checks if it is even
		product*=array[i]; //multiplies	//TODO: only multiply even numbers, e.g., 2. Skip odd numbers, e.g., 3
	}
	}
	return product;
}

int max_of_numbers(int *array, int count)
{
	//This function returns the maximum integer of an array.
	//
	//TODO: return the maximum number from the array
	int max = array[0]; //initializing max 
	for (int i =0; i<count; i++){
		if (array[i] > max){ //check if the current element is greater tan the temporary max
		max = array[i];
		}
	}
	return max;
}

int reversed_number(int number)
{
	//This funciton returns the number as reversed
	//TODO: if input is 12345, return 54321
	int reversed = 0;
	while (number != 0){ //this loop makes it work until a digit exists after dividing by 10
		int digit = number%10;//what is the remainder from 10
		reversed = reversed * 10 + digit; 
		number /= 10; //to continue with the least significant digit
	}

	return reversed;
}


char alphabet_index(int index)
{
	//TODO: for index 0, return A. index 1, B, etc. until 25 for Z.
	//if index is out of range, return space ' '.
	if ( index >= 0 && index<= 25){ //because there are 26 letters in english alphabet
	return (char)('A' + index); //in char A to Z every letter is continued with an 1 increment
	}
	return ' ';
}


