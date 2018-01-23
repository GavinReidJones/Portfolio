/*q4b.cpp : Defines the entry point for the console application.

Last edited 30/11/17 by Gavin Reid-Jones

The Test function to apply the symmetric gauss siedel method to find a solution to the matrix problem, Ax=b.
*/
#include "stdafx.h"
#include <cmath>
#include <iostream>

double *symmetric_gauss_siedel(double *matrix_entries, double *column_no, double *row_start, double *b, int n, double tol_gs, int nmax, bool output_errors);

int main()
{
	//define the matrices and variables to be used in the test 
	double *matrix_entries, *column_no, *row_start, *b, *X;
	double tol_gs = pow(10, -10);
	int n=4, nmax=20;
	bool output_errors = true;

	//defines the sizes of the test arrays
	matrix_entries = new double[8]{ 8, 2, 3, 1, 4, 2, 1, 7 };
	column_no = new double[8]{ 1, 4, 2, 4, 3, 1, 2, 4 };
	row_start = new double[n + 1]{ 1, 3, 5, 6, 9 };
	b = new double[n] { 58, 29, 8, 55};
	X = new double[n] ;
	
	//calls the symmetric gauss siedel method
	X=symmetric_gauss_siedel(matrix_entries, column_no, row_start, b, n, tol_gs, nmax, output_errors);

	//displays x
	std::cout << " X = {";
	for (int i = 0; i < n; i++)
	{
		std::cout << X[i] << " ";
	}
	std::cout << "} \n \n";
	
	return 0;
}

