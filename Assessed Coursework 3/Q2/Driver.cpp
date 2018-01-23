/*
Driver.cpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

This driver is intended to solve a linear ODE using the  Runge Kutta 4 method
and to determine the numerical error E(h) present in the method.
*/

//Module dependencies
#include "LinearODE.hpp"
#include "Vector.hpp"
#include "RungeKutta4Solver.hpp"

//Standard unit dependencies
#include <assert.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

void main()
{
	//Q2bi
	//initialise the time variables and the step size for the method
	double InitialTime = 0, FinalTime = 10, h = 0.01;

	//Initialise the solution vector
	Vector Uh(1);
	//Initialise the vector to store the rhs of the ODE
	Vector F(1);
	//Create reference to vector
	Vector& pU(Uh);

	//Instantiate pointer to the ODE interface
	ODEInterface* pODE = new LinearODE(Uh, F);

	//Instantiate the solver with the correct parameters
	RungeKutta4Solver* pQuestion2 = new RungeKutta4Solver(*pODE, pU, InitialTime, FinalTime, h, "output.dat",1,25);
	//Call solve method from solver
	pQuestion2->Solve();

	//Free up memory
	delete pQuestion2;

	//Q2bii
	//Change ending time of the method
	FinalTime = 2;
	//Initialise variable to store the approximation error
	double ApproximationError = 0.0;
	//Set the output file name
	std::string outputFileName = "Error.dat";

	// Setting strem file precision
	std::ofstream error_file;
	error_file.setf(std::ios::scientific, std::ios::floatfield);
	error_file.precision(4);

	//Open the output file
	error_file.open(outputFileName);
	assert(error_file.is_open());
	//Print a header
	error_file << std::setw(10) << "h" << std::setw(20) << "E(h)" << std::endl;
	//Loop through different values of h to determine the error present in the method
	for (h = 0.0025; h<1.001; h = h + 0.0025)
	{
		//Instantiate a solver
		RungeKutta4Solver* pQuestion2 = new RungeKutta4Solver(*pODE, pU, InitialTime, FinalTime, h);
		//Call the numerical error method from the solver
		ApproximationError = pQuestion2->NumericalError();
		//Output the size of h and the error present to the file
		error_file << std::setw(15) << "" << std::setw(20) << ApproximationError << std::endl;
		//Reset the Error
		ApproximationError = 0.0;
		//Free up memory
		delete pQuestion2;

	}

	//Close the file
	error_file.close();
	//Free up memory
	delete pODE;


	return;
}