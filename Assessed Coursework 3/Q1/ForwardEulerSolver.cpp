/*
ForwardEulerSolver.hpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

ForwardEulerSolver is a class to utilise the Forward Euler method of solving ODEs.
The class contains a method to solve an ODE using Forward Euler method
and a function to determine the numerical error E(h) present in the method.
*/
//Module dependencies
#include "ForwardEulerSolver.hpp"
//Standard unit dependencies
#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

//Specialised constructor
ForwardEulerSolver::ForwardEulerSolver(ODEInterface& AnODESystem, Vector& initialState,
										const double initialTime, const double finalTime, 
										const double stepSize, const std::string outputFileName,
										const int saveGap, const int printGap): mInitialState(initialState)
{
	mpODESystem = &AnODESystem;
	mInitialState = Vector(initialState);
	mInitialTime = initialTime;
	mFinalTime = finalTime;
	mStepSize = stepSize;
	mOutputFileName = outputFileName;
	mSaveGap = saveGap;
	mPrintGap = printGap;
}

void ForwardEulerSolver::Solve()
{
	//create vectors to store solution and calculation vectors to be used by the Forward Euler method
	Vector Uht(mInitialState);
	Vector Uht1(mInitialState);
	Vector F(mInitialState);
	Vector AnalyticSolution(mInitialState);
	
	//initialise counters for the number of iterations since the last save to file and print to the screen 
	int SaveGapCounter=mSaveGap-1, PrintGapCounter=mPrintGap-1;
	//initialise variables to store the time value the method is using and the number of steps the method will perform 
	double t, MeshSize;

	// Setting strem file precision
	std::ofstream output_file;
	output_file.setf(std::ios::scientific, std::ios::floatfield);
	output_file.precision(4);

	//Open file
	output_file.open(mOutputFileName);
	assert(output_file.is_open());
	
	//Call the print header function derived from the AbstractODESolver
	PrintHeader("Forward Euler");
	//Calculate mesh size
	MeshSize=(mFinalTime - mInitialTime) / mStepSize ;

	for (int j = 0; j<MeshSize+1; j++)
	{
		//Determine time value the method has reached
		t = j*mStepSize;
		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the current solution and the f vector 
		
		mpODESystem->ComputeF(t, Uht, F);
		//For every dimension of U perform the Forward Euler Method 
		for (int i = 0; i<mInitialState.GetSize(); i++)
		{
			Uht1[i] = Uht[i] + mStepSize*F[i];
		}


		//increment the SaveGapCounter, if it reaches the required number of iterations since the last save to file, it will save and reset the counter
		SaveGapCounter++;
		if (SaveGapCounter == mSaveGap)
		{
			SaveIteration(Uht, output_file);
			SaveGapCounter = 0;
		}
		//increment the PrintGapCounter, if it reaches the required number of iterations since the last print to console, it will print and reset the counter
		PrintGapCounter++;
		if (PrintGapCounter == mPrintGap)
		{
			PrintIteration(t, Uht);
			PrintGapCounter = 0;
		}

		//update the vector to be calculated
		Uht = Vector(Uht1);
	}
	
	// Close file
	output_file.close();

}

double ForwardEulerSolver::NumericalError()
{
	//create vectors to store solution and calculation vectors to be used by the Forward Euler method
	Vector Uht(mInitialState);
	Vector Uht1(mInitialState);
	Vector F(mInitialState);
	Vector AnalyticSolution(mInitialState);
	
	double t, MeshSize, CurrentNumError, NumError=0.0;
	//Calculate mesh size
	MeshSize = (mFinalTime - mInitialTime) / mStepSize;

	for (int j = 0; j < MeshSize + 1; j++)
	{
		//Determine time value the method has reached
		t = j*mStepSize;
		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the current solution and the f vector 

		mpODESystem->ComputeF(t, Uht, F);
		//For every dimension of U perform the Forward Euler Method 
		for (int i = 0; i<mInitialState.GetSize(); i++)
		{
			Uht1[i] = Uht[i] + mStepSize*F[i];
		}

		//Initialise CurrentNumError
		CurrentNumError = 0.0;
		//Apply the ComputeAnalyticSolution from the referenced ODEInterface class
		mpODESystem->ComputeAnalyticSolution(t, AnalyticSolution);
		//Calculate the numerical error present in the current iteration of the method
		for (int i = 0; i < mInitialState.GetSize(); i++)
		{
			CurrentNumError += AnalyticSolution[i] - Uht[i];
		}

		//If the size of the current error is larger than the previous Largest error it is stored to be displayed by the method
		CurrentNumError = sqrt(pow(CurrentNumError, 2));
		if (CurrentNumError > NumError)
		{
			NumError = CurrentNumError;
		}
		//Update calculation Vector
		Uht = Vector(Uht1);

	}
	//return Result
	return NumError;
}
