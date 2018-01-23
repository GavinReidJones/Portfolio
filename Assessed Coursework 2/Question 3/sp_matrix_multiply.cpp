
/*sp_matrix_multiply.cpp : Defines the entry point for the console application.

Last edited  23/1/18 by Gavin Reid-Jones

The function perfoms the multiplication of an n x n and an 1 x n matrix
*/

//declare standard c++ dependencies
#include <cmath>
#include <iostream>



void *sp_matrix_multiply(double *Ax, double *matrix_entries, int *column_no, int *row_start, double *x, int n)
{
	//integers to loop the calculation of the product and a type transform to use as a paramater
	int col_num, i, j;
	//summation variables to calculate the product vector
	double elementtotal=0, rowtotal=0;

	//loops through every value in the row start array
	for (i = 0; i < n ; i++)
	{
		//loops through each row in the matrix by using the row start array
		for (j = row_start[i] - 1; j < row_start[i + 1] - 1; j++)
		{
			//stores the column position of an element to an integer value so it can be used as a parameter
			col_num = column_no[j]-1;
			//calculates the value of the product of the matrix element and the corresponding value in the x vector 
			elementtotal = matrix_entries[j] * x[col_num];
			//calculates the result element in the Ax vector
			rowtotal = rowtotal + elementtotal;
		}
		//stores the result in the Ax vector
		Ax[i] = rowtotal;
		//clears the calculation for the next loop through.
		rowtotal = 0;
		elementtotal = 0;
	 }
	
	return NULL;
}

