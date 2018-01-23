/*
Driver.cpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

This Driver is intended to be used to test the accuracy of the compute f method, then solve two Neural 
field initial value problems
*/

//Module Dependencies
#include "RungeKutta4Solver.hpp"
#include "NeuralField1D.hpp"
#include "ODEInterface.hpp"
//set the value of pi
const double pi = atan(1) * 4;

int main()
{
	//initialise t
	double t=0.0;
	
	//set up the vector to store the parameters to test the accuracy of ComputeF
	Vector ParametersA(8);
	//A1
	ParametersA[0] = 1;
	//A2
	ParametersA[1] = 0;
	//b
	ParametersA[2] = 2;
	//mu
	ParametersA[3] = 3.5;
	//theta
	ParametersA[4] = 1.0;
	//L
	ParametersA[5] = 50;
	//m
	ParametersA[6] =2000;
	//alpha
	ParametersA[7] = 0.4;

	//instantiate a pointer to the parameter vector
	Vector& pParameters(ParametersA);
	//Instantiate a Neural Field interface with the selected parameters
	ODEInterface* Q3b = new NeuralField1D(pParameters);

	//initialise vectors of size m+1 for the initial states Q, the ustar and vstar vectors that 
	//will be used to verify the accuracy result 

	Vector Ustar(ParametersA[6]+1);
	Vector Vstar(ParametersA[6] + 1);
	
	//declare variables for x sigma and the two parameters to be used by the error function in calculating vstar 
	double x;
	double sigma = (2 * ParametersA[5]) / ParametersA[6];
	long double ErrFuncPar1, ErrFuncPar2;

	//a loop to determine the value of each ODE stored in Ustar, Vstar and Q
	for (int i = 0; i <= ParametersA[6]; i++)
	{
		//calculate x
		x = -ParametersA[5] + i*sigma;
				
		//Calculate the test value for Ustar corresponding to the correct ODE
		Ustar[i] = ParametersA[4] - (1.0 / ParametersA[3])*pow(x, 2)*log( 1.25 - exp(-pow(x, 2)));

		//calculate the two parameters of the error function in Vstar
		ErrFuncPar1 = ((2 * ParametersA[5] - x) / sqrt(2));
		ErrFuncPar2 = ((2 * ParametersA[5] + x) / sqrt(2));
		
		//calculate test values Vstar
		Vstar[i] = -Ustar[i] + 0.8*sqrt(pi / 8)*exp(-pow(x, 2) / 2)*(erf(ErrFuncPar1) + erf(ErrFuncPar2));
	}

	//Initialise a vector to store F
	Vector F(ParametersA[6] + 1);

	//Call ComputeF
	Q3b->ComputeF(t, Ustar, F);
	
	//initialise values for a max infinite norm and the current infinite norm
	double CurrentNorm,Norm=0.0;
	//loop through each ODE stored in the vector
	for (int i = 0; i < ParametersA[6]; i++)
	{
		//calculate the difference between Vstar and F
		CurrentNorm = (Vstar[i] - F[i]);
		//Check the modulus
		CurrentNorm = sqrt(pow(CurrentNorm, 2));
		//if the current norm is larger than the previous largest infinity norm it replaces it
		if (CurrentNorm > Norm)
		{
			Norm = CurrentNorm;
			
		}
	}
	
	//print out the infinity norm of vstar-f(ustar)
	std::cout << "The Norm of V*-f(u*) is " << Norm << "\n";
	
	//delete the Nerual Field Interface used in the first section
	delete Q3b;
	
	//question bii
	//Redefine some of the values of the parameter Vector

	//set up the vector to store the parameters
	Vector ParametersB(8);
	//A1
	ParametersB[0] = 0;
	//A2
	ParametersB[1] = 1;
	//b
	ParametersB[2] = 0.4;
	//mu
	ParametersB[3] = 3.5;
	//theta
	ParametersB[4] = 1.0;
	//L
	ParametersB[5] = 50;
	//m
	ParametersB[6] = 300;
	//alpha
	ParametersB[7] = 0.1;
	
	
	sigma = (2 * ParametersB[5]) / ParametersB[6];
	//initialise vectors of size m+1 for the initial states Q, the ustar and vstar vectors that 
	//will be used to verify the accuracy result 
	Vector Qb(ParametersB[6] + 1);
	for (int i = 0; i < ParametersB[6]+1; i++)
	{
		//calculate x
		x = -ParametersB[5] + i*sigma;
		//Q is the initial value for each ODE
		Qb[i] = 4 / pow(cosh(ParametersB[7] * x), 2);
	}
	//instantiate a pointer to the parameter vector
	Vector& pParametersB(ParametersB);

	//Instantiate a Neural Field interface with the selected parameters
	ODEInterface* Q3bii = new NeuralField1D(pParametersB);
	//instantiate a pointer to the initial condition vector
	Vector& pQb(Qb);
	//Instantiate a Runge-Kutta 4 solver
	RungeKutta4Solver* pQ3bii = new RungeKutta4Solver(*Q3bii, pQb, 0, 10, 0.01,"output1.dat",1000,1000);
	//call the solve method from the solver
	pQ3bii->Solve();

	//Free up memory
	delete Q3bii;
	delete pQ3bii;

	//question biii
	//set up the vector to store the parameters
	Vector ParametersC(8);
	//A1
	ParametersC[0] = 0;
	//A2
	ParametersC[1] = 1;
	//b
	ParametersC[2] = 0.4;
	//mu
	ParametersC[3] = 3.5;
	//theta
	ParametersC[4] = 1.0;
	//L
	ParametersC[5] = 50;
	//m
	ParametersC[6] = 300;
	//alpha
	ParametersC[7] = 0.4;


	sigma = (2 * ParametersC[5]) / ParametersC[6];
	//initialise vectors of size m+1 for the initial states Q, the ustar and vstar vectors that 
	//will be used to verify the accuracy result 
	Vector Qc(ParametersC[6] + 1);
	for (int i = 0; i < ParametersC[6] + 1; i++)
	{
		//calculate x
		x = -ParametersC[5] + i*sigma;
		//Q is the initial value for each ODE
		Qc[i] = 4 / pow(cosh(ParametersC[7] * x), 2);
	}
	//instantiate a pointer to the parameter vector
	Vector& pParametersC(ParametersC);

	//Instantiate a Neural Field interface with the selected parameters
	ODEInterface* Q3biii = new NeuralField1D(pParametersC);
	//instantiate a pointer to the initial condition vector
	Vector& pQc(Qc);
	//Instantiate a Runge-Kutta 4 solver
	RungeKutta4Solver* pQ3biii = new RungeKutta4Solver(*Q3biii, pQc, 0, 10, 0.01, "output2.dat", 1000, 1000);
	//call the solve method from the solver
	pQ3biii->Solve();

	//Free up memory
	delete Q3biii;
	delete pQ3biii;



	return 0;
}


