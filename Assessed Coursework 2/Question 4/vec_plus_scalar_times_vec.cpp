
/*vec_plus_scalar_times_vec.cpp : Defines the entry point for the console application.

Last edited  23/1/17 by Gavin Reid-Jones

The function perfoms the operation of adding a vector to a vector multiplied by a scalar,
in the form x=y + a*z
*/


#include <iostream>
#include <cmath>

void *vec_plus_scalar_times_vec(double* xvector, double *yvector, double *zvector, double alpha, int n)
{

	//performs the calculation x = y+ a*z
	for (int i = 0; i < n; i++)
	{
		xvector[i] = yvector[i]+zvector[i] * alpha;
	}
	
	return NULL;
}