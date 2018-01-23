/*symmetric_gauss_siedel.cpp : Defines the entry point for the console application.

Last edited 30/11/17 by Gavin Reid-Jones

The function perfoms the symmetric Gauss Siedel method to solve the Matrix problem Ax=b
This can then be used to reduce computation time in the pcg method. 
*/
#include "stdafx.h"
#include <cmath>
#include <iostream>

double *symmetric_gauss_siedel(double *matrix_entries, double *column_no, double *row_start, double *b, int n, double tol_gs, int nmax, bool output_errors)
{
	//declare the variables to be used in the function 
	double ajj, errorX=10, l = 0;
	//declare the vectors used in the function
	double *Z, *Z_lhalf, *Z_l1;

	//initialise the vectors used in the gauss siedel method 
	Z = new double[n];
	Z_lhalf = new double[n];
	Z_l1= new double[n];

	//sets the initial guess for Z to 0
	for (int i = 0; i < n; i++)
	{
		Z[i] = 0;
	}
	
	//loops the process while the number of iterations is less than the threshold given or while the error is more than the tolerance 
	while ((l < nmax) && (errorX > tol_gs))
	{
		//loops through every column in the matrix
		for (int j = 0; j < n; j++)
		{
			//determines whether the element in the matrix entries vector is on the middle diagonal
			for (int i = row_start[j]-1; i<row_start[j+1]-1; i++)
			{
				if (column_no[i]  == j+1)
				{
					ajj = matrix_entries[i];
				}
			}
			//variables store the sum of when m<j and m>j
			double Sumtotalless = 0, sumtotalmore = 0;
			int m = 0;
			for (int i = row_start[j]-1; i<row_start[j + 1]-1; i++)
			{
				//m stores the vector address that corresponds to the right value
				m = column_no[i]-1;
				//calculates the sum of elements that are to the left of the j element
				if (m< j)
				{
					Sumtotalless = Sumtotalless+ matrix_entries[i] * Z_lhalf[m];
				}
				//calculates the sum of elements that are to the right of the j element
				else if (m > j)
				{
					Sumtotalless = Sumtotalless + matrix_entries[i] * Z[m];	
				}
			}
			//performs the calculation to determine the elements of z_lhalf
			Z_lhalf[j] = (1.0 / ajj)*(b[j]- Sumtotalless- sumtotalmore);
		}

		for (int j = n; j >-1; j--)
		{
			//determines whether the element in the matrix entries vector is on the middle diagonal
			for (int i = row_start[j] - 1; i<row_start[j + 1] - 1; i++)
			{
				if (column_no[i] == j + 1)
				{
					ajj = matrix_entries[i];
				}
			}

			//variables store the sum of when m<j and m>j
			double Sumtotalless = 0, sumtotalmore = 0;
			int m = 0;
			for (int i = row_start[j]-1; i<row_start[j + 1]-1; i++)
			{
				m = column_no[i]-1;
				//calculates the sum of elements that are to the left of the j element
				if (m< j)
				{
					Sumtotalless = Sumtotalless + matrix_entries[i] * Z_lhalf[m];
				}
				//calculates the sum of elements that are to the right of the j element
				else if (m > j)
				{
					
					sumtotalmore = sumtotalmore + matrix_entries[i] * Z_l1[m];

				}
			}
			//performs the calculation to determine the elements of z_l1
			Z_l1[j] = (1.0 / ajj)*(b[j] - Sumtotalless - sumtotalmore);
		}

		//maximum error of x is calculated by taking the modulus of the difference between zk and zk1 
		errorX = pow(pow(Z_l1[0] - Z[0], 2), 0.5);
		// loops through all members of z to determine the largest difference
		for (int i = 0; i < n; i++)
		{
			if (errorX < pow(pow(Z_l1[i] - Z[i], 2),0.5))
			{
				errorX = pow(pow(Z_l1[i] - Z[i], 2), 0.5);
			}
		}

		//replaces the values in z with those in z_l1
		Z = Z_l1;

		// if the user has told the function to display the error results it will print them to the console
		if (output_errors == true)
		{
			std::cout << "k = " << l << " Error = " << errorX << "\n";
		}
		//increment l
		l++;
	}
	//return the result

    return Z;
}

