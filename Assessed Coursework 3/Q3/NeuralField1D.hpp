/*
NeuralField1D.hpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

NeuralField1D is an class to interface with a one dimensional Neural field problem.
The class contains an interface to du(x,t)/dt 
where U is the space variable and t the time variable.
*/

#ifndef NEURALFIELDONEDHEADERDEF
#define NEURALFIELDONEDHEADERDEF

//Depoendencies of module
#include "ODEInterface.hpp"
#include "Vector.hpp"
#include "RungeKutta4Solver.hpp"


class NeuralField1D : public ODEInterface
{
public:
	//Specialised Constructor
	NeuralField1D(Vector& parameters);
	//Overidden method to solve the equation given by the right hand side of du(x,t)
	void ComputeF(const double t, const Vector& u, Vector& f) const;
	//Overidden method to solve the equation if given the analytical solution, this doesn't apply for the Neural Field problem. 
	void ComputeAnalyticSolution(const double t, Vector& u) const;



private:
	//Default constructor
	NeuralField1D();
	//Vector to store parameters used in the problem.
	Vector& mParameters;

	

	
};


#endif // !NEURALFIELDONEDHEADERDEF
