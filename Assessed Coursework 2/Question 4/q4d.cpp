/*q4b.cpp : Defines the entry point for the console application.

Last edited 30/11/17 by Gavin Reid-Jones

The Test function to apply the Precondtioned Conjugate Gradient method to find a solution to the differential equation problem, -u''+u=1.
The function creates a CSR form matrix of size n x n depending on the size of the mesh, and uses the PCG method to solve the resulting matrix problem.
*/
#include "stdafx.h"
#include <iostream>
#include <cmath>

double *pcg(double *matrix_entries, double *column_no, double *row_start, double *b, int n, double tol, double tol_gs, int nmax);

int main()
{
	//define the matrices and variables to be used in the test 
	double *matrix_entries, *column_no, *row_start, *b, *U, *solution;
	double tol = pow(10, -10), h = 0.03125, numberofelements = 0, tol_gs= pow(10,-20), linf=0;
	int n = (1 / h) + 2;
	int nmax = 10;


	numberofelements = 3 * n - 2;
	//defines the sizes of the test arrays
	matrix_entries = new double[numberofelements];
	column_no = new double[numberofelements];
	row_start = new double[n + 1];
	b = new double[n];
	U = new double[n];

	//k counts which element in the matrix entry and column number the program is on, l is used to calculate which row the element is on
	int k = 0, l = 0;

	//sets the first element of the matrix entries and column number rows as the row only require two entries
	matrix_entries[k] = ((2.0 / pow(h, 2)) + (4.0 / 6.0));
	column_no[k] = 1;
	row_start[l] = k + 1;
	//increment the element and row counters
	k++;
	l++;
	//sets the second element of the matrix entries and column number rows as the row only require two entries
	matrix_entries[k] = ((-1.0 / pow(h, 2)) + (1.0 / 6.0));
	column_no[k] = 2;
	k++;
	// loops through assigning the three elements in each row 
	for (int i = 2; i < n; i++)
	{
		//stores the starting point of the row 
		row_start[l] = k + 1;
		//stores the element and increments the element counter
		matrix_entries[k] = ((-1.0 / pow(h, 2)) + (1.0 / 6.0));
		column_no[k] = i - 1;
		k++;
		matrix_entries[k] = ((2.0 / pow(h, 2)) + (4.0 / 6.0));
		column_no[k] = i;
		k++;
		matrix_entries[k] = ((-1.0 / pow(h, 2)) + (1.0 / 6.0));
		column_no[k] = i + 1;
		k++;

		l++;
	}

	//sets the second last element of the matrix entries and column number rows as the row only require two entries
	row_start[l] = k + 1;
	l++;
	matrix_entries[k] = ((-1.0 / pow(h, 2)) + (1.0 / 6.0));
	column_no[k] = n - 1;
	k++;
	//sets the final element of the matrix entries and column number rows as the row only require two entries
	matrix_entries[k] = ((2.0 / pow(h, 2)) + (4.0 / 6.0));
	column_no[k] = n;
	k++;
	row_start[l] = k + 1;

	//sets the array of the results given in the question
	//the boundary points at b[0] and b[n] are 0.5 because you have to take an average of the boundary condition and the initial conditions in a numerical method  
	b[0] = 0.5;
	for (int i = 1; i < n; i++)
	{
		b[i] = 1;
	}
	b[n] = 0.5;

	//calculate U using the pcg method
	U = pcg(matrix_entries, column_no, row_start, b, n, tol,tol_gs, nmax);

	// delete the inital matrix as it is no longer used
	delete[] matrix_entries;
	delete[] column_no;
	delete[] row_start;

	//declare the vector to store the analytical solution of u
	solution = new double[n];
	for (int i = 0; i < n; i++)
	{
		//calculates the analytical solution at each point in u
		solution[i] = (1.0 + exp(1) - exp(1.0 - i*h) - exp(i * h)) / (1.0 + exp(1));

		linf = linf+pow(pow(solution[i] - U[i], 2), 0.5);
		
	}

	//calculates the norm of l_inf
	linf = pow(linf, 0.5);

	//displays l_inf
	std::cout << "l_inf = " << linf << "\n";

	//deletes the arrays storing the analytical and numerical solutions to U before the program closes 
	delete[] U;
	delete[] solution;

	return 0;
}


