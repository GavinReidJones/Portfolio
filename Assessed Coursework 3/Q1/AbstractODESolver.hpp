/*
AbstractODESolver.hpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

Abstract class used to derive ODE Solvers such as the forward Euler Method
and the Runge-Kutta 4 method.
*/
#ifndef ABSTRACTODESOLVERHEADERDEF
#define ABSTRACTODESOLVERHEADERDEF

//Module dependencies
#include "ODEInterface.hpp"

class AbstractODESolver
{

protected:
	//Variables to store the start and end times of a solution and the step size h
	double mFinalTime, mInitialTime, mStepSize;
	//A way for the solver to access the ODe that it is trying to solve
	ODEInterface* mpODESystem;

public:
	//virtual method to solve ODE
	virtual void Solve() = 0;
	//virtual method to print a header to the console 
	virtual void PrintHeader(std::string method) const;
	//virtual method to print an iteration of the solver to the console
	virtual void PrintIteration(const double t, Vector& Solution) const;
	//virtual method to save an iteration of the solver to an output file
	virtual void SaveIteration(Vector& Solution, std::ofstream& output_file) const ;

};

#endif // !ABSTRACTODESOLVERHEADERDEF


