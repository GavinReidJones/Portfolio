/*
NeuralField1D.cpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

NeuralField1D is an class to interface with a one dimensional Neural field problem.
The class contains an interface to du(x,t)/dt
where U is the space variable and t the time variable.
*/

//Module dependencies
#include "NeuralField1D.hpp"
//Standard unit dependencies
#include <cmath>

//Specialised constructor 
NeuralField1D::NeuralField1D(Vector& parameters): mParameters(parameters)
{
	Vector mParameters(parameters);
}

//Overidden method to solve the equation f(u) = -u(x,t)+sum(w(xi,xj)*g(xj,t)*rho)
void NeuralField1D::ComputeF(const double t, const Vector & u, Vector & f) const
{
	//declare the variables to be used in the method
	double sigma= (2.0 * mParameters[5]) / mParameters[6];
	double  Q,Xi, Xj,G,summation, rho;
	
	//copy u so it can be used in the calculations in the method
	Vector U(u);
	//Initialise a a variable to store the size of the vector that stores the set of ODEs
	double size = mParameters[6]+1;

	//initialise a vector to store each value of w depending on the distance between the two x values
	Vector W(size);
	double DistanceBetweenX;
	//the loop calculates every possible distance between xi and xj, this is important as it means w is only calculated m times rather than m^2 times
	for (int i = 0; i < size; i++)
	{
		//calculates distance betwween x depending on what iteration the loop is on
		DistanceBetweenX = (i*2* mParameters[5])/ mParameters[6];
		//Stores the w value corresponding to the distance between x
		W[i] = mParameters[0] * exp(-pow(DistanceBetweenX, 2)) + mParameters[1] * exp(-mParameters[2] * DistanceBetweenX)*(mParameters[2] * sin(DistanceBetweenX) + cos(DistanceBetweenX));
	}

	//Loop to calculate F corresponding to each ODE 
	for(int i = 0; i<size;i++)
	{
		//initialise the summation term
		summation = 0;
		//calculates the value of Xi
		Xi = -mParameters[5] + i*sigma;

		//loop to calculate the summation term of F
		for (int j = 0; j < size; j++)
		{
			//calculates the value of Xj
			Xj = -mParameters[5] +j*sigma;

			//sets the value of rho depending on the value of j
			if (j == 0 || j == mParameters[6])
			{
				rho = sigma / 3;
			}
			else if (j % 2 == 1)
			{
				rho = 4.0 * sigma / 3;
			}
			else if (j % 2 == 0)
			{
				rho = 2.0 * sigma / 3;
			}

			//calculate the current distance between the two X values
 			DistanceBetweenX = sqrt(pow(Xi -Xj, 2));
			//work out the position in the w vector that the corresponding w value to the distance is given by
			double Wlocation = DistanceBetweenX / ((2.0 * mParameters[5]) / mParameters[6]);
			//round the location to avoid any precision errors that may occur
			Wlocation = round(Wlocation);
			//Calculate G
			G = 1.0 / (1.0 + exp(-mParameters[3] * (U[j] - mParameters[4])));
			//increment the summation value by w*g*rho	
			summation += W[Wlocation]*G* rho;
		}
		//store the calculated f value 
		f[i] = -U[i] + summation;
		
	}
}
//Method to solve the analytic solution is not applicable for this interface but had to be overidden. 
void NeuralField1D::ComputeAnalyticSolution(const double t, Vector & u) const
{
}
