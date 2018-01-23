/*pcg.cpp : Defines the entry point for the console application.

Last edited 30/11/17 by Gavin Reid-Jones

The Preconditioned Conjugate Gradient function takes the CSR form of a matrix A, size n x n, and a resulting vector b and uses a 6 step process to produce a
solution to x for the matrix problem Ax=b

Though similar to the Cg method the PCG relies on applying the symmetric Gauss Siedel method to a vector to cut down on computing time for the program.
*/
#include "stdafx.h"
#include <iostream>
#include <cmath>

//allow the function to use the other functions we have created
double *sp_matrix_multiply(double *matrix_entries, double *column_no, double *row_start, double *x, int n);
double *copy_vec(double *vector, int n);
double dotproduct(double *vector1, double *vector2, int n);
double *vec_plus_scalar_times_vec(double *yvector, double *zvector, double alpha, int n);
double *symmetric_gauss_siedel(double *matrix_entries, double *column_no, double *row_start, double *b, int n, double tol_gs, int nmax, bool output_errors);

double *pcg(double *matrix_entries, double *column_no, double *row_start, double *b, int n, double tol, double tol_gs, int nmax)
{
	//declare the vectors used in the function
	double *rk,*rk1, *xk,*xk1, *zk,*zk1, *pk, *pk1;
	//declare the variables to be used in the function , rknorm is set to one to initialise it before it is used in the termination threshhold
	double alpha_k, beta_k, k, rknorm=1;
	
	//initialise the guess for xk
	xk = new double[n];
	//set X0=0
	for (int i = 0; i < n; i++)
	{
		xk[i] = 0;
	}
	//use copy vec function to copy b to rk
	rk = copy_vec(b, n);
	//use guass siedel to get inital preconditioned vector
	zk = symmetric_gauss_siedel(matrix_entries, column_no, row_start, rk, n, tol_gs, nmax, false);
	//copy zk
	pk = copy_vec(zk, n);
	// initialise k
	k = 0;

	// loop until the normal of rk is below the tolerance threshold given as a parameter 
	while (rknorm>tol)
	{
		//performs the pcg method using the methods developed in the earlier questions
		alpha_k = dotproduct(zk, rk, n) / dotproduct(pk, sp_matrix_multiply(matrix_entries, column_no, row_start, pk, n), n);
		xk1 = vec_plus_scalar_times_vec(xk, pk, alpha_k, n);
		rk1 = vec_plus_scalar_times_vec(rk, sp_matrix_multiply(matrix_entries, column_no, row_start, pk, n), -alpha_k, n);
		zk1 = symmetric_gauss_siedel(matrix_entries, column_no, row_start, rk1, n, tol_gs, nmax, false);
		beta_k = dotproduct(zk1, rk1, n) / dotproduct(zk, rk, n);
		pk1 = vec_plus_scalar_times_vec(zk1, pk, beta_k, n);

		//sets the values of k to those of k+1
		xk = xk1;
		rk = rk1;
		zk = zk1;
		pk = pk1;
		
		//set the normal of r_k to be 0
		rknorm = 0;
		//perform the calculation of the normal 
		for (int i = 0; i < n; i++)
		{
			rknorm = rknorm + pow(rk[i], 2);
		}
		rknorm = pow(rknorm, 0.5);
	
		//print the value of the normal and the iteration for the user to see
		std::cout << "r_k normal = " << rknorm << " Iteration k = " << k << "\n";
		k++ ;
	}
	


	return xk;
}