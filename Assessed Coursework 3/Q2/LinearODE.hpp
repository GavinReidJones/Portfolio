/*
LinearODE.hpp

Written by Gavin Reid-Jones. Last edited 8/1/18.

This Class is an interface to allow the the solver to calculate a Linear ODE
The class contains a specialised constructor, A method to solve the RHS of the ODE Problem
and a method to calculate the analytical solution to an ODE Problem.
*/
#ifndef LINEARODEHEADERDEF
#define LINEARODEHEADERDEF

//Module dependencies
#include "ODEInterface.hpp"
#include "Vector.hpp"


class LinearODE : public ODEInterface
{
	public:
		//Specialised constructor
		LinearODE( Vector& u,  Vector& f);
		//Method to compute the right hand side to the ODE problem
		void ComputeF(const double t, const Vector& u, Vector& f) const;
		//Method to compute the analytical solution to the ODE problem
		void ComputeAnalyticSolution(const double t, Vector& u) const;
	
	private:
		//Vectors to store f and u
		Vector mpF, mpU;

};


#endif // !LINEARODEHEADERDEF
