/*
RungeKutta4Solver.hpp

Written by Gavin Reid-Jones. Last edited 7/1/18.

RungeKutta4Solver is a class to utilise the Runge-Kutta 4 method of solving ODEs.
The class contains a method to solve an ODE using Runge-Kutta
and a method to determine the numerical error E(h) present in the method.
*/

#ifndef RUNGEKUTTAFOURSOLVERHEADERDEF
#define RUNGEKUTTAFOURSOLVERHEADERDEF

//Dependecies of module
#include "Vector.hpp"
#include "ODEInterface.hpp"
#include "AbstractODESolver.hpp"

class RungeKutta4Solver : public AbstractODESolver
{
public:
	//Specialised Constructor
	RungeKutta4Solver(ODEInterface& anODESystem, const Vector& initialState,
						const double initialTime, const double finalTime,
						const double stepSize, const std::string outputFileName = "output.dat",
						const int saveGap = 1, const int printGap = 1);
	
	//Method to perform Runge-Kutta 4 Method to solve an ODE 
	void Solve();

	//Method that returns the numerical error present in the Runge-Kutta method 
	double NumericalError();

private:
	//Default constructor
	RungeKutta4Solver();

	//Vector to store the initial state of the ODE system
	Vector mInitialState;
	//String variable to store the name of the output file
	std::string mOutputFileName;
	//Variables to store the period of the results that are displayed and saved
	int mSaveGap, mPrintGap;
};
#endif
