/*
RungeKutta4Solver.cpp

Written by Gavin Reid-Jones. Last edited 7/1/18.

RungeKutta4Solver is a class to utilise the Runge-Kutta 4 method of solving ODEs.
The class contains a method to solve an ODE using Runge-Kutta
and a method to determine the numerical error E(h) present in the method.
*/

//Dependecies of module
#include "RungeKutta4Solver.hpp"
//Unit dependencies
#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

//Specialised Constructor
RungeKutta4Solver::RungeKutta4Solver(ODEInterface& anODESystem, const Vector& initialState,
									const double initialTime, const double finalTime,
									const double stepSize, const std::string outputFileName, 
									const int saveGap, const int printGap) : mInitialState(initialState)
{
	//initialise variables to be used in the class
	mpODESystem = &anODESystem;
	mInitialState = Vector(initialState);
	mInitialTime = initialTime;
	mFinalTime = finalTime;
	mStepSize = stepSize;
	mOutputFileName = outputFileName;
	mSaveGap = saveGap;
	mPrintGap = printGap;
}

void RungeKutta4Solver::Solve()
{
	//store size of solution vector to avoid repeatedly using .getsize() function
	double ProblemSize = mInitialState.GetSize();
	//create vectors to store solution and calculation vectors to be used by the Runge-Kutta method
	Vector Uht(mInitialState);
	Vector Uht1(ProblemSize);
	Vector F(ProblemSize);
	Vector k1(ProblemSize);
	Vector k2(ProblemSize);
	Vector k3(ProblemSize);
	Vector k4(ProblemSize);
	Vector calculationk(ProblemSize);
	//initialise counters for the number of iterations since the last save to file and print to the screen 
	int SaveGapCounter = mSaveGap-1, PrintGapCounter = mPrintGap-1;
	//initialise variables to store the time value the method is using and the number of steps the method will perform 
	double t, MeshSize;

	// Setting stream file precision
	std::ofstream output_file;
	output_file.setf(std::ios::scientific, std::ios::floatfield);
	output_file.precision(4);

	//Open output file
	output_file.open(mOutputFileName);
	assert(output_file.is_open());

	//Call the print header function derived from the AbstractODESolver
	PrintHeader("Runge-Kutta 4");
	//Calculate mesh size
	MeshSize = (mFinalTime - mInitialTime) / mStepSize;

	for (int j = 0; j<MeshSize + 1; j++)
	{
		//Determine time value the method has reached
		t = j*mStepSize;

		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the current solution and the f vector 
		mpODESystem->ComputeF(t, Uht, F);
		//Store the k1 Vector to be used in the RK4 method 
		for (int i = 0; i<ProblemSize; i++)
		{
			k1[i] = F[i];
		}

		//Copy the vector k1 to be used in the calculation of k2
		calculationk=k1;
		calculationk = calculationk*(mStepSize / 2);
		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the intermediate solution and the f vector 
		mpODESystem->ComputeF(t+mStepSize/2, calculationk, F);
		//Store the k2 Vector to be used in the RK4 method 
		for (int i = 0; i<ProblemSize; i++)
		{
			k2[i] = F[i];
		}
		//Copy the vector k2 to be used in the calculation of k3
		calculationk=k2;
		calculationk = calculationk*(mStepSize / 2);
		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the intermediate solution and the f vector 
		mpODESystem->ComputeF(t + mStepSize / 2, calculationk, F);
		//Store the k3 Vector to be used in the RK4 method 
		for (int i = 0; i<ProblemSize; i++)
		{
			k3[i] = F[i];
		}
		//Copy the vector k3 to be used in the calculation of k4
		calculationk = k3;
		calculationk = calculationk*mStepSize;
		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the intermediate solution and the f vector 
		mpODESystem->ComputeF(t + mStepSize / 2, calculationk, F);
		//Store the k1 Vector to be used in the RK4 method 
		for (int i = 0; i<ProblemSize; i++)
		{
			k4[i] = F[i];
		}

		//Apply the RK4 Method
		for (int i = 0; i < ProblemSize; i++)
		{
			Uht1[i] = Uht[i] + (mStepSize / 6)*(k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
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


double RungeKutta4Solver::NumericalError()
{
	//store size of solution vector to avoid repeatedly using .getsize() function
	double ProblemSize = mInitialState.GetSize();
	//create vectors to store solution and calculation vectors to be used by the Runge-Kutta method
	Vector Uht(mInitialState);
	Vector Uht1(ProblemSize);
	Vector F(ProblemSize);
	Vector k1(ProblemSize);
	Vector k2(ProblemSize);
	Vector k3(ProblemSize);
	Vector k4(ProblemSize);
	Vector calculationk(ProblemSize);
	Vector AnalyticSolution(ProblemSize);

	double t, MeshSize, CurrentNumError, NumError = 0.0;

	//Calculate mesh size
	MeshSize = (mFinalTime - mInitialTime) / mStepSize;

	for (int j = 0; j<MeshSize + 1; j++)
	{
		//Determine time value the method has reached
		t = j*mStepSize;

		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the current solution and the f vector 
		mpODESystem->ComputeF(t, Uht, F);
		//Store the k1 Vector to be used in the RK4 method 
		for (int i = 0; i<ProblemSize; i++)
		{
			k1[i] = F[i];
		}

		//Copy the vector k1 to be used in the calculation of k2
		calculationk = k1;
		calculationk = calculationk*(mStepSize / 2);
		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the intermediate solution and the f vector 
		mpODESystem->ComputeF(t + mStepSize / 2, calculationk, F);
		//Store the k2 Vector to be used in the RK4 method 
		for (int i = 0; i<ProblemSize; i++)
		{
			k2[i] = F[i];
		}
		//Copy the vector k2 to be used in the calculation of k3
		calculationk = k2;
		calculationk = calculationk*(mStepSize / 2);
		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the intermediate solution and the f vector 
		mpODESystem->ComputeF(t + mStepSize / 2, calculationk, F);
		//Store the k3 Vector to be used in the RK4 method 
		for (int i = 0; i<ProblemSize; i++)
		{
			k3[i] = F[i];
		}
		//Copy the vector k3 to be used in the calculation of k4
		calculationk = k3;
		calculationk = calculationk*mStepSize;
		//Call the ComputeF method from the referenced ODEInterface class, using the vector for the intermediate solution and the f vector 
		mpODESystem->ComputeF(t + mStepSize / 2, calculationk, F);
		//Store the k1 Vector to be used in the RK4 method 
		for (int i = 0; i<ProblemSize; i++)
		{
			k4[i] = F[i];
		}

		//Apply the RK4 Method
		for (int i = 0; i < ProblemSize; i++)
		{
			Uht1[i] = Uht[i] + (mStepSize / 6)*(k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
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

