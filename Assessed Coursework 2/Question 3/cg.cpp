/*cg.cpp : Defines the entry point for the console application.

Last edited 23/1/18  by Gavin Reid-Jones

The Conjugate Gradient function takes the CSR form of a matrix A, size n x n, and a resulting vector b and uses a 5 step process to produce a
solution to x for the matrix problem Ax=b  
*/ 

#include <iostream>
#include <cmath>

//allow the function to use the other functions we have created
void *sp_matrix_multiply(double *Ax, double *matrix_entries, int *column_no, int *row_start, double *x, int n);
void *copy_vec(double *copy_vector, double *new_vector, int n);
double dotproduct(double *vector1, double *vector2, int n);
void *vec_plus_scalar_times_vec(double* xvector, double *yvector, double *zvector, double alpha, int n);

double *cg(double *matrix_entries, int *column_no, int *row_start, double *b, int n, double tol)
{
	//declare the vectors used in the function
	double *r_k, *Ap_k, *p_k, *x_k, *r_k1, *p_k1, *x_k1;

	//defines the sizes of the used arrays
	r_k = new double[n];
	Ap_k = new double[n];
	p_k = new double[n];
	r_k1 = new double[n];
	p_k1 = new double[n];
	x_k1 = new double[n];

	//declare the variables to be used in the function , r_kn is set to one to initialise it before it is used in the termination threshhold
	double alpha_k, beta_k, r_knorm = 1, k;
	//initialise the iteration counter k
	k = 0;
	//call the copy vector function to store b as r_0
	copy_vec(b, r_k, n);
	//call the copy vector function to store r_0 as p_0
	copy_vec(r_k,p_k, n);
	//declare the initial guess for x_0 
	x_k = new double[n];
	//set all x_0 values to 0
	for (int i = 0; i < n; i++)
	{
		x_k[i] = 0;
	}

	// loop until the normal of r_k is below the tolerance threshold given as a parameter 
	while (r_knorm > tol)
	{
		//each step in the CG method is calculated in the loop
		//calculate Ap_k
		sp_matrix_multiply(Ap_k, matrix_entries, column_no, row_start, p_k, n);
		//alpha_k calls the dot product and matrix multiply functions from previous questions
		alpha_k = dotproduct(r_k, r_k, n) / dotproduct(p_k,Ap_k, n);
		//x_k calls the vector plus scalar function from a previous question
		vec_plus_scalar_times_vec(x_k1,x_k, p_k, alpha_k, n);
		
		
		//r_k1 is the representation of r_k+1 but i didnt want to use mathematical symbols in variable names, it calls the vector plus scalar function from a previous question
		vec_plus_scalar_times_vec(r_k1,r_k,Ap_k , -alpha_k, n);
		//alpha_k calls the dot product function from previous questions
		beta_k = dotproduct(r_k1, r_k1, n) / dotproduct(r_k, r_k, n);
		//p_k calls the vector plus scalar function from a previous question, this is a slight abuse as i am just iterating over the same vector p_k when i really should of used p_k1
		vec_plus_scalar_times_vec(p_k1,r_k1, p_k, beta_k, n);

		//set k =k+1
		copy_vec(r_k1, r_k, n);
		copy_vec(x_k1, x_k, n);
		copy_vec(p_k1, p_k, n);
		

		//set the normal of r_k to be 0
		r_knorm = 0;
		//perform the calculation of the normal 
		for (int i = 0; i < n; i++)
		{
			r_knorm = r_knorm + pow(r_k[i], 2);
		}
		r_knorm = pow(r_knorm, 0.5);
		//increment the iteration counter
		k++;

		//print the value of the normal and the iteration for the user to see
		std::cout << "r_k normal = " << r_knorm << " Iteration k = " << k << "\n";
	}


	return x_k;

}