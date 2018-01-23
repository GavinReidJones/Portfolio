
/*copy_vec.cpp : Defines the entry point for the console application.

Last edited  23/1/17 by Gavin Reid-Jones

The copy vector function creates a copy of a given vector of size n
*/

//Standard C++ dependencies
#include <iostream>
#include <cmath>

void *copy_vec(double *copy_vector, double *new_vector, int n)
{

	//copies the corresponding values from the vector passsed to the function to the new vector
	for (int i = 0; i < n; i++)
	{
		new_vector[i] = copy_vector[i];
	}
	
	return NULL;
}