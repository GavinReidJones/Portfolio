/*q2e.cpp : Defines the entry point for the console application.

Last edited 30/11/17 by Gavin Reid-Jones

The Test function to apply the CG method to the given matrix problem Ax=b
*/

#include <cmath>
#include <iostream>

double *cg(double *matrix_entries, int *column_no, int *row_start, double *b, int n, double tol);

int main()
{
	//define the matrices and variables to be used in the test 
	double *matrix_entries, *b, *X;
	int *column_no, *row_start;
	double tol= pow(10,-10);
	int n = 4;

	//defines the sizes of the test arrays
	matrix_entries = new double[8]{ 8, 2, 3, 1, 4, 2, 1, 7 };
	column_no = new int[8]{ 1, 4, 2, 4, 3, 1, 2, 4 };
	row_start = new int[n + 1]{ 1, 3, 5, 6, 9 };
	b = new double[n] { 58, 29, 8, 55};
	X = new double[n];

	//call the CG method function
	X=cg(matrix_entries, column_no, row_start, b, n, tol);

	//display the approximate solution provided by the CG method
	std::cout << "\n X = { " << X[0] << " " << X[1] << " " << X[2] << " " << X[3] << " } \n";
	//deletes the pointer arrays to save memory ass they are no longer needed
	delete[] matrix_entries;
	delete[] column_no;
	delete[] row_start;
	delete[] X;
	delete[] b;


	return 0;
}

