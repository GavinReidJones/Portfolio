/*
ForwardEulerSolver.hpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

ForwardEulerSolver is a class to utilise the Forward Euler method of solving ODEs.
The class contains a method to solve an ODE using Forward Euler method
and a function to determine the numerical error E(h) present in the method.
*/

#ifndef FORWARDEULERSOLVERHEADERDEF
#define FORWARDEULERSOLVERHEADERDEF

//Module dependencies
#include "Vector.hpp"
#include "ODEInterface.hpp"
#include "AbstractODESolver.hpp"

//Forward Euler solver is derived from AbstractODESolver
class ForwardEulerSolver : public AbstractODESolver
{
public :
	//Specialised Constructor
	ForwardEulerSolver(ODEInterface& AnODESystem, Vector& initialState,
		const double initialTime, const double finalTime,
		const double stepSize,	const std::string outputFileName = "output.dat",
		const int saveGap = 1, const int printGap = 1);
	
	//Method that returns the numerical error present in the Forward Euler method 
	double NumericalError();
	//Method to perform Forward Euler Method to solve an ODE 
	void Solve();

private:
	//Default Constructor
	ForwardEulerSolver();
	//Vector to store the initial state of the ODE system
	Vector& mInitialState;
	//String variable to store the name of the output file
	std::string mOutputFileName;
	//Variables to store the period of the results that are displayed and saved
	int mSaveGap, mPrintGap;
};

#endif

 