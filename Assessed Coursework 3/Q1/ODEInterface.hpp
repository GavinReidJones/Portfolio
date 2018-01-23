#ifndef ODEINTERFACEHEADERDEF
#define ODEINTERFACEHEADERDEF

#include "Vector.hpp"

// Interface class for ODE problems of the type
//  du/dt = f(t,u)
//  where t is a real number
//        u is a vector of state variables

class ODEInterface
{

  public:

    // Compute right-hand side (pure virtual)
    virtual void ComputeF( const double t, const Vector& u, Vector& f ) const = 0;

    // Compute analytical solution
    virtual void ComputeAnalyticSolution( const double t, Vector& u ) const = 0;

};

#endif
