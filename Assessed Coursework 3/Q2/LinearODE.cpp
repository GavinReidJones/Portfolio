/*
LinearODE.cpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

This Class is an interface to allow the the solver to calculate a Linear ODE
The class contains a specialised constructor, A method to solve the RHS of the ODE Problem
and a method to calculate the analytical solution to an ODE Problem.
*/
#include "LinearODE.hpp"
#include "Vector.hpp"

//Standard unit dependencies
#include <cmath>


//Specialised constructor
LinearODE::LinearODE(Vector & u, Vector & f) : mpU(u), mpF(f)
{
	//Vectors store the values passed into the interface
	mpU = Vector(u);
	mpF = Vector(f);
}

//Method to compute the right hand side to the ODE problem
void LinearODE::ComputeF(const double t, const Vector & u, Vector & f)const
{
	//works for every dimension of the problem
	for (int i = 0; i < u.GetSize(); i++)
	{
		//Store the RHS of the problem in the appropriate vector
		f[i] = 1.0 / (1.0 + pow(t, 2.0));
	}
	
}

//Method to compute the analytical solution to the ODE problem
void LinearODE::ComputeAnalyticSolution(const double t, Vector & u)const
{
	//works for every dimension of the problem
	for (int i = 0; i < u.GetSize(); i++)
	{
		//Store the analytical solution of the problem in the appropriate vector
		u[i] = (1.0 / sqrt(1.0))*atan(t / sqrt(1.0));
	}
	
	
}
