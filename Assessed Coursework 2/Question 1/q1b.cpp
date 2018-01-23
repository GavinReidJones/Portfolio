/*q1b.cpp : Defines the entry point for the console application.

Last edited 23/1/17 by Gavin Reid-Jones

The Test function to solve the matrix multiplication problem Ax
*/

//declare standard c++ dependencies
#include <cmath>
#include <iostream>

double *sp_matrix_multiply(double *matrix_entries, double *column_no, double *row_start, double *x, int n);

void main()
{
	//define the matrices and variables to be used in the test 
	double *matrix_entries, *column_no, *row_start, *x, *Ax;
	int n = 4;

	//defines the sizes of the test arrays
	matrix_entries = new double[8];
	column_no = new double[8]; { 1, 4, 2, 4, 3, 1, 2, 4 }
	row_start = new double[n + 1]; { 1, 3, 5, 6, 9 }
	x = new double[n] { 6, 8, 2, 5};
	Ax = new double[n];
	
	//initialise matrix entries
	matrix_entries[0] = 8;
	matrix_entries[1] = 2;
	matrix_entries[2] = 3;
	matrix_entries[3] = 1;
	matrix_entries[4] = 3;
	matrix_entries[5] = 2;
	matrix_entries[6] = 1;
	matrix_entries[7] = 7;
	//initialise column number entries
	column_no[0] = 1;
	column_no[1] = 4
	column_no[2] = 2;
	column_no[3] = 4;
	column_no[4] = 3;
	column_no[5] = 1;
	column_no[6] = 2;
	column_no[7] = 4;
	//initialise row start entries
	row_start[0] = 1;
	row_start[1] = 3;
	row_start[2] = 5;
	row_start[3] = 6;
	row_start[4] = 9;
	//initialise x vector
	x[0] = 6;
	x[1] = 8;
	x[2] = 2;
	x[3] = 5;

	//calls the function to find Ax
	sp_matrix_multiply(Ax, matrix_entries, column_no, row_start, x, n);

	//deletes the pointer arrays to save memory ass they are no longer needed
	delete[] matrix_entries;
	delete[] column_no;
	delete[] row_start;
	delete[] x;

	//prints Ax
	std::cout << "Ax = (" << Ax[0] << " " << Ax[1] << " " << Ax[2] << " " << Ax[3] << ") \n ";

	//deletes the Ax array to save memory as it is no longer needed
	delete[] Ax;

}

