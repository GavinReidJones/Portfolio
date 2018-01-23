/*dot_product.cpp : Defines the entry point for the console application.

Last edited  23/1/18 by Gavin Reid-Jones

The dot product function performs the dot product calculation on two one dimensional vectors of the same size n. 
*/

#include <iostream>
#include <cmath>

double dotproduct(double *vector1, double *vector2, int n)
{
   	//define the variables used in the loop to calculate the final dot product
	double Dotproductresult = 0, Elementresult = 0;

		//loops through every element in the vector
		for (int i = 0; i < n; i++)
		{
			//multiplies each element in vector 1 by the corresponding element in vector 2 and adds it to the running total for the dot product
			Elementresult = vector1[i] * vector2[i];
			Dotproductresult = Dotproductresult + Elementresult;
		}
	//returns Result
	return Dotproductresult;

}

