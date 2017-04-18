//---------------------------------------------------------------------//
// University of Central Florida									   //
// COP 3502 - Fall 2016 - Szumlanski								   //
// Program Author: Henry Ton										   //
// PID: H2950390												       //
// Program 2: Fibonacci.c											   //
//---------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Fibonacci.h"

//---------------------------------------------------------------------//
// This function takes in an integer and returns the number of
// digits that it contains.
//---------------------------------------------------------------------//
int digitCounter(int n)
{
	if (n < 10)
		return 1;

	int counter = 1, div = 10;

	while ((n / div) >= 1)
	{
		div = div * 10;
		counter++;
	}
	return counter;
}

//---------------------------------------------------------------------//
// hugeAdd takes in two struct pointers and returns the sum of the 
// two struct pointers in HugeInteger format
//---------------------------------------------------------------------//
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
	HugeInteger *r;
	int carry = 0, i, length, temp, short_length;

	// Checking for NULL
	if (p == NULL || q == NULL)
		return NULL;

	// Two distinct lengths are calculated, the length of the shorter array
	// and the length of the longer array
	length = ((p->length > q->length) ? p->length : q->length);
	short_length = ((p->length < q->length) ? p->length : q->length);

	// Allocating space for r and the integer array
	r = malloc(sizeof(HugeInteger));
	r->digits = calloc(length + 1, sizeof(int));

	// This is where the two arrays in the struct are added
	// (Up until the shortest digit terminates)
	for (i = 0; i < short_length; i++)
	{
		temp = p->digits[i] + q->digits[i] + carry;

		if (temp > 9)
		{
			carry = 1;
			r->digits[i] = temp % 10;
		}
		else
		{
			carry = 0;
			r->digits[i] = temp;
		}
	}

	// Finishing up the addition with any carry over digits
	if (p->length > q->length)
	{
		for (i = short_length; i < length; i++)
		{
			temp = p->digits[i] + carry;
			if (temp > 9)
			{
				r->digits[i] = temp % 10;
				carry = 1;
				if ((i == length - 1) && (p->digits[i] == 0))
					length++;
			}
			else 
			{
				r->digits[i] = temp;
				carry = 0;
			}
		}
	}
	else if (q->length > p->length)
	{
		for (i = short_length; i < length; i++)
		{
			temp = q->digits[i] + carry;
			if (temp > 9)
			{
				r->digits[i] = temp % 10;
				carry = 1;
				if ((i == length - 1) && (q->digits[i] == 0))
					length++;
			}
			else
			{
				r->digits[i] = temp;
				carry = 0;
			}
		}
	}
	else if (p->length == q->length)
	{
		if (carry == 1)
		{
			r->digits[i] = 1;
			length++;
		}
	}

	r->length = length;

	return r;
}

//---------------------------------------------------------------------//
// Frees all dynamically allocated space
//---------------------------------------------------------------------//
HugeInteger *hugeDestroyer(HugeInteger *p)
{
	if (p == NULL)
		return NULL;
	free(p->digits);
	free(p);

	return NULL;
}

//---------------------------------------------------------------------//
// This function takes in a struct pointer and converts the array to
// an unsigned integer value
//---------------------------------------------------------------------//
unsigned int *toUnsignedInt(HugeInteger *p)
{
	// Checking for NULL
	if (p == NULL)
		return NULL;

	int i, mult = 1, length = p->length;
	unsigned int *x, temp = 0;

	x = malloc(sizeof(unsigned int));

	for (i = 0; i < length; i++)
	{
			temp += p->digits[i] * mult;
			mult = mult * 10;
			
	// Returns NULL if the number cannot be represented properly
	if(temp >= 294967296 && p->digits[i+1] >=4)
			{
				return NULL;
			}
	}
		*x = temp;

	return x;
}

//---------------------------------------------------------------------//
// This function takes a string of numbers and breaks them down into 
// HugeInteger format while calculating the length of the array
//---------------------------------------------------------------------//
HugeInteger *parseString(char *str)
{
	HugeInteger *p;
	int i, j, length;
	char temp;

	// Checking for NULL
	if (str == NULL)
		return NULL;

	p = malloc(sizeof(HugeInteger));

	length = strlen(str);
	p->digits = calloc(length + 1, sizeof(int));
	j = length - 1;

	for (i = 0; i < length; i++)
	{
		temp = str[i];
		// converting each value of the string into an integer value to 
		// be stored in p->digits[j]
		p->digits[j] = atoi(&temp);
		j--;
	}

	p->length = length;

	return p;
}

//---------------------------------------------------------------------//
// parseInt takes in an unsigned integer value and converts 
// it into a string. This string is passed into parseString to be
// converted into HugeInteger format
//---------------------------------------------------------------------//
HugeInteger *parseInt(unsigned int n)
{
	HugeInteger *p;
	int length;
	char *str;
	
	length = digitCounter(n);

	if (n <= INT_MAX)
	{
		str = malloc(sizeof(int) * (length + 1));
		sprintf(str, "%d", n);
	}
	else if (n <= UINT_MAX)
	{
		str = malloc(sizeof(long long) * (length + 1));
		sprintf(str, "%u", n);
	}
	else
		return NULL;

	p = parseString(str);
	free(str);

	return p;
}

//---------------------------------------------------------------------//
// The fib function takes in an integer (n) and calculates the nth 
// term of the fibonacci sequence in 0(nk)
//---------------------------------------------------------------------//
HugeInteger *fib(int n)
{
	HugeInteger *p, *q, *r;
	int i;
	
	// base case
	if (n < 2)
	{
		return p = parseInt(n);
	}
	
	// Initializing the first two values of the fib sequence
	r = parseString("0");
	q = parseString("1");

	// 0(n) function that calls hugeAdd( 0(k)) n times. So 0(n*k)
	for (i = 1; i < n; i++)
	{
		p = hugeAdd(q, r);
		if (i == n - 1)
			break;
		r = hugeDestroyer(r);
		r = q;
		q = p;
	}
	// Cleaning up
	r = hugeDestroyer(r);
	q = hugeDestroyer(q);

	return p;
}

//---------------------------------------------------------------------//
// This wasn't as bad as the other assignment, asides
// from figuring out the fib function
//---------------------------------------------------------------------//
double difficultyRating(void)
{
	return 4.0;
}

//---------------------------------------------------------------------//
// Rought estimate of the time i spent programming this
//---------------------------------------------------------------------//
double hoursSpent(void)
{
	return 29.0;
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Fibonacci.h"

// print a HugeInteger (followed by a newline character)
void hugePrint(HugeInteger *p)
{
	int i;

	if (p == NULL || p->digits == NULL)
	{
		printf("(null pointer)\n");
		return;
	}

	for (i = p->length - 1; i >= 0; i--)
		printf("%d", p->digits[i]);
	printf("\n");
}

int main(void)
{
	int i;
	HugeInteger *p;

	for (i = 0; i <= 1000; i++)
	{
		printf("F(%d) = ", i);
		hugePrint(p = fib(i));
		hugeDestroyer(p);
	}

	return 0;
}
