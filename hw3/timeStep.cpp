/*  Code for Assignment 3 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted 
code for any purpose.  The code was written for teaching, not research 
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file timeStep.cpp

/*  take one time step

A wave Gaussian packet centered on x_0 with half-width r_0 and wave number k

u_0(x) = exp( - (x-x_0)^2/(2r_0^2) ) * sin(kx)

set u[j] = u_0(x_j)

*/

#include <iostream>
#include <math.h>
#include <vector>         // so you can use the vector class/template system
using namespace std;


void timeStep( vector<double>& u,      // the solution at the current time, replaced by the solution at the next tiome
               vector<double>& v,      // a temp vector
               double          dx,     // the space step
               double          dt,     // the time step
               int             nx) {   // number of grid points
  
  for ( int j = 0; j < (nx-1); j++) {  // do a left shift ...
    v[j] = u[j+1];
   }
  v[nx-1] = 0.;                        // ... adding a zero on the end
  
  for ( int j = 0; j < nx; j++) {      // copy v back to u when the time step is done.
    u[j] = v[j];
   }
  
  return;
 }

  