/*
AbstractODESolver.hpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

Abstract class used to derive ODE Solvers such as the forward Euler Method
and the Runge-Kutta 4 method.
*/

//Module dependencies
#include "AbstractODESolver.hpp"
//Standard unit dependencies
#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

//Method to print a header to the console, when given the name of the solver being used
void AbstractODESolver::PrintHeader(std::string method) const
{
	std::cout << "------------------------------------------------------------------------- \n"
		<< "This solver will attempt to use the " << method << " to solve an ODE \n"
		<< "------------------------------------------------------------------------- \n"
		<< "	t			Uh \n";
}

//method to print an iteration of the solver to the console
void AbstractODESolver::PrintIteration(const double t, Vector & Solution) const
{
	std::cout << std::setw(10) << t << "	(";
	// Write data
	for (int i = 0; i < Solution.GetSize() && i < 3; i++)
	{
		std::cout << std::scientific
			<< std::setprecision(6)
			<< std::setw(5)<<   Solution[i] <<"  ";
	}
	std::cout << " )\n";

}
//method to save an iteration of the solver to an output file, when given the solution vector and an output stream
void AbstractODESolver::SaveIteration(Vector & Solution, std::ofstream & output_file) const
{
	// Write data
	for (int i = 0; i<Solution.GetSize(); i++)
	{
		output_file << std::setw(15) << Solution[i] << "  ";
		
	}
	output_file << std::endl;
}
